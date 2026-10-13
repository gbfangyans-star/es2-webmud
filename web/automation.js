// 觸發（trigger）與計時器（timer）。設定只存在這個瀏覽器（localStorage），可匯出／匯入。
//
// 觸發樣式採 zMUD 寫法：
//   *  任意文字        ?  任一個字
//   %d 數字            %n 可帶正負號的數字
//   %w 一個詞（中英文字、數字）   %a 同 %w
//   %s 空白            %x 非空白字元
//   ( ) 擷取成 %1～%9   {甲|乙} 二選一   [abc] 字元集合
//   ^ 行首  $ 行尾      ~ 讓下一個字元照字面比對
// 也可勾選「正規表示式」直接寫 JavaScript regex。
// 指令可用 ; 串接，%0 是整段符合的文字，%1～%9 是擷取到的文字。
//
// 網頁本地指令（不送到伺服器，輸入欄、觸發、計時器都能用）：
//   #wa 毫秒      等一下再送後面的指令（只寫 #wa 是 1 秒）
//   #3 指令       同一個指令重複 3 次
//   #dis／#con    中斷連線（不自動重連）／重新連線
//   #tr [on|off]  開關全部觸發      #t+ 類別／#t- 類別  開關某一組觸發
//   #sh 文字      只在自己畫面印一行字

import {bgTimeout,bgInterval,clearBg} from './bg_timer.js';

const STORAGE_KEY='es2-automation-v1';
const MAX_AUTO_SENDS_PER_SECOND=20;
const TIMER_TICK_MS=250;
const MAX_USER_CHAIN_COMMANDS=9;   // 輸入欄一次最多送幾個指令（#wa 等本地指令不算）
const MAX_REPEAT=99;
const MAX_WAIT_MS=3600000;

const esc=s=>String(s??'').replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
const uid=()=>Date.now().toString(36)+Math.random().toString(36).slice(2,7);

export function compilePattern(pattern,{regex=false,caseSensitive=false}={}){
  const flags='u'+(caseSensitive?'':'i');
  if(regex)return new RegExp(pattern,flags);
  const p=String(pattern);
  let out='';
  for(let i=0;i<p.length;i++){
    const c=p[i];
    if(c==='~'&&i+1<p.length){out+=escapeRe(p[++i]);continue;}
    if(c==='^'&&i===0){out+='^';continue;}
    if(c==='$'&&i===p.length-1){out+='$';continue;}
    if(c==='*'){out+='.*';continue;}
    if(c==='?'){out+='.';continue;}
    if(c==='('||c===')'){out+=c;continue;}
    if(c==='{'){
      const end=p.indexOf('}',i);
      if(end>i){out+='(?:'+p.slice(i+1,end).split('|').map(escapeRe).join('|')+')';i=end;continue;}
    }
    if(c==='['){
      const end=p.indexOf(']',i);
      if(end>i){out+='['+p.slice(i+1,end).replace(/[\\\]]/g,'\\$&')+']';i=end;continue;}
    }
    if(c==='%'&&i+1<p.length){
      const k=p[i+1];
      const map={d:'\\d+',n:'[+-]?\\d+',w:'[\\p{L}\\p{N}_]+',a:'[\\p{L}\\p{N}_]+',s:'\\s+',x:'\\S+'};
      if(map[k]){out+=map[k];i++;continue;}
    }
    out+=escapeRe(c);
  }
  return new RegExp(out,flags);
}
function escapeRe(c){return c.replace(/[.*+?^${}()|[\]\\\/]/g,'\\$&');}

export function expandCommand(template,match){
  return String(template).replace(/%(\d)/g,(_,n)=>match[Number(n)]??'');
}

// 把一行拆成一個個指令，並展開 #3 e 這種重複寫法。
export function splitCommandLine(line){
  const out=[];
  for(const part of String(line).split(';').map(s=>s.trim()).filter(Boolean)){
    const m=part.match(/^#(\d+)\s+(.+)$/);
    if(m){const n=Math.min(MAX_REPEAT,Number(m[1]));for(let i=0;i<n;i++)out.push(m[2].trim());}
    else out.push(part);
  }
  return out;
}
// #wa／#wait 回傳要等的毫秒數，不是等待指令就回傳 null。
export function parseWait(part){
  const m=String(part).trim().match(/^#wa(?:it)?(?:\s+(\d+))?\s*$/i);
  if(!m)return null;
  return Math.min(MAX_WAIT_MS,m[1]===undefined?1000:Number(m[1]));
}

function defaultState(){return {triggersEnabled:true,paused:false,disabledClasses:[],triggers:[],timers:[]};}
function normalizeTrigger(t){
  return {id:t.id||uid(),pattern:String(t.pattern||''),command:String(t.command||''),cls:String(t.cls||''),
    enabled:t.enabled!==false,caseSensitive:!!t.caseSensitive,regex:!!t.regex,prompt:!!t.prompt};
}
function normalizeTimer(t){
  const seconds=Math.max(1,Math.floor(Number(t.seconds)||0));
  const fireAt=Math.min(seconds,Math.max(0,Math.floor(Number(t.fireAt)||0)));
  return {id:t.id||uid(),name:String(t.name||''),seconds,fireAt,command:String(t.command||''),loop:!!t.loop};
}

export class Automation{
  constructor({sendCommand,sendUserCommand,notify,isBlocked,disconnect,connect}){
    this.sendCommand=sendCommand;   // (command) => void，觸發／計時器送出的指令（畫面上照樣顯示）
    this.sendUserCommand=sendUserCommand||sendCommand; // 玩家自己在輸入欄打的指令
    this.disconnect=disconnect||(()=>false); // #dis：回傳 false 表示本來就沒連線
    this.connect=connect||(()=>false);       // #con：回傳 false 表示已經連線中
    this.pending=new Set();         // 被 #wa 擋住、還在等的指令串
    this.notify=notify;             // (message) => void，在畫面印一行系統訊息
    this.isBlocked=isBlocked||(()=>false); // 輸入密碼、編輯文章時不自動送指令
    this.state=this.load();
    this.compiled=new Map();
    this.lineBuffer='';
    this.promptFired=new Set();     // 這一行尚未換行時已經觸發過的 trigger id
    this.sendTimes=[];
    this.running=new Map();         // timer id -> {startedAt, fired}
    this.tickTimer=null;
    this.listeners=new Set();
  }

  // ---------- 儲存 ----------
  load(){
    try{
      const x=JSON.parse(localStorage.getItem(STORAGE_KEY)||'null');
      if(x&&typeof x==='object'){
        const s=defaultState();
        s.triggersEnabled=x.triggersEnabled!==false;
        s.paused=!!x.paused;
        s.disabledClasses=Array.isArray(x.disabledClasses)?x.disabledClasses.map(String):[];
        s.triggers=Array.isArray(x.triggers)?x.triggers.map(normalizeTrigger):[];
        s.timers=Array.isArray(x.timers)?x.timers.map(normalizeTimer):[];
        return s;
      }
    }catch(_){}
    return defaultState();
  }
  save(){
    try{localStorage.setItem(STORAGE_KEY,JSON.stringify(this.state));}catch(_){}
    this.compiled.clear();
    this.emit();
  }
  onChange(fn){this.listeners.add(fn);}
  emit(){for(const fn of this.listeners)fn();}

  exportJSON(){
    const {triggersEnabled,disabledClasses,triggers,timers}=this.state;
    return JSON.stringify({format:'es2-automation',version:1,triggersEnabled,disabledClasses,triggers,timers},null,2);
  }
  importJSON(text){
    const x=JSON.parse(text);
    if(!x||typeof x!=='object'||(!Array.isArray(x.triggers)&&!Array.isArray(x.timers)))
      throw new Error('檔案格式不正確');
    this.stopAllTimers();
    this.state.triggers=(x.triggers||[]).map(normalizeTrigger);
    this.state.timers=(x.timers||[]).map(normalizeTimer);
    this.state.disabledClasses=Array.isArray(x.disabledClasses)?x.disabledClasses.map(String):[];
    if(typeof x.triggersEnabled==='boolean')this.state.triggersEnabled=x.triggersEnabled;
    this.save();
    return {triggers:this.state.triggers.length,timers:this.state.timers.length};
  }

  // ---------- 開關 ----------
  setTriggersEnabled(on){this.state.triggersEnabled=!!on;this.save();}
  setPaused(on){this.state.paused=!!on;if(this.state.paused)this.cancelPending();this.save();}
  toggleClass(cls,on){
    const set=new Set(this.state.disabledClasses);
    if(on)set.delete(cls);else set.add(cls);
    this.state.disabledClasses=[...set];this.save();
  }
  classes(){return [...new Set(this.state.triggers.map(t=>t.cls).filter(Boolean))].sort();}

  // #tr、#t+、#t-、#sh、#dis、#con。回傳 true 表示是本地指令，不送到伺服器。
  // （#wa 和 #3 由 run() 處理。）
  handleClientCommand(raw){
    const text=String(raw).trim();
    let m=text.match(/^#tr(?:\s+(on|off))?\s*$/i);
    if(m){
      const next=m[1]?m[1].toLowerCase()==='on':!this.state.triggersEnabled;
      this.setTriggersEnabled(next);
      this.notify(`觸發已全部${next?'開啟':'關閉'}。`);
      return true;
    }
    m=text.match(/^#t([+-])\s*(.*)$/i);
    if(m){
      const cls=m[2].trim(),on=m[1]==='+';
      if(!cls){this.notify('請寫上要開關的觸發類別。');return true;}
      this.toggleClass(cls,on);
      const n=this.state.triggers.filter(t=>t.cls===cls).length;
      this.notify(n?`觸發類別「${cls}」已${on?'開啟':'關閉'}（${n} 個）。`:`沒有類別為「${cls}」的觸發。`);
      return true;
    }
    m=text.match(/^#(?:sh|show)(?:\s+(.*))?$/i);
    if(m){this.notify(m[1]||'');return true;}
    if(/^#dis(?:connect)?\s*$/i.test(text)){
      if(!this.disconnect())this.notify('目前沒有連線。');
      return true;
    }
    if(/^#con(?:nect)?\s*$/i.test(text)){
      if(!this.connect())this.notify('已經連線中。');
      return true;
    }
    return false;
  }

  // ---------- 觸發 ----------
  upsertTrigger(t){
    const x=normalizeTrigger(t);
    compilePattern(x.pattern,x); // 樣式有錯就在這裡丟出例外
    const i=this.state.triggers.findIndex(y=>y.id===x.id);
    if(i>=0)this.state.triggers[i]=x;else this.state.triggers.push(x);
    this.save();return x;
  }
  removeTrigger(id){this.state.triggers=this.state.triggers.filter(t=>t.id!==id);this.save();}
  regexFor(t){
    let re=this.compiled.get(t.id);
    if(re===undefined){
      try{re=t.pattern?compilePattern(t.pattern,t):null;}catch(_){re=null;}
      this.compiled.set(t.id,re);
    }
    return re;
  }
  activeTriggers(){
    if(!this.state.triggersEnabled||this.state.paused)return [];
    const off=new Set(this.state.disabledClasses);
    return this.state.triggers.filter(t=>t.enabled&&!(t.cls&&off.has(t.cls)));
  }

  // 收到遊戲文字（已去掉 @@WEBHUD 資料，可含 ANSI 色碼；cleanText 由呼叫端提供）。
  feed(text,cleanText){
    if(!this.state.triggers.length)return;
    this.lineBuffer+=String(text);
    const parts=this.lineBuffer.split(/\r\n|\n|\r/);
    this.lineBuffer=parts.pop()||'';
    if(this.lineBuffer.length>4000)this.lineBuffer=this.lineBuffer.slice(-4000);
    const active=this.activeTriggers();
    for(const line of parts){
      if(active.length)this.matchLine(cleanText(line),active,this.promptFired);
      this.promptFired=new Set();
    }
    // 沒有換行的提示行（例如「你要買嗎？」），只比對勾了「提示行」的觸發。
    if(this.lineBuffer&&active.length){
      const promptTriggers=active.filter(t=>t.prompt&&!this.promptFired.has(t.id));
      if(promptTriggers.length){
        const fired=this.matchLine(cleanText(this.lineBuffer),promptTriggers,new Set());
        for(const id of fired)this.promptFired.add(id);
      }
    }
  }
  matchLine(line,triggers,skip){
    const fired=[];
    // 遊戲的「> 」提示字元常和下一則訊息黏在同一行，比對前先拿掉，^ 行首才會準。
    const plain=line.replace(/^(?:[>＞]\s*)+/,'').replace(/\s+$/,'');
    if(!plain.trim())return fired;
    for(const t of triggers){
      if(skip.has(t.id))continue;
      const re=this.regexFor(t);if(!re)continue;
      re.lastIndex=0;
      const m=re.exec(plain);if(!m)continue;
      fired.push(t.id);
      if(t.command)this.run(expandCommand(t.command,m),`觸發「${t.pattern}」`);
    }
    return fired;
  }

  // 執行一串以 ; 分隔的指令（可含 #wa、#3 等本地指令）。
  // user：玩家在輸入欄打的。一次最多送 9 個、不受每秒 20 個的保險限制。
  run(commandLine,source,{user=false}={}){
    const parts=splitCommandLine(commandLine);
    if(user&&!parts.length){this.sendUserCommand(String(commandLine));return;} // 空白行照送（例如按 Enter 繼續）
    this.step({parts,i:0,source,user,sent:0,timer:null},true);
  }
  step(job,first){
    while(job.i<job.parts.length){
      const part=job.parts[job.i++];
      const wait=parseWait(part);
      if(wait!==null){
        if(job.i>=job.parts.length)return; // 最後一個是 #wa，不用等
        this.pending.add(job);
        job.timer=bgTimeout(()=>{this.pending.delete(job);this.step(job,false);},wait); // 背景分頁也準時
        return;
      }
      if(this.handleClientCommand(part))continue;
      // 玩家當下打的指令照常送（沒連線時會顯示提示）；等過 #wa 之後和自動指令則先確認現在能送。
      if((!job.user||!first)&&this.isBlocked())return;
      if(job.user){
        if(job.sent>=MAX_USER_CHAIN_COMMANDS){this.notify('你的動作太快了...');return;}
        job.sent++;
        this.sendUserCommand(part);
        continue;
      }
      const now=Date.now();
      this.sendTimes=this.sendTimes.filter(x=>now-x<1000);
      if(this.sendTimes.length>=MAX_AUTO_SENDS_PER_SECOND){
        // 觸發互相引發、無限循環時的保險：全部暫停，等玩家檢查設定。
        this.setPaused(true);
        this.notify(`自動指令一秒內超過 ${MAX_AUTO_SENDS_PER_SECOND} 個（${job.source}），已暫停全部觸發與計時器，請檢查設定後再按輸入欄左邊的按鈕恢復。`);
        return;
      }
      this.sendTimes.push(now);
      this.sendCommand(part);
    }
  }
  // 丟掉所有被 #wa 擋住、還沒送出的指令（斷線、暫停時）。
  cancelPending(){
    for(const job of this.pending)clearBg(job.timer);
    this.pending.clear();
  }

  // ---------- 計時器 ----------
  upsertTimer(t){
    const x=normalizeTimer(t);
    if(x.fireAt>x.seconds)throw new Error('「剩幾秒時執行」不能大於倒數秒數');
    const i=this.state.timers.findIndex(y=>y.id===x.id);
    if(i>=0)this.state.timers[i]=x;else this.state.timers.push(x);
    if(this.running.has(x.id))this.startTimer(x.id); // 改了設定就從頭開始倒數
    this.save();return x;
  }
  removeTimer(id){this.stopTimer(id);this.state.timers=this.state.timers.filter(t=>t.id!==id);this.save();}
  startTimer(id){
    this.running.set(id,{startedAt:Date.now(),fired:false});
    this.ensureTicking();this.emit();
  }
  stopTimer(id){
    this.running.delete(id);
    if(!this.running.size&&this.tickTimer){clearBg(this.tickTimer);this.tickTimer=null;}
    this.emit();
  }
  stopAllTimers(){for(const id of [...this.running.keys()])this.stopTimer(id);}
  remaining(id){
    const r=this.running.get(id),t=this.state.timers.find(x=>x.id===id);
    if(!r||!t)return null;
    return Math.max(0,t.seconds-(Date.now()-r.startedAt)/1000);
  }
  ensureTicking(){
    if(this.tickTimer)return;
    this.tickTimer=bgInterval(()=>this.tick(),TIMER_TICK_MS); // 網頁在背景也照常倒數
  }
  tick(){
    const now=Date.now();
    for(const [id,r] of [...this.running]){
      const t=this.state.timers.find(x=>x.id===id);
      if(!t){this.running.delete(id);continue;}
      const left=t.seconds-(now-r.startedAt)/1000;
      if(!r.fired&&left<=t.fireAt){
        r.fired=true;
        // 暫停時照常倒數，只是不送指令。
        if(!this.state.paused&&t.command)this.run(t.command,`計時器「${t.name||t.command}」`);
      }
      if(left<=0){
        if(t.loop){r.startedAt+=t.seconds*1000;r.fired=false;}
        else this.running.delete(id);
      }
    }
    if(!this.running.size&&this.tickTimer){clearBg(this.tickTimer);this.tickTimer=null;}
    this.emit();
  }
}

// ---------- 管理視窗 ----------
export function setupAutomationUI(auto,{dialog,toggleButton,openButtons}){
  if(!dialog)return;
  let tab='triggers';
  let editingTrigger=null,editingTimer=null;
  const $=s=>dialog.querySelector(s);

  function renderToggle(){
    if(!toggleButton)return;
    const paused=auto.state.paused;
    toggleButton.classList.toggle('is-paused',paused);
    toggleButton.textContent=paused?'暫停':'自動';
    const tr=auto.state.triggersEnabled?'開':'關';
    toggleButton.title=paused
      ? `自動功能已暫停（觸發與計時器都不送指令）。按一下恢復。`
      : `自動功能運作中（觸發：${tr}，#tr 可切換）。按一下全部暫停。`;
    toggleButton.setAttribute('aria-pressed',paused?'true':'false');
  }

  function renderTabs(){
    for(const b of dialog.querySelectorAll('[data-auto-tab]')){
      const on=b.dataset.autoTab===tab;
      b.classList.toggle('active',on);b.setAttribute('aria-selected',on?'true':'false');
    }
    $('#autoTriggerPane').hidden=tab!=='triggers';
    $('#autoTimerPane').hidden=tab!=='timers';
  }

  function renderTriggers(){
    $('#autoTriggersEnabled').checked=auto.state.triggersEnabled;
    const off=new Set(auto.state.disabledClasses);
    $('#autoClassList').innerHTML=auto.classes().map(c=>
      `<label class="auto-class"><input type="checkbox" data-auto-class="${esc(c)}"${off.has(c)?'':' checked'}> ${esc(c)}</label>`).join('')
      ||'<span class="auto-muted">尚無類別</span>';
    const rows=auto.state.triggers.map(t=>`<tr class="${t.enabled?'':'is-off'}">
      <td><input type="checkbox" data-trigger-enable="${t.id}"${t.enabled?' checked':''} aria-label="啟用"></td>
      <td class="auto-mono">${esc(t.pattern)}</td>
      <td class="auto-mono">${esc(t.command)}</td>
      <td>${esc(t.cls)}</td>
      <td class="auto-actions"><button type="button" data-trigger-edit="${t.id}">編輯</button><button type="button" data-trigger-del="${t.id}">刪除</button></td>
    </tr>`).join('');
    $('#autoTriggerRows').innerHTML=rows||'<tr><td colspan="5" class="auto-muted">尚未設定任何觸發。</td></tr>';
  }

  function fillTriggerForm(t){
    editingTrigger=t?.id||null;
    $('#trgPattern').value=t?.pattern||'';
    $('#trgCommand').value=t?.command||'';
    $('#trgClass').value=t?.cls||'';
    $('#trgEnabled').checked=t?t.enabled:true;
    $('#trgCase').checked=!!t?.caseSensitive;
    $('#trgRegex').checked=!!t?.regex;
    $('#trgPrompt').checked=!!t?.prompt;
    $('#trgSave').textContent=editingTrigger?'儲存修改':'新增觸發';
    $('#trgError').textContent='';
    $('#trgTestResult').textContent='';
  }

  function readTriggerForm(){
    return {id:editingTrigger||undefined,pattern:$('#trgPattern').value.trim(),command:$('#trgCommand').value.trim(),
      cls:$('#trgClass').value.trim(),enabled:$('#trgEnabled').checked,caseSensitive:$('#trgCase').checked,
      regex:$('#trgRegex').checked,prompt:$('#trgPrompt').checked};
  }

  function fmt(sec){
    const s=Math.ceil(sec);
    return s>=60?`${Math.floor(s/60)}:${String(s%60).padStart(2,'0')}`:`${s} 秒`;
  }
  function renderTimers(){
    const rows=auto.state.timers.map(t=>{
      const left=auto.remaining(t.id);
      const running=left!==null;
      return `<tr class="${running?'is-running':''}">
        <td>${esc(t.name||'—')}</td>
        <td>${t.seconds}</td>
        <td>${t.fireAt}</td>
        <td class="auto-mono">${esc(t.command)}</td>
        <td>${t.loop?'循環':'一次'}</td>
        <td class="auto-left" data-timer-left="${t.id}">${running?fmt(left):'—'}</td>
        <td class="auto-actions">
          <button type="button" data-timer-run="${t.id}">${running?'停止':'開始'}</button>
          <button type="button" data-timer-edit="${t.id}">編輯</button>
          <button type="button" data-timer-del="${t.id}">刪除</button>
        </td>
      </tr>`;}).join('');
    $('#autoTimerRows').innerHTML=rows||'<tr><td colspan="7" class="auto-muted">尚未設定任何計時器。</td></tr>';
  }
  // 倒數中只更新剩餘秒數，不重建整張表（避免打斷按鈕操作）。
  function refreshTimerCountdown(){
    for(const cell of dialog.querySelectorAll('[data-timer-left]')){
      const left=auto.remaining(cell.dataset.timerLeft);
      const text=left===null?'—':fmt(left);
      if(cell.textContent!==text)cell.textContent=text;
      const row=cell.closest('tr');
      const btn=row?.querySelector('[data-timer-run]');
      const label=left===null?'開始':'停止';
      if(btn&&btn.textContent!==label){btn.textContent=label;row.classList.toggle('is-running',left!==null);}
    }
  }

  function fillTimerForm(t){
    editingTimer=t?.id||null;
    $('#tmrName').value=t?.name||'';
    $('#tmrSeconds').value=t?.seconds??'';
    $('#tmrFireAt').value=t?.fireAt??0;
    $('#tmrCommand').value=t?.command||'';
    $('#tmrLoop').checked=!!t?.loop;
    $('#tmrSave').textContent=editingTimer?'儲存修改':'新增計時器';
    $('#tmrError').textContent='';
  }

  let lastStructure='';
  function render(){
    renderToggle();
    if(!dialog.open)return;
    // 結構（設定）有變才重建表格；只有倒數變化時只更新數字。
    const structure=JSON.stringify(auto.state)+'|'+[...auto.running.keys()].join(',');
    if(structure!==lastStructure){lastStructure=structure;renderTabs();renderTriggers();renderTimers();}
    else refreshTimerCountdown();
  }
  auto.onChange(render);

  function open(which){
    tab=which||tab;lastStructure='';
    if(!dialog.open)dialog.showModal();
    render();
  }
  for(const [btn,which] of openButtons||[])btn?.addEventListener('click',()=>open(which));
  toggleButton?.addEventListener('click',e=>{
    e.preventDefault();
    auto.setPaused(!auto.state.paused);
    auto.notify(auto.state.paused?'自動功能已暫停：觸發與計時器都不會送出指令。':'自動功能已恢復。');
  });

  dialog.addEventListener('click',e=>{
    const t=e.target instanceof Element?e.target:null;if(!t)return;
    const b=t.closest('button');
    if(b?.dataset.autoTab){tab=b.dataset.autoTab;lastStructure='';render();return;}
    if(b?.dataset.triggerEdit){fillTriggerForm(auto.state.triggers.find(x=>x.id===b.dataset.triggerEdit));$('#trgPattern').focus();return;}
    if(b?.dataset.triggerDel){
      const x=auto.state.triggers.find(y=>y.id===b.dataset.triggerDel);
      if(x&&confirm(`刪除觸發「${x.pattern}」？`)){auto.removeTrigger(x.id);if(editingTrigger===x.id)fillTriggerForm(null);}
      return;
    }
    if(b?.dataset.timerRun){const id=b.dataset.timerRun;if(auto.running.has(id))auto.stopTimer(id);else auto.startTimer(id);return;}
    if(b?.dataset.timerEdit){fillTimerForm(auto.state.timers.find(x=>x.id===b.dataset.timerEdit));$('#tmrSeconds').focus();return;}
    if(b?.dataset.timerDel){
      const x=auto.state.timers.find(y=>y.id===b.dataset.timerDel);
      if(x&&confirm(`刪除計時器「${x.name||x.command}」？`)){auto.removeTimer(x.id);if(editingTimer===x.id)fillTimerForm(null);}
      return;
    }
  });
  dialog.addEventListener('change',e=>{
    const t=e.target;
    if(t.dataset?.triggerEnable){
      const x=auto.state.triggers.find(y=>y.id===t.dataset.triggerEnable);
      if(x){x.enabled=t.checked;auto.save();}
    }else if(t.dataset?.autoClass!==undefined){
      auto.toggleClass(t.dataset.autoClass,t.checked);
    }else if(t.id==='autoTriggersEnabled'){
      auto.setTriggersEnabled(t.checked);
    }
  });

  $('#trgSave').addEventListener('click',()=>{
    const x=readTriggerForm();
    if(!x.pattern){$('#trgError').textContent='請輸入樣式。';return;}
    try{auto.upsertTrigger(x);fillTriggerForm(null);}
    catch(err){$('#trgError').textContent='樣式有誤：'+err.message;}
  });
  $('#trgNew').addEventListener('click',()=>fillTriggerForm(null));
  $('#trgTest').addEventListener('click',()=>{
    const x=readTriggerForm(),sample=$('#trgSample').value;
    try{
      const m=compilePattern(x.pattern,x).exec(sample);
      $('#trgTestResult').textContent=m
        ? `符合。會送出：${expandCommand(x.command,m)||'（沒有指令）'}${m.length>1?'　擷取：'+m.slice(1).map((v,i)=>`%${i+1}=${v}`).join('，'):''}`
        : '不符合。';
    }catch(err){$('#trgTestResult').textContent='樣式有誤：'+err.message;}
  });

  $('#tmrSave').addEventListener('click',()=>{
    const seconds=Number($('#tmrSeconds').value),fireAt=Number($('#tmrFireAt').value||0);
    if(!Number.isFinite(seconds)||seconds<1){$('#tmrError').textContent='倒數秒數至少 1 秒。';return;}
    if(!Number.isFinite(fireAt)||fireAt<0){$('#tmrError').textContent='「剩幾秒時執行」不能小於 0。';return;}
    if(!$('#tmrCommand').value.trim()){$('#tmrError').textContent='請輸入要執行的指令。';return;}
    try{
      auto.upsertTimer({id:editingTimer||undefined,name:$('#tmrName').value.trim(),seconds,fireAt,
        command:$('#tmrCommand').value.trim(),loop:$('#tmrLoop').checked});
      fillTimerForm(null);
    }catch(err){$('#tmrError').textContent=err.message;}
  });
  $('#tmrNew').addEventListener('click',()=>fillTimerForm(null));

  $('#autoExport').addEventListener('click',()=>{
    const a=document.createElement('a');
    const stamp=new Date().toISOString().slice(0,10);
    a.href=URL.createObjectURL(new Blob([auto.exportJSON()],{type:'application/json'}));
    a.download=`es2-triggers-timers-${stamp}.json`;
    document.body.appendChild(a);a.click();
    setTimeout(()=>{a.remove();URL.revokeObjectURL(a.href);},1000);
  });
  const fileInput=$('#autoImportFile');
  $('#autoImport').addEventListener('click',()=>fileInput.click());
  fileInput.addEventListener('change',async()=>{
    const f=fileInput.files?.[0];fileInput.value='';
    if(!f)return;
    if(!confirm('匯入會取代目前所有的觸發與計時器設定，確定嗎？'))return;
    try{
      const r=auto.importJSON(await f.text());
      auto.notify(`已匯入 ${r.triggers} 個觸發、${r.timers} 個計時器。`);
    }catch(err){alert('匯入失敗：'+err.message);}
  });

  fillTriggerForm(null);fillTimerForm(null);renderToggle();
  return {open};
}

import {SessionRecorder} from './session_recorder.js';
import {PlayerStateObserver} from './player_state.js';

const sessionRecorder = new SessionRecorder();
const observer = new PlayerStateObserver();
const term = document.querySelector('#terminal');
const input = document.querySelector('#command');
const conn = document.querySelector('#conn');
const landing = document.querySelector('#landing');
const gameApp = document.querySelector('#gameApp');

let ws = null;
let started = false;
let history = [];
let hi = 0;
let retry = 0;
let tail = '';
let graph = {nodes:[], edges:[]};
let nodeById = new Map();
let labelIndex = new Map();
let adjacency = new Map();
let currentRoomId = null;
let mapBootstrapRetryTimer=null;
let lastMissingMapRoomId='';
let hudTimer = null;
let hudPollInFlight = false;
let lastUserCommandAt = 0;
let hudKickTimer = null;
let hudResponseTimer = null;
let hudPollBuffer = '';
let hudPollStartedAt = 0;
let pendingUserCommands = [];
let lastReceiveAt = 0;
let welcomeStyled = false;
let welcomeBuffer = '';
let mapRefreshPending = false;
let hudBootstrapInFlight = false;
let hudBootstrapAttempts = 0;
const HUD_POLL_MS = 800;
const HUD_USER_GRACE_MS = 350;
const HUD_KICK_DELAY_MS = 20;
const HUD_POLL_TIMEOUT_MS = 1200;
const HUD_ACTION_FLUSH_MS = 180;

const esc = s => String(s).replace(/[&<>\"]/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','\"':'&quot;'}[c]));
const baseColors = {
  30:'#707770',31:'#ff7474',32:'#65df8b',33:'#efd06b',34:'#76a9ff',35:'#d98df0',36:'#69dbe5',37:'#e5ece7',
  90:'#8e978f',91:'#ff9999',92:'#8be9a6',93:'#f4dc8c',94:'#9bc0ff',95:'#e6abf5',96:'#93edf3',97:'#ffffff'
};
const bgColors = {40:'#090b0a',41:'#532020',42:'#1d4d2e',43:'#4e4219',44:'#1c3150',45:'#47244d',46:'#17464a',47:'#d7ddd9'};


const contextTitle=document.getElementById('contextTitle');
const contextBody=document.getElementById('contextBody');
let contextState={room:'',people:[],items:[],combat:null,inventory:[]};
let contextRoomScan=false;
let chatView='chat';
let chatParseBuffer='';
const chatMessages={chat:[],tell:[]};
const CHAT_LOG_LIMIT=200;
const contextChatLog=document.getElementById('contextChatLog');
function renderChatLog(){
  if(!contextChatLog)return;
  const rows=chatMessages[chatView]||[];
  contextChatLog.innerHTML=rows.length
    ? rows.map(x=>`<div class="context-chat-message ${chatView==='tell'?'is-tell':'is-chat'}">${x.html}</div>`).join('')
    : `<div class="context-chat-empty">尚無 ${chatView.toUpperCase()} 訊息。</div>`;
  contextChatLog.scrollTop=contextChatLog.scrollHeight;
}
function setupChatTabs(){
  for(const btn of document.querySelectorAll('.context-chat-tab[data-chat-tab]')){
    btn.addEventListener('click',()=>{
      chatView=btn.dataset.chatTab==='tell'?'tell':'chat';
      for(const x of document.querySelectorAll('.context-chat-tab[data-chat-tab]')){
        const on=x.dataset.chatTab===chatView;
        x.classList.toggle('active',on);
        x.setAttribute('aria-selected',on?'true':'false');
      }
      renderChatLog();
    });
  }
}
function extractChatMessage(plain){
  let text=String(plain||'').trim();
  if(!text)return null;

  // Channel output can arrive while the telnet prompt is still on the same
  // physical line.  Do not require the CHAT/TELL marker to be column zero.
  const chatAt=text.indexOf('【閒聊】');
  if(chatAt>=0)return {kind:'chat',text:text.slice(chatAt).trim()};

  // Remove only browser/telnet prompt debris.  Incoming tells may otherwise be
  // prefixed by the prompt and were previously missed because the parser used
  // start-anchored regular expressions.
  text=text.replace(/^(?:[>＞]\s*)+/,'').trim();
  if(!text)return null;

  if(/^你告訴.+[：﹕:]/.test(text))return {kind:'tell',text};
  if(/^你回答.+[：﹕:]/.test(text))return {kind:'tell',text};
  if(/告訴你[：﹕:]/.test(text))return {kind:'tell',text};
  if(/回答你[：﹕:]/.test(text))return {kind:'tell',text};
  return null;
}
function captureChatMessages(raw){
  chatParseBuffer+=String(raw);
  const parts=chatParseBuffer.split(/\r\n|\n|\r/);
  chatParseBuffer=parts.pop()||'';
  for(const line of parts){
    const plain=cleanText(line).trim();
    if(!plain)continue;
    const hit=extractChatMessage(plain);
    if(!hit)continue;
    // Render normalized text rather than the whole transport line, otherwise a
    // leading command prompt becomes part of the chat history.  CHAT/TELL have
    // their own pane colors, so ANSI preservation is unnecessary here.
    chatMessages[hit.kind].push({html:esc(hit.text)});
    if(chatMessages[hit.kind].length>CHAT_LOG_LIMIT)chatMessages[hit.kind].splice(0,chatMessages[hit.kind].length-CHAT_LOG_LIMIT);
    if(chatView===hit.kind)renderChatLog();
  }
}
setupChatTabs();
renderChatLog();
function escContext(s){return String(s).replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));}
function combatStat(label,cur,max,sideKey){
  const pct=max>0?Math.max(0,Math.min(100,cur*100/max)):0;
  const segments=10;
  const lit=Math.max(0,Math.min(segments,Math.ceil(pct/100*segments)));
  const blocks=Array.from({length:segments},(_,i)=>`<i class="${i<lit?'on':''}"></i>`).join('');
  return `<div class="context-combat-stat ${sideKey}"><div class="context-combat-stat-head"><span>${label}</span></div><div class="context-combat-segments" aria-label="${label} ${lit}/${segments}格">${blocks}</div></div>`;
}
function combatCard(side,sideKey){
  if(!side)return `<div class="context-combat-card ${sideKey} context-combat-empty"></div>`;
  return `<div class="context-combat-card ${sideKey}"><strong>${escContext(side.name)}</strong>${combatStat('形體',side.hp,side.hpmax,sideKey)}${combatStat('精',side.gin,side.ginmax,sideKey)}${combatStat('氣',side.kee,side.keemax,sideKey)}${combatStat('神',side.sen,side.senmax,sideKey)}</div>`;
}
function itemActionLabel(action,equipped){
  if(equipped)return '已裝備';
  return ({eat:'吃',drink:'飲用',study:'研讀'})[action]||'';
}
function inventoryPanel(){
  const items=(contextState.inventory||[]).filter(it=>['eat','drink','study'].includes(it.action));
  const rows=items.slice(0,24).map(it=>{
    const label=itemActionLabel(it.action,it.equipped);
    const button=label?`<button type="button" class="context-item-action" data-command="${escContext(it.command)}">${label}</button>`:'';
    return `<div class="context-inventory-row"><span class="context-inventory-name">${escContext(it.name)}</span>${button}</div>`;
  });
  return `<div class="context-inventory"><div class="context-section-title">可使用道具</div>${rows.length?rows.join(''):'<div class="context-empty">目前沒有可直接使用的道具。</div>'}</div>`;
}
function bindCommandButtons(root){
  if(!root||root.dataset.commandDelegated==='1')return;
  root.dataset.commandDelegated='1';
  root.addEventListener('click',e=>{
    const btn=e.target.closest('.context-item-action[data-command]');
    if(!btn||!root.contains(btn))return;
    e.preventDefault();
    e.stopPropagation();
    const command=btn.dataset.command||'';
    if(!command)return;
    // Stable delegated handler: renderContext() replaces innerHTML frequently.
    // innerHTML frequently, so listen on the persistent panel instead of
    // relying on handlers attached to transient button nodes.
    send(command);
    if(input){input.value='';input.focus();}
  });
}
function bindContextActions(){bindCommandButtons(contextBody);}
function renderContext(){
  if(!contextBody)return;
  let primary='';
  if(contextState.combat?.target){
    contextTitle.textContent='戰鬥狀態';
    primary=`<div class="context-combat-grid">${combatCard(contextState.combat.self,'is-self')}<div class="context-vs">VS</div>${combatCard(contextState.combat.target,'is-target')}</div>`;
  }else{
    contextTitle.textContent='可使用道具';
    primary='';
  }
  contextBody.innerHTML=primary+inventoryPanel();
  bindContextActions();
}
function observeContext(raw){
  // Context parsing uses plain text only. ANSI/control sequences remain available to the terminal renderer,
  // but are stripped here and non-room command output is never scanned as room entities.
  const text=cleanText(String(raw));
  const lines=text.split(/\r?\n/);
  for(const rawLine of lines){
    const line=rawLine.trim();
    if(!line)continue;
    if(line.startsWith('@@WEBHUD|'))continue;
    if(/^>\s*$/.test(line)){contextRoomScan=false;continue;}
    const m=line.match(/^([^<>]{1,24})\s+-\s*$/);
    if(m&&!/^(ES2|HTTP|WebMUD)/i.test(m[1])){
      contextState={...contextState,room:m[1].trim(),people:[],items:[]};
      contextRoomScan=true;
      continue;
    }
    if(!contextRoomScan)continue;
    // Only entity lines belonging to the active room description are eligible.
    const e=line.match(/^(.{1,40})\s+\(([^()]{1,40})\)\s*$/);
    if(e){
      const label=e[1].trim();
      if(/箱|劍|刀|衣|帽|瓶|石|鍋|包|棍|杖|槍|斧|鞋|甲|戒|符|藥|錢|金|杯|碗|壺/.test(label)){if(!contextState.items.includes(label))contextState.items.push(label);}
      else if(!contextState.people.includes(label))contextState.people.push(label);
    }
  }
  renderContext();
}
function parseWebHud(raw){
  for(const line of cleanText(String(raw)).split(/\r?\n/)){
    if(!line.startsWith('@@WEBHUD|'))continue;
    const a=line.split('|');
    if(a[1]==='ROOM'&&a.length>=3){beginRuntimeRoomSnapshot(a[2],a[3]||a[2]);continue;}
    if(a[1]==='MAPMETA'&&a.length>=3){setRoomMapMeta(a[2],a[3]||'',a[4]||'',a[5]||'');continue;}
    if(a[1]==='EXIT'&&a.length>=5){mergeRuntimeExit(a[2],a[3],a[4],a[5]||'');continue;}
    if(a[1]==='END'){finalizeRuntimeRoomSnapshot();continue;}
    if(a[1]==='INVBEGIN'){contextState.inventory=[];continue;}
    if(a[1]==='ITEM'&&a.length>=7){
      contextState.inventory.push({name:a[2],id:a[3],action:a[4],command:a[5],equipped:a[6]==='1'});
      continue;
    }
    if(a[1]==='INVEND'){renderContext();continue;}
    if(a[1]==='NONE'){contextState.combat=null;renderContext();continue;}
    if(a.length<12)continue;
    const side={name:a[2],hp:+a[4],hpmax:+a[5],gin:+a[6],ginmax:+a[7],kee:+a[8],keemax:+a[9],sen:+a[10],senmax:+a[11]};
    if(a[1]==='SELF'){
      // The silent LPC HUD feed is also the browser side-panel source, so the
      // role status no longer waits for the player to type hp/score manually.
      observer.state.vitals.hp={current:side.hp,limit:side.hpmax,limitKind:'effective'};
      observer.state.vitals.jing={current:side.gin,limit:side.ginmax,limitKind:'effective'};
      observer.state.vitals.qi={current:side.kee,limit:side.keemax,limitKind:'effective'};
      observer.state.vitals.shen={current:side.sen,limit:side.senmax,limitKind:'effective'};
      if(a.length>=19){
        observer.state.score.level=+a[12];
        observer.state.vitals.food={current:+a[13],limit:+a[14],limitKind:'maximum'};
        observer.state.vitals.water={current:+a[15],limit:+a[16],limitKind:'maximum'};
        observer.state.vitals.fatigue={current:+a[17],limit:+a[18],limitKind:'maximum'};
      }
      renderObserved();
    }
    contextState.combat ||= {self:null,target:null};
    if(a[1]==='SELF')contextState.combat.self=side;
    if(a[1]==='TARGET')contextState.combat.target=side;
    renderContext();
  }
}
renderContext();

function xterm256(n){
  n=Number(n);
  if(n<16){
    const fallback=['#000','#800000','#008000','#808000','#000080','#800080','#008080','#c0c0c0','#808080','#ff0000','#00ff00','#ffff00','#0000ff','#ff00ff','#00ffff','#fff'];
    return fallback[n] || '';
  }
  if(n>=232){const v=8+(n-232)*10;return `rgb(${v},${v},${v})`;}
  n-=16;const r=Math.floor(n/36),g=Math.floor((n%36)/6),b=n%6;const cv=i=>i===0?0:55+i*40;
  return `rgb(${cv(r)},${cv(g)},${cv(b)})`;
}
function terminalSafe(s){
  return String(s)
    .replace(/\x1b\][^\x07]*(?:\x07|\x1b\\)/g,'')
    .replace(/\x1b[78]/g,'')
    .replace(/\x1b\[[0-?]*[ -\/]*[@-~]/g,m=>m.endsWith('m')?m:'');
}
function ansi(s){
  s=terminalSafe(s);
  let html='',last=0,open=false,bold=false,underline=false,fg='',bg='';
  const re=/\x1b\[([0-9;]*)m/g;let m;
  const close=()=>{if(open){html+='</span>';open=false;}};
  while((m=re.exec(s))){
    html+=esc(s.slice(last,m.index));close();
    const cs=(m[1]||'0').split(';').filter(x=>x!=='').map(Number);if(!cs.length)cs.push(0);
    for(let i=0;i<cs.length;i++){
      const c=cs[i];
      if(c===0){bold=false;underline=false;fg='';bg='';}
      else if(c===1)bold=true;
      else if(c===4)underline=true;
      else if(c===22)bold=false;
      else if(c===24)underline=false;
      else if(c===39)fg='';
      else if(c===49)bg='';
      else if(baseColors[c])fg=baseColors[c];
      else if(bgColors[c])bg=bgColors[c];
      else if((c===38||c===48) && cs[i+1]===5 && Number.isFinite(cs[i+2])){const col=xterm256(cs[i+2]);if(c===38)fg=col;else bg=col;i+=2;}
    }
    const st=(bold?'font-weight:700;':'')+(underline?'text-decoration:underline;':'')+(fg?`color:${fg};`:'')+(bg?`background:${bg};`:'');
    if(st){html+=`<span style="${st}">`;open=true;}
    last=re.lastIndex;
  }
  html+=esc(s.slice(last));close();return html;
}
function cleanText(s){return terminalSafe(String(s)).replace(/\x1b\[[0-9;]*m/g,'').replace(/\r/g,'');}

const passwordPrompts=['請輸入密碼:','請設定您的密碼:','請重設您的密碼:','請再輸入一次您的密碼﹐以確認您沒記錯:','您兩次輸入的密碼並不一樣﹐請重新設定一次密碼:'];
function updateInputMode(chunk){
  tail=(tail+cleanText(chunk)).slice(-700);
  const secret=passwordPrompts.some(x=>tail.includes(x));
  input.type=secret?'password':'text';input.autocomplete=secret?'current-password':'off';
  const mode=document.querySelector('#inputMode');if(mode){mode.textContent=secret?'密碼輸入':'指令輸入';mode.classList.toggle('secret',secret);}
}

function classifyLine(line){
  const plain=cleanText(line).trim();
  if(!plain)return '';
  if(isRoomLabel(plain))return 'room-line';
  if(/^出口\s*[:：]/.test(plain)||/明顯的出口|唯一的出口/.test(plain))return 'exit-line';
  if(/受了傷|受到.*傷害|受傷|擊中|砍中|刺中|轟中|死亡|死了|斃命/.test(plain))return 'combat-hot';
  if(/經脈|內力|真氣|氣血|恢復|療傷/.test(plain))return 'combat-cool';
  if(/施展|神功|內功|招式|劍法|刀法|掌法/.test(plain))return 'system-highlight';
  return '';
}
function compactGameOutput(s){
  // Keep deliberate paragraph spacing, but prevent MUD output from turning repeated
  // empty lines into large blank vertical gaps in the browser terminal.
  let out=String(s).replace(/(?:\r?\n[ \t]*){3,}/g,'\n\n');
  // Once login is complete, the classic standalone MUD prompt is redundant because
  // WebMUD already has a command input box. Remove it regardless of current room state.
  if(welcomeStyled)out=out.replace(/(^|\r?\n)[ \t]*>[ \t]*(?=\r?\n|$)/g,'$1');
  return out;
}
function renderChunk(s){
  const parts=compactGameOutput(s).split(/(\r\n|\n|\r)/);let out='';
  for(let i=0;i<parts.length;i++){
    const p=parts[i];
    if(p==='\n'||p==='\r'||p==='\r\n'){out+='<br>';continue;}
    if(!p)continue;
    const cls=classifyLine(p);out+=cls?`<span class="${cls}">${ansi(p)}</span>`:ansi(p);
  }
  return out;
}
function shouldStick(){return term.scrollHeight-term.scrollTop-term.clientHeight<90;}
function hpLineKind(line){
  const p=cleanText(line).trim();
  if(!p)return 'blank';
  if(/^>\s*hp\s*$/i.test(p)||/^hp\s*$/i.test(p))return 'command';
  if(/^>\s*$/.test(p))return 'prompt';
  let hits=0;
  for(const label of ['形體','精','氣','神','食物','飲水','疲勞']){
    if(new RegExp(label+'\\s*-?\\d+\\s*\\/\\s*-?\\d+').test(p))hits++;
  }
  return hits>=2?'summary':'other';
}
function isHpSummaryLine(line){
  return hpLineKind(line)==='summary';
}
// Strip @@WEBHUD|...| lines out of a buffer, keeping only real text.
function stripWebHudLines(whole){
  return String(whole).split(/\r\n|\n|\r/).filter(line=>{
    const plain=cleanText(line).trim();
    if(!plain)return false;
    if(/^@@WEBHUD\|/.test(plain))return false;
    if(/^>\s*$/.test(plain))return false;
    if(/^webhud$/i.test(plain))return false;
    return true;
  });
}
function consumeHudPollOutput(s){
  if(!hudPollInFlight){
    // Defensive fallback: a @@WEBHUD block can still arrive here if the
    // client's poll already timed out (hudPollInFlight reset) before this
    // — now late — server response landed. These lines must never be shown
    // as visible game text regardless of polling state, so still recognise
    // and swallow a complete BEGIN..END block even when unexpected.
    const str=String(s);
    if(str.includes('@@WEBHUD|BEGIN') && /(?:^|\n)@@WEBHUD\|END(?:\n|$)/.test(cleanText(str))){
      parseWebHud(str);
      const kept=stripWebHudLines(str);
      return {visible:kept.length?kept.join('\n')+'\n':'',done:true};
    }
    return {visible:str,done:false};
  }
  hudPollBuffer += String(s);
  parseWebHud(hudPollBuffer);
  const clean=cleanText(hudPollBuffer);
  const hasEnd=/(?:^|\n)@@WEBHUD\|END(?:\n|$)/.test(clean);
  const timedOut=Date.now()-hudPollStartedAt>HUD_POLL_TIMEOUT_MS;
  if(!hasEnd && !timedOut)return {visible:'',done:false};
  const whole=hudPollBuffer;
  hudPollInFlight=false;hudBootstrapInFlight=false;hudPollBuffer='';hudPollStartedAt=0;
  if(hudResponseTimer){clearTimeout(hudResponseTimer);hudResponseTimer=null;}
  flushPendingUserCommands();
  const kept=stripWebHudLines(whole);
  // HUD polling is a silent transport. Internal payload/prompt whitespace must never
  // create a visible terminal line. Real asynchronous text is still preserved.
  return {visible:kept.length?kept.join('\n')+'\n':'',done:true};
}
function hudPollReady(force=false,allowNoRoom=false){
  if((!currentRoomId&&!allowNoRoom)||input.type==='password'||ws?.readyState!==1||hudPollInFlight)return false;
  // Real player input has priority over internal HUD telemetry.
  if(!force && Date.now()-lastUserCommandAt<HUD_USER_GRACE_MS)return false;
  // HUD must continue updating during combat even when no classic ">" prompt is emitted.
  // Only hold polling while the newest server text is an interactive login/choice prompt.
  const recent=tail.trim().split('\n').slice(-2).join(' ').slice(-220);
  if(/請輸入(?:選項|.*數字)|請輸入\s*Y\s*或\s*N|密碼|是否.*[？?]|確定嗎/.test(recent))return false;
  return true;
}
function pollHud(force=false,allowNoRoom=false){
  if(!hudPollReady(force,allowNoRoom))return false;
  observer.begin('hp','webhud');
  hudPollInFlight=true;
  hudPollBuffer='';
  hudPollStartedAt=Date.now();
  ws.send('webhud\r\n');
  if(allowNoRoom)hudBootstrapInFlight=true;
  if(hudResponseTimer)clearTimeout(hudResponseTimer);
  hudResponseTimer=setTimeout(()=>{
    hudResponseTimer=null;
    if(!hudPollInFlight)return;
    // Never let a missing/split HUD END marker hold real player clicks forever.
    hudPollInFlight=false;hudBootstrapInFlight=false;hudPollBuffer='';hudPollStartedAt=0;
    flushPendingUserCommands();
    if(!currentRoomId&&!exactRoomTrackingReady)scheduleMapBootstrapRetry(180);
  },HUD_POLL_TIMEOUT_MS);
  return true;
}
function startHudPolling(){
  if(hudTimer)return;
  hudTimer=setInterval(pollHud,HUD_POLL_MS);
  setTimeout(pollHud,120);
}
function stopHudPolling(){
  if(hudTimer){clearInterval(hudTimer);hudTimer=null;}
  if(hudKickTimer){clearTimeout(hudKickTimer);hudKickTimer=null;}
  if(hudResponseTimer){clearTimeout(hudResponseTimer);hudResponseTimer=null;}
  hudPollInFlight=false;hudPollBuffer='';hudPollStartedAt=0;
  pendingUserCommands=[];
}
function kickHudAfterServerText(force=false){
  if(hudKickTimer)clearTimeout(hudKickTimer);
  hudKickTimer=setTimeout(()=>{hudKickTimer=null;pollHud(force);},HUD_KICK_DELAY_MS);
}
function renderWelcomeIfPresent(s){
  if(welcomeStyled)return {html:'',rest:String(s),hold:false};
  welcomeBuffer+=String(s);
  const clean=cleanText(welcomeBuffer);
  const connected=/\[ES2 connected\]/i.test(clean);
  const prompt=/使用者代號|您的使用者代號|請輸入密碼/.exec(clean);
  const statusLines=clean.split(/\r?\n/).map(x=>x.trim()).filter(Boolean).filter(line=>
    /已經執行了|現在時間|目前共有/.test(line)
  ).map(line=>line.replace(/^東方故事(?:Ⅱ|II)?/, '東方故事'));
  const statusPanel=statusLines.length?`<div class="login-server-status" aria-label="伺服器狀態">${statusLines.map(line=>`<div>${escContext(line)}</div>`).join('')}</div>`:'';
  const card=`<div class="login-welcome login-welcome-art" aria-label="東方故事 II 天朝帝國 Celestial Empire">
    <img src="/login_title_v3185.png" alt="東方故事 II 天朝帝國 Celestial Empire" class="login-title-art">
    ${statusPanel}
  </div>`;

  // Browser presentation only. The canonical Neolith bytes are still received,
  // recorded and parsed; the original pre-login title block is hidden in WebMUD.
  // Do not depend on title spacing, ANSI, II/Ⅱ, source line, or TCP chunk boundaries.
  if(connected && !term.querySelector('.login-welcome-art')){
    const after=clean.replace(/^\s*\[ES2 connected\]\s*/i,'');
    welcomeBuffer=after;
    return {html:`<span class="sys">[ES2 connected]</span><br>${card}`,rest:'',hold:true};
  }
  if(prompt){
    welcomeStyled=true;
    const rest=clean.slice(prompt.index);
    welcomeBuffer='';
    return {html:term.querySelector('.login-welcome-art')?'':card,rest,hold:false};
  }
  if(welcomeBuffer.length>24000){
    welcomeStyled=true;
    const rest=welcomeBuffer;welcomeBuffer='';
    return {html:'',rest,hold:false};
  }
  return {html:'',rest:'',hold:true};
}
function print(s,system=false){
  const stick=shouldStick();
  lastReceiveAt=Date.now();
  if(!system){sessionRecorder.appendResponse(s);captureChatMessages(s);}
  observer.consume(s);renderObserved();updateInputMode(s);observeRoomText(s);bootstrapExactRoomFromOutput(s);

  let shown=String(s);
  let prefix='';
  if(!system){
    const welcome=renderWelcomeIfPresent(shown);
    prefix=welcome.html||'';shown=welcome.rest;
    if(welcome.hold)return;
    shown=consumeHudPollOutput(shown).visible;
  }
  if(prefix)term.insertAdjacentHTML('beforeend',prefix);
  if(shown)term.insertAdjacentHTML('beforeend',`<span class="${system?'sys':''}">${renderChunk(shown)}</span>`);
  if(stick)term.scrollTop=term.scrollHeight;
}

function parsePairFromState(key){
  // Silent webhud is the live source. Manual score output is only a fallback, never
  // allowed to override newer background vitals with stale values.
  const live=observer.state.vitals?.[key];if(live)return {current:live.current,max:live.limit};
  const detail=observer.state.scoreDetail?.stats?.[key];if(detail)return {current:detail.current,max:detail.maximum};
  return null;
}
function renderScoreHUD(){ renderObserved(); }

function renderObserved(){
  const labels={hp:'形體',jing:'精',qi:'氣',shen:'神',food:'食物',water:'飲水',fatigue:'疲勞'};
  const rows=[];
  for(const key of ['hp','jing','qi','shen','food','water','fatigue']){
    const v=parsePairFromState(key);if(!v)continue;
    const pct=v.max>0?Math.max(0,Math.min(100,Math.round(v.current*100/v.max))):0;
    const colors={hp:'#ef6262',jing:'#70c7ff',qi:'#70d99b',shen:'#b89cff',food:'#e9a45f',water:'#68b9e8',fatigue:'#8b9690'};
    const filled=Math.max(0,Math.min(10,Math.round(pct/10)));
    const segments=Array.from({length:10},(_,i)=>`<i class="hud-segment${i<filled?' filled':''}" aria-hidden="true"></i>`).join('');
    rows.push(`<div class="hudstat hud-${key}" style="--hud-color:${colors[key]}"><div><span>${labels[key]}</span><b>${v.current}/${v.max}</b></div><div class="hud-segments" role="img" aria-label="${labels[key]} ${pct}%">${segments}</div></div>`);
  }
  const hud=document.querySelector('#scoreHud');if(hud&&rows.length){hud.innerHTML=rows.join('');hud.classList.remove('muted');}
  const level=observer.state.scoreDetail?.level ?? observer.state.score?.level;
  const lev=document.querySelector('#levelHud');if(lev)lev.textContent=level!==undefined?`Lv.${level}`:'Lv.--';
}

const vec={north:[0,-1],south:[0,1],east:[1,0],west:[-1,0],northeast:[1,-1],northwest:[-1,-1],southeast:[1,1],southwest:[-1,1]};
const verticalDirs=new Set(['up','down']);
const exploredRooms=new Set();
const roomMapMeta=new Map();
let runtimeSnapshot=null;
let exactRoomTrackingReady=false;
const MAP_CACHE_KEY='es2.mapExplored.v7.readonlyworld';
const STATIC_WORLD_MAP=true;
let predictedRoomId=null;
let mapCacheSaveTimer=null;
// V7: localStorage may remember exploration only. The shipped Map DB is immutable.
function loadTopologyCache(){
  try{
    const raw=localStorage.getItem(MAP_CACHE_KEY);if(!raw)return;
    const cache=JSON.parse(raw);if(!cache||typeof cache!=='object')return;
    for(const id of cache.explored||[])if(nodeById.has(id))exploredRooms.add(id);
  }catch(_){/* ignore corrupt browser cache */}
}
function scheduleTopologyCacheSave(){
  clearTimeout(mapCacheSaveTimer);mapCacheSaveTimer=setTimeout(()=>{
    try{localStorage.setItem(MAP_CACHE_KEY,JSON.stringify({explored:[...exploredRooms]}));}
    catch(_){/* storage full/private mode */}
  },120);
}

function normalizeRoomLabel(s){return String(s).replace(/^【|】$/g,'').replace(/^\[|\]$/g,'').trim();}
function indexGraph(){
  nodeById=new Map(graph.nodes.map(n=>[n.id,n]));labelIndex=new Map();adjacency=new Map(graph.nodes.map(n=>[n.id,[]]));
  for(const n of graph.nodes){const key=normalizeRoomLabel(n.label);if(!labelIndex.has(key))labelIndex.set(key,[]);labelIndex.get(key).push(n.id);}
  for(const e of graph.edges){if(!e.resolved||!nodeById.has(e.from)||!nodeById.has(e.to))continue;adjacency.get(e.from)?.push(e);}
}
async function loadGraph(){
  try{
    // V7: the shipped DB owns room IDs, exits and coordinates. Runtime is read-only.
    const r=await fetch('/world_static_map.json',{cache:'no-store'});if(!r.ok)throw Error(String(r.status));graph=await r.json();
    indexGraph();loadTopologyCache();loadFixedWorldPositions();
    const layerHud=document.querySelector('#mapLayerHud');if(layerHud)layerHud.textContent='MAP V8 唯讀全圖｜自動定位';
    renderLocalMap();}
  catch(e){document.querySelector('#localMap').innerHTML='<div class="map-empty">固定世界地圖尚未建立</div>';}
}
function isRoomLabel(line){
  const text=normalizeRoomLabel(String(line).replace(/^\s+|\s+$/g,''));
  if(labelIndex.has(text))return true;
  for(const label of labelIndex.keys())if(text===label||text.startsWith(label+' '))return true;
  return false;
}
function roomCandidatesFromLine(line){
  const text=normalizeRoomLabel(cleanText(line).trim());const exact=labelIndex.get(text);if(exact)return exact;
  for(const [label,ids] of labelIndex){if(text===label||text.startsWith(label+' ')||text.startsWith('【'+label+'】'))return ids;}
  return [];
}
function chooseRoom(candidates){
  if(!candidates.length)return null;if(candidates.length===1)return candidates[0];
  if(currentRoomId){const near=new Set((adjacency.get(currentRoomId)||[]).map(e=>e.to));const hit=candidates.find(id=>near.has(id));if(hit)return hit;}
  return null;
}
function ensureRuntimeRoom(id,label){
  id=String(id||'').replace(/#\d+$/,'');if(!id)return null;
  // V7: runtime must never create, rename or otherwise mutate map rooms.
  return nodeById.has(id)?id:null;
}


function setRoomMapMeta(id,area,layer,mode){
  id=ensureRuntimeRoom(id,'');if(!id)return;
  roomMapMeta.set(id,{area:normalizeRoomLabel(area)||area||'',layer:normalizeRoomLabel(layer)||layer||'地面',mode:String(mode||'').toLowerCase()});
  scheduleTopologyCacheSave();
  if(id===currentRoomId&&!runtimeSnapshot)renderLocalMap();
}
function mapMeta(id){return roomMapMeta.get(id)||{area:'',layer:'地面',mode:''};}
function sameMapLayer(a,b){const ma=mapMeta(a),mb=roomMapMeta.get(b);return !mb||!ma.layer||!mb.layer||ma.layer===mb.layer;}

function beginRuntimeRoomSnapshot(id,label){
  const rawId=String(id||'').replace(/#\d+$/,'');
  id=ensureRuntimeRoom(rawId,label);
  if(!id){
    // A room path not present in the packaged DB must never permanently disable
    // bootstrap. Keep retrying telemetry, but do not mutate the read-only map.
    lastMissingMapRoomId=rawId;
    exactRoomTrackingReady=false;currentRoomId=null;predictedRoomId=null;hudBootstrapInFlight=false;
    renderLocalMap();scheduleMapBootstrapRetry();return;
  }
  // First exact ROOM path permanently disables room-name guessing. Duplicate room
  // names can never move the marker again.
  exactRoomTrackingReady=true;lastMissingMapRoomId='';
  runtimeSnapshot={id,old:''};
  const changed=id!==currentRoomId;
  currentRoomId=id;predictedRoomId=null;exploredRooms.add(id);
  hudBootstrapInFlight=false;hudBootstrapAttempts=0;
  if(changed)renderLocalMap();
  startHudPolling();
}
function finalizeRuntimeRoomSnapshot(){
  if(!runtimeSnapshot)return;runtimeSnapshot=null;
  scheduleTopologyCacheSave();
  // V5 deliberately does not rebuild or recalculate the map here. HUD completion
  // is telemetry only. The visible map has already moved synchronously on input.
}

function mergeRuntimeExit(from,direction,to,toLabel){
  // V7: WEBHUD exits are telemetry/validation only. The packaged Map DB is authoritative.
  from=String(from||'').replace(/#\d+$/,'');to=String(to||'').replace(/#\d+$/,'');
  direction=String(direction||'').toLowerCase();
  if(!nodeById.has(from)||!nodeById.has(to)||!direction)return false;
  return (adjacency.get(from)||[]).some(e=>e.direction===direction&&e.to===to);
}

function setExactRoom(id,label){
  const rawId=String(id||'').replace(/#\d+$/,'');
  id=ensureRuntimeRoom(rawId,label);if(!id){
    lastMissingMapRoomId=rawId;exactRoomTrackingReady=false;currentRoomId=null;renderLocalMap();scheduleMapBootstrapRetry();return;
  }
  exactRoomTrackingReady=true;lastMissingMapRoomId='';
  if(id!==currentRoomId){currentRoomId=id;exploredRooms.add(id);scheduleTopologyCacheSave();renderLocalMap();}
  const crt=document.querySelector('#consoleRoomTitle');if(crt)crt.textContent=safeMapLabel(label||nodeById.get(id)?.label||'')||'東方故事 II';
}
function looksLikeWorldRoomOutput(chunk){
  const text=cleanText(String(chunk||''));
  if(!text.trim())return false;
  // Examine a rolling receive window, not one WebSocket packet. Neolith may split
  // the room title and exit sentence across separate TCP/WebSocket chunks.
  if(/明顯的出口|唯一的出口|沒有明顯的出口|出口\s*[:：]/.test(text))return true;
  for(const raw of text.split(/\r?\n/)){
    const line=raw.trim();
    if(/^.{1,32}\s+-\s*(?:\/[^\s]+)?\s*$/.test(line) && !/ES2|WebMUD|HTTP/i.test(line))return true;
  }
  return false;
}
function scheduleMapBootstrapRetry(delay=180){
  if(currentRoomId||exactRoomTrackingReady||input.type==='password'||ws?.readyState!==1)return;
  if(mapBootstrapRetryTimer)return;
  mapBootstrapRetryTimer=setTimeout(()=>{
    mapBootstrapRetryTimer=null;
    if(currentRoomId||exactRoomTrackingReady||input.type==='password'||ws?.readyState!==1)return;
    if(!looksLikeWorldRoomOutput(tail))return;
    if(hudBootstrapAttempts>=8)hudBootstrapAttempts=0;
    hudBootstrapAttempts++;
    if(!pollHud(true,true))scheduleMapBootstrapRetry(220);
  },delay);
}
function bootstrapExactRoomFromOutput(chunk){
  if(currentRoomId||exactRoomTrackingReady||hudBootstrapInFlight)return;
  if(input.type==='password'||ws?.readyState!==1)return;
  // `tail` is updated immediately before this call. Using it makes bootstrap
  // immune to room output being fragmented across network packets.
  if(!looksLikeWorldRoomOutput(tail))return;
  scheduleMapBootstrapRetry(40);
}
function observeRoomText(chunk){
  if(!graph.nodes.length||exactRoomTrackingReady)return;
  // Login/bootstrap fallback only. Once WEBHUD has supplied an exact LPC room path,
  // ordinary room prose must never move the map marker. Duplicate names such as
  // 村間/小路 previously caused a false jump, then WEBHUD corrected it 1-2s later.
  for(const line of cleanText(chunk).split('\n')){
    const id=chooseRoom(roomCandidatesFromLine(line));
    if(id&&id!==currentRoomId){currentRoomId=id;renderLocalMap();startHudPolling();break;}
  }
}
function safeMapLabel(raw){
  const s=normalizeRoomLabel(String(raw||'')).trim();
  if(!s||s.includes('/')||/^\.?\.?\//.test(s)||/^[/\\]/.test(s)||/^[A-Za-z0-9_.:-]+$/.test(s))return '';
  return s;
}
function twoCharMapLabel(raw){
  let s=safeMapLabel(raw);if(!s)return '';
  const rules=[
    [/李記當舖|李記當鋪|李記商行/,'當鋪'],[/小旅店|小飯店|客棧|客栈/,'旅店'],[/雜貨舖|雜貨鋪|雜貨店/,'雜貨'],
    [/藥舖|藥鋪|药铺|藥店|药店/,'藥鋪'],[/村口大門|村口大门/,'村門'],[/廣場中央|广场中央/,'中央'],
    [/溪邊小路|溪边小路|河邊|河边/,'溪邊'],[/西瓜田/,'瓜田'],[/石子路|石磚路|石砖路/,'石路'],[/街道/,'街道'],
    [/農家|农家/,'農家'],[/私塾/,'私塾'],[/福祠/,'福祠'],[/獵戶|猎户/,'獵戶'],[/小溪|溪流/,'小溪'],[/廣場|广场/,'廣場'],
    [/錢莊|钱庄/,'錢莊'],[/武館|武馆/,'武館'],[/鐵舖|铁铺/,'鐵舖'],[/酒樓|酒楼/,'酒樓'],[/茶館|茶馆/,'茶館'],
    [/軍營|军营/,'軍營'],[/草棚/,'草棚'],[/七彩石/,'彩石'],[/老松林|松林/,'松林'],[/家園大廳|家园大厅|大廳|大厅/,'大廳'],
    [/寢室|寝室/,'寢室'],[/書房|书房/,'書房'],[/演武場|演武场/,'演武'],[/城門|城门/,'城門'],[/堡門|堡门/,'堡門'],
    [/雪亭堡/,'雪堡'],[/虎刀門|虎刀门/,'虎門'],[/寺|廟|庙/,'寺廟'],[/宮|宫/,'宮殿'],[/府/,'府邸'],[/莊|庄/,'山莊']
  ];
  for(const [re,label] of rules)if(re.test(s))return label;
  const chars=[...s.replace(/[\s　·・()（）【】\[\]]/g,'')];
  return chars.slice(0,2).join('');
}
function mapNodeClass(raw){return safeMapLabel(raw)?'map-node-special':'map-node-known';}
let mapZoom=1;
function setMapZoom(next){
  mapZoom=Math.max(.72,Math.min(1.45,next));
  const svg=document.querySelector('#localMap .topology-svg');if(svg)svg.style.transform=`scale(${mapZoom})`;
  const lab=document.querySelector('#mapZoomLabel');if(lab)lab.textContent=`${Math.round(mapZoom*100)}%`;
}
const stableWorldPos=new Map();
function loadFixedWorldPositions(){
  stableWorldPos.clear();
  for(const n of graph.nodes||[]){
    const x=Number(n?.x),y=Number(n?.y);
    if(n?.id&&Number.isFinite(x)&&Number.isFinite(y))stableWorldPos.set(n.id,[x,y]);
  }
  if(stableWorldPos.size!==nodeById.size)throw new Error('Map DB coordinates incomplete');
}

function renderLocalMap(){
  const el=document.querySelector('#localMap');if(!el)return;
  const layerHud=document.querySelector('#mapLayerHud'),trans=document.querySelector('#mapTransitions');
  if(!currentRoomId||!nodeById.has(currentRoomId)){
    const msg=lastMissingMapRoomId?`固定地圖未收錄此房：${esc(lastMissingMapRoomId)}`:'正在定位所在房間…';
    el.innerHTML=`<div class="map-empty">${msg}</div>`;if(trans)trans.hidden=true;return;
  }
  exploredRooms.add(currentRoomId);
  const meta=mapMeta(currentRoomId),center=stableWorldPos.get(currentRoomId)||[0,0],radius=3;
  if(layerHud)layerHud.textContent=`MAP V8 唯讀全圖 ｜ ${meta.area?meta.area+' ｜ ':''}${meta.layer||'地面'}`;
  const visible=new Map();
  for(const [id,p] of stableWorldPos){
    if(!nodeById.has(id)||!sameMapLayer(currentRoomId,id))continue;
    const dx=p[0]-center[0],dy=p[1]-center[1];if(Math.abs(dx)<=radius&&Math.abs(dy)<=radius)visible.set(id,[dx,dy]);
  }
  const NS='http://www.w3.org/2000/svg',W=360,H=314,cx=W/2,cy=H/2,sx=54,sy=46;
  const svg=document.createElementNS(NS,'svg');svg.setAttribute('viewBox',`0 0 ${W} ${H}`);svg.setAttribute('class','topology-svg');svg.style.transform=`scale(${mapZoom})`;
  const xy=(id)=>{const p=visible.get(id);return p?[cx+p[0]*sx,cy+p[1]*sy]:null;};
  const edgeSeen=new Set();
  for(const [from] of visible)for(const e of adjacency.get(from)||[]){
    if(!visible.has(e.to)||!vec[e.direction]||!sameMapLayer(currentRoomId,e.to))continue;const a=xy(from),b=xy(e.to);if(!a||!b)continue;
    const key=[from,e.to].sort().join('↔');if(edgeSeen.has(key))continue;edgeSeen.add(key);const line=document.createElementNS(NS,'line');
    line.setAttribute('x1',a[0]);line.setAttribute('y1',a[1]);line.setAttribute('x2',b[0]);line.setAttribute('y2',b[1]);line.setAttribute('class','map-edge'+((a[0]!==b[0]&&a[1]!==b[1])?' diagonal':''));svg.appendChild(line);
  }
  for(const [id] of visible){
    const [x,y]=xy(id),raw=nodeById.get(id)?.label||'',label=twoCharMapLabel(raw),g=document.createElementNS(NS,'g');
    const cls=id===currentRoomId?'map-node-current':mapNodeClass(raw);g.setAttribute('class',`map-node ${cls}`);
    // Two-character labels live inside a fixed-size room tile. This prevents labels
    // from colliding with neighbouring rooms and makes every visible room readable.
    const tileW=34,tileH=22;
    const r=document.createElementNS(NS,'rect');r.setAttribute('x',x-tileW/2);r.setAttribute('y',y-tileH/2);r.setAttribute('width',tileW);r.setAttribute('height',tileH);r.setAttribute('rx',3);r.setAttribute('class','map-node-rect');g.appendChild(r);
    if(label){const t=document.createElementNS(NS,'text');t.setAttribute('x',x);t.setAttribute('y',y+4);t.setAttribute('text-anchor','middle');t.setAttribute('class','map-node-label map-node-label-inside');t.textContent=label;g.appendChild(t);}
    if(id===currentRoomId){const dot=document.createElementNS(NS,'circle');dot.setAttribute('cx',x);dot.setAttribute('cy',y-7);dot.setAttribute('r',2.4);dot.setAttribute('class','map-current-dot');g.appendChild(dot);}svg.appendChild(g);
  }
  el.replaceChildren(svg);
  const vertical=(adjacency.get(currentRoomId)||[]).filter(e=>verticalDirs.has(e.direction)||!vec[e.direction]||!sameMapLayer(currentRoomId,e.to));
  if(trans){trans.replaceChildren();for(const e of vertical){const box=document.createElement('span');box.className='map-transition';const mark=e.direction==='up'?'▲':e.direction==='down'?'▼':'◇';const target=twoCharMapLabel(nodeById.get(e.to)?.label||'');box.innerHTML=`<b>${mark}</b> ${esc(e.direction)}${target?'：'+esc(target):''}`;trans.appendChild(box);}trans.hidden=!vertical.length;}
}



const directionAliases={n:'north',s:'south',e:'east',w:'west',ne:'northeast',nw:'northwest',se:'southeast',sw:'southwest',u:'up',d:'down'};
function movementDirection(command){
  const parts=String(command||'').trim().toLowerCase().split(/\s+/).filter(Boolean);if(!parts.length)return '';
  let dir=parts[0]==='go'?(parts[1]||''):parts[0];return directionAliases[dir]||dir;
}
function optimisticMapMove(command){
  if(!currentRoomId)return false;
  const dir=movementDirection(command);if(!dir)return false;
  const edge=(adjacency.get(currentRoomId)||[]).find(e=>String(e.direction||'').toLowerCase()===dir);
  if(!edge?.to||!nodeById.has(edge.to))return false;
  predictedRoomId=edge.to;currentRoomId=edge.to;exploredRooms.add(edge.to);scheduleTopologyCacheSave();renderLocalMap();
  const crt=document.querySelector('#consoleRoomTitle'),label=safeMapLabel(nodeById.get(edge.to)?.label||'');if(crt&&label)crt.textContent=label;
  return true;
}



function connect(){
  if(ws&&[WebSocket.OPEN,WebSocket.CONNECTING].includes(ws.readyState))return;
  conn.textContent='CONNECTING';const proto=location.protocol==='https:'?'wss':'ws';ws=new WebSocket(`${proto}://${location.host}/mud`);ws.binaryType='arraybuffer';
  ws.onopen=()=>{
    // A TCP/WebSocket reconnect starts at the Neolith login object, not inside
    // the previous room. Never let stale room/HUD state emit internal `webhud`
    // commands into the username/password prompts.
    stopHudPolling();
    if(mapBootstrapRetryTimer){clearTimeout(mapBootstrapRetryTimer);mapBootstrapRetryTimer=null;}
    currentRoomId=null;
    runtimeSnapshot=null;
    exactRoomTrackingReady=false;
    tail='';
    hudPollInFlight=false;
    hudPollBuffer='';
    hudPollStartedAt=0;
    pendingUserCommands=[];
    mapRefreshPending=false;hudBootstrapInFlight=false;hudBootstrapAttempts=0;
    retry=0;conn.textContent='LIVE';sessionRecorder.markTransportOpen();
  };
  ws.onmessage=e=>{
    const raw=e.data instanceof ArrayBuffer?new TextDecoder('utf-8').decode(e.data):e.data;
    observeContext(raw);print(raw);
    // A completed movement command must refresh ROOM/NAME/EXITS immediately. The
    // normal 350ms user-input grace remains for all other commands so telemetry
    // cannot compete with player input.
    if(currentRoomId && !String(raw).includes('@@WEBHUD|')){
      const forceMapRefresh=mapRefreshPending;
      if(forceMapRefresh)mapRefreshPending=false;
      kickHudAfterServerText(forceMapRefresh);
    }
  };
  ws.onclose=e=>{stopHudPolling();if(mapBootstrapRetryTimer){clearTimeout(mapBootstrapRetryTimer);mapBootstrapRetryTimer=null;}pendingUserCommands=[];mapRefreshPending=false;hudBootstrapInFlight=false;hudBootstrapAttempts=0;currentRoomId=null;runtimeSnapshot=null;tail='';sessionRecorder.finishResponse();sessionRecorder.markTransportClose(e?.code??null,e?.reason||'');sessionRecorder.markReconnect();conn.textContent='DISCONNECTED';if(!started)return;const wait=Math.min(10000,1000*2**Math.min(retry++,3));print(`\n[${wait/1000} 秒後重新連線]\n`,true);setTimeout(connect,wait);};
  ws.onerror=()=>conn.textContent='ERROR';
}
function transmitUserCommand(c,sensitive=false){
  const op=c.split(/\s+/)[0];
  if(!sensitive && /^(?:n|s|e|w|ne|nw|se|sw|u|d|north|south|east|west|northeast|northwest|southeast|southwest|up|down|go|enter|out)$/i.test(op)){
    // Catworld-style feel: move the marker immediately using already-known topology;
    // the silent HUD response that follows is authoritative and corrects it if needed.
    optimisticMapMove(c);mapRefreshPending=true;
  }
  if(!sensitive&&['score','hp','skills','inventory','look','go'].includes(op))observer.begin(op,c);
  sessionRecorder.beginCommand(c,{sensitive});
  ws.send(c+'\r\n');
  if(!sensitive&&c)history.push(c);
  hi=history.length;
  input.type='text';input.autocomplete='off';tail='';
}
function flushPendingUserCommands(){
  if(hudPollInFlight||ws?.readyState!==1||!pendingUserCommands.length)return;
  const queued=pendingUserCommands;
  pendingUserCommands=[];
  for(const item of queued)transmitUserCommand(item.command,item.sensitive);
}
function send(c){
  const sensitive=input.type==='password';c=String(c??'').trim();
  if(c){lastUserCommandAt=Date.now();if(hudKickTimer){clearTimeout(hudKickTimer);hudKickTimer=null;}}
  if(ws?.readyState!==1){print('\n[尚未連上 ES2]\n',true);return;}
  // The silent HUD request and a real player command must never share the same
  // Neolith command/response window. If a click arrives while `webhud` is in
  // flight, hold it for a few milliseconds and send it immediately after the
  // @@WEBHUD|END marker. This prevents interaction buttons from being swallowed
  // by the HUD parser or interleaved with the telemetry command.
  if(hudPollInFlight){
    if(!pendingUserCommands.some(x=>x.command===c&&x.sensitive===sensitive))
      pendingUserCommands.push({command:c,sensitive});
    // A HUD response is background telemetry. A real click must win quickly even
    // if the END marker is delayed/lost. Give the current HUD packet a very short
    // grace period, then release the queued player action.
    setTimeout(()=>{
      if(!pendingUserCommands.length)return;
      if(hudPollInFlight){
        hudPollInFlight=false;hudPollBuffer='';hudPollStartedAt=0;
        if(hudResponseTimer){clearTimeout(hudResponseTimer);hudResponseTimer=null;}
      }
      flushPendingUserCommands();
    },HUD_ACTION_FLUSH_MS);
    return;
  }
  transmitUserCommand(c,sensitive);
}

document.querySelector('#enterGame')?.addEventListener('click',async()=>{
  started=true;landing.classList.add('leaving');setTimeout(()=>{landing.hidden=true;gameApp.hidden=false;input.focus();},180);
  await loadGraph();connect();
});
document.querySelector('#form')?.addEventListener('submit',e=>{e.preventDefault();send(input.value);input.value='';input.focus();});

// Command focus hot-zone: the whole main console (the large transcript area plus
// the command bar background) acts as an easy target for returning to command
// entry after the player has clicked the map, status panel, chat, etc.  Real
// controls keep their own click behaviour; only non-interactive console space
// redirects focus to #command.
const consolePanel=document.querySelector('.console-panel');
consolePanel?.addEventListener('click',e=>{
  if(!input||input.disabled)return;
  const target=e.target instanceof Element?e.target:null;
  if(!target)return;
  if(target.closest('button,a,input,textarea,select,option,label,[contenteditable="true"],[role="button"]'))return;
  const selection=window.getSelection?.();
  if(selection&&String(selection).trim())return;
  try{input.focus({preventScroll:true});}catch(_){input.focus();}
});

// The padding/background of the command bar is part of the same hot-zone.  This
// explicit handler also covers browsers where a form/background click does not
// bubble as expected from nested layout elements.
document.querySelector('#form')?.addEventListener('click',e=>{
  if(!input||input.disabled)return;
  const target=e.target instanceof Element?e.target:null;
  if(target?.closest('button,input,textarea,select,option,label'))return;
  try{input.focus({preventScroll:true});}catch(_){input.focus();}
});
document.querySelectorAll('[data-cmd]').forEach(b=>b.addEventListener('click',()=>{send(b.dataset.cmd);input.focus();}));

document.querySelectorAll('[data-ui-focus]').forEach(b=>b.addEventListener('click',()=>{
  document.querySelectorAll('.nav-item').forEach(x=>x.classList.toggle('active',x===b));
  const target=b.dataset.uiFocus==='map'?document.querySelector('#mapPanel'):document.querySelector('#chatPanel');
  if(target){target.scrollIntoView({behavior:'smooth',block:'nearest'});target.classList.remove('ui-focus-flash');requestAnimationFrame(()=>target.classList.add('ui-focus-flash'));}
  input.focus();
}));
document.querySelectorAll('.nav-item[data-cmd]').forEach(b=>b.addEventListener('click',()=>{
  document.querySelectorAll('.nav-item').forEach(x=>x.classList.toggle('active',x===b));
}));
document.querySelector('[data-ui-settings]')?.addEventListener('click',()=>document.querySelector('#uiSettings')?.showModal());
document.querySelectorAll('[data-map-action]').forEach(b=>b.addEventListener('click',()=>{
  const a=b.dataset.mapAction;if(a==='in')setMapZoom(mapZoom+.12);else if(a==='out')setMapZoom(mapZoom-.12);else setMapZoom(1);
}));
const fontRange=document.querySelector('#terminalFontSize'),fontValue=document.querySelector('#terminalFontValue');
fontRange?.addEventListener('input',()=>{document.documentElement.style.setProperty('--terminal-font-size',fontRange.value+'px');if(fontValue)fontValue.textContent=fontRange.value+'px';localStorage.setItem('es2-ui-font',fontRange.value);});
const compactToggle=document.querySelector('#compactContext');compactToggle?.addEventListener('change',()=>{document.body.classList.toggle('context-compact',compactToggle.checked);localStorage.setItem('es2-ui-compact',compactToggle.checked?'1':'0');});
try{const f=localStorage.getItem('es2-ui-font');if(f&&fontRange){fontRange.value=f;document.documentElement.style.setProperty('--terminal-font-size',f+'px');if(fontValue)fontValue.textContent=f+'px';}const c=localStorage.getItem('es2-ui-compact')==='1';if(compactToggle){compactToggle.checked=c;document.body.classList.toggle('context-compact',c);}}catch(_){}



async function bootPreviewMode(){
  const p=new URLSearchParams(location.search);if(!p.has('preview'))return false;
  started=true;landing.hidden=true;gameApp.hidden=false;conn.textContent='PREVIEW';
  graph={nodes:[
    {id:'/preview/main',label:'中央大街'},{id:'/preview/wuguan',label:'武館'},{id:'/preview/yaopu',label:'藥舖'},{id:'/preview/qianzhuang',label:'錢莊'},{id:'/preview/kelou',label:'客棧'},{id:'/preview/nanjie',label:'南街'},{id:'/preview/xiaoxiang',label:'小巷'},{id:'/preview/caopeng',label:'草棚'},{id:'/preview/yingdi',label:'振武軍營'}
  ],edges:[]};indexGraph();
  const es=[['/preview/main','north','/preview/wuguan'],['/preview/wuguan','north','/preview/yaopu'],['/preview/main','east','/preview/qianzhuang'],['/preview/main','west','/preview/kelou'],['/preview/main','south','/preview/nanjie'],['/preview/qianzhuang','south','/preview/xiaoxiang'],['/preview/xiaoxiang','east','/preview/caopeng'],['/preview/caopeng','east','/preview/yingdi']];
  for(const [a,d,b] of es){mergeRuntimeExit(a,d,b,nodeById.get(b)?.label||'');const rev={north:'south',south:'north',east:'west',west:'east'}[d];mergeRuntimeExit(b,rev,a,nodeById.get(a)?.label||'');}
  setRoomMapMeta('/preview/main','雪亭','地面','');setExactRoom('/preview/main','中央大街');
  observer.state.vitals={hp:{current:176,limit:210},jing:{current:1296,limit:1296},qi:{current:1738,limit:1738},shen:{current:449,limit:449},food:{current:303,limit:551},water:{current:261,limit:429},fatigue:{current:0,limit:100}};observer.state.score={level:15};renderObserved();
  term.innerHTML='<span class="room-line">【雪亭・中央大街】</span><br>這是一條寬闊的青石大街，兩旁店舖林立，遠處可見城門與屋脊。<br><br><span class="exit-line">出口：北、南、東、西</span><br><br>一名往來的行人從街角走過。<br><br><span class="cmd">&gt; look</span><br>你仔細觀察四周，風裡帶著炊煙與木香。';
  document.querySelector('#contextTitle').textContent='中央大街';document.querySelector('#contextBody').innerHTML='<div class="context-line context-person">行人</div><div class="context-line context-item">街邊招牌</div><div class="context-line">東：錢莊　西：客棧　北：武館</div>';
  document.querySelector('#contextChatLog').innerHTML='<div class="context-line"><b>[CHAT]</b> 測試玩家：新版介面預覽。</div>';
  return true;
}
bootPreviewMode();

input?.addEventListener('keydown',e=>{
  if(e.key==='ArrowUp'){e.preventDefault();hi=Math.max(0,hi-1);input.value=history[hi]||'';}
  else if(e.key==='ArrowDown'){e.preventDefault();hi=Math.min(history.length,hi+1);input.value=history[hi]||'';}
});

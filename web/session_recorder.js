const DEFAULT_KEY='es2-session-recorder-v2';
// 長時間掛機時的上限：紀錄只保留最近的指令與回應，單筆回應也有長度上限，
// 否則 records / pending 會無限成長，每收到一段文字就把整份紀錄 JSON 化寫進
// sessionStorage，掛數小時後 CPU 與記憶體會越來越吃重。
const MAX_RECORDS=200;
const MAX_RESPONSE_CHARS=16*1024;
const APPEND_PERSIST_DELAY_MS=1000;

function capResponse(text){
  return text.length>MAX_RESPONSE_CHARS?text.slice(-MAX_RESPONSE_CHARS):text;
}
function clone(x){return JSON.parse(JSON.stringify(x))}
function safeStorage(storage){
  try{
    if(!storage)return null;
    const k='__es2_storage_probe__';
    storage.setItem(k,'1');
    storage.removeItem(k);
    return storage;
  }catch{return null}
}

export class SessionRecorder {
  constructor({storage=null,key=DEFAULT_KEY}={}){
    this.storage=safeStorage(storage ?? (typeof sessionStorage!=='undefined'?sessionStorage:null));
    this.key=key;
    this.persistTimer=null;
    if(!this.restore())this.reset();
  }
  snapshot(){
    return {
      format:'es2-browser-session-state-v2',
      startedAt:this.startedAt,
      sequence:this.sequence,
      reconnects:this.reconnects,
      records:this.records,
      pending:this.pending,
      events:this.events
    };
  }
  persist(){
    if(this.persistTimer){clearTimeout(this.persistTimer);this.persistTimer=null;}
    if(!this.storage)return;
    try{this.storage.setItem(this.key,JSON.stringify(this.snapshot()))}catch{}
  }
  restore(){
    if(!this.storage)return false;
    try{
      const raw=this.storage.getItem(this.key);
      if(!raw)return false;
      const x=JSON.parse(raw);
      if(x?.format!=='es2-browser-session-state-v2'||!Array.isArray(x.records)||!Array.isArray(x.events))return false;
      this.startedAt=x.startedAt||new Date().toISOString();
      this.sequence=Number(x.sequence||0);
      this.reconnects=Number(x.reconnects||0);
      this.records=x.records.slice(-MAX_RECORDS);
      this.pending=x.pending||null;
      this.events=x.events;
      return true;
    }catch{return false}
  }
  reset(){
    this.records=[];
    this.pending=null;
    this.events=[];
    this.sequence=0;
    this.startedAt=new Date().toISOString();
    this.reconnects=0;
    this.persist();
  }
  clear(){
    this.reset();
    if(this.storage){
      try{this.storage.removeItem(this.key)}catch{}
    }
  }
  event(kind,extra={}){
    const row={sequence:++this.sequence,kind,time:new Date().toISOString(),...extra};
    this.events.push(row);
    if(this.events.length>500)this.events=this.events.slice(-500);
    // 沒有對應指令的背景輸出（聊天、戰鬥訊息）很頻繁，合併寫入即可。
    if(kind==='ambient_output')this.schedulePersist();
    else this.persist();
    return row;
  }
  beginCommand(command,{sensitive=false}={}){
    if(sensitive){
      this.event('sensitive_input_redacted');
      return null;
    }
    if(this.pending)this.finishResponse('');
    const c=String(command||'').trim();
    if(!c)return null;
    this.pending={
      sequence:++this.sequence,
      command:c,
      response:'',
      startedAt:new Date().toISOString()
    };
    this.persist();
    return this.pending;
  }
  appendResponse(text){
    const x=String(text||'');
    if(!x)return;
    if(!this.pending){
      this.event('ambient_output',{bytes:new TextEncoder().encode(x).length});
      return;
    }
    this.pending.response=capResponse(this.pending.response+x);
    this.schedulePersist();
  }
  // 回應文字會一小段一小段持續進來，不必每段都整份寫入 storage；
  // 合併成約每秒一次。開始/結束指令、事件仍立即寫入。
  schedulePersist(){
    if(!this.storage||this.persistTimer)return;
    if(typeof setTimeout!=='function'){this.persist();return;}
    this.persistTimer=setTimeout(()=>{this.persistTimer=null;this.persist();},APPEND_PERSIST_DELAY_MS);
  }
  finishResponse(extra=''){
    if(!this.pending)return null;
    this.pending.response=capResponse(this.pending.response+String(extra||''));
    this.pending.finishedAt=new Date().toISOString();
    const row=this.pending;
    this.records.push(row);
    if(this.records.length>MAX_RECORDS)this.records=this.records.slice(-MAX_RECORDS);
    this.pending=null;
    this.persist();
    return row;
  }
  markTransportOpen(){this.event('transport_open')}
  markTransportClose(code=null,reason=''){this.event('transport_close',{code,reason:String(reason||'')})}
  markReconnect(){this.reconnects++;this.event('transport_reconnect_attempt',{count:this.reconnects})}
  rows({includePending=true}={}){
    const rows=this.records.map(clone);
    if(includePending&&this.pending){
      rows.push({...clone(this.pending),finishedAt:new Date().toISOString(),partial:true});
    }
    return rows;
  }
  toJSONL(){return this.rows().map(x=>JSON.stringify(x)).join('\n')}
  manifest(){
    const rows=this.rows({includePending:false});
    const ops=new Set(rows.map(r=>(r.command.split(/\s+/)[0]||'')));
    const eventKinds=new Set(this.events.map(e=>e.kind));
    return {
      format:'es2-browser-session-v2',
      startedAt:this.startedAt,
      generatedAt:new Date().toISOString(),
      records:rows.length,
      events:this.events.length,
      reconnects:this.reconnects,
      transport:{
        opened:eventKinds.has('transport_open'),
        closed:eventKinds.has('transport_close')
      },
      privacy:{
        sensitiveInputsStored:false,
        redactedEvents:this.events.filter(e=>e.kind==='sensitive_input_redacted').length
      },
      coverage:{
        score:ops.has('score'),
        hp:ops.has('hp'),
        skills:ops.has('skills'),
        inventory:ops.has('inventory'),
        look:ops.has('look'),
        movement:ops.has('go'),
        who:ops.has('who')
      }
    };
  }
}

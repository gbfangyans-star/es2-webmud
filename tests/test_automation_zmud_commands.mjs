import assert from 'node:assert/strict';
globalThis.localStorage={store:{},getItem(k){return this.store[k]??null;},setItem(k,v){this.store[k]=String(v);}};
const {Automation,splitCommandLine,parseWait}=await import('../web/automation.js');
const sleep=ms=>new Promise(r=>setTimeout(r,ms));

assert.deepEqual(splitCommandLine('#3 e;n; ;#2 #wa 10'),['e','e','e','n','#wa 10','#wa 10']);
assert.equal(parseWait('#wa'),1000);assert.equal(parseWait('#WAIT 250'),250);assert.equal(parseWait('#war'),null);

function make(){
  const log=[],notes=[];let connected=true,blocked=false;
  const a=new Automation({
    sendCommand:c=>log.push('auto:'+c),sendUserCommand:c=>log.push('user:'+c),notify:m=>notes.push(m),
    isBlocked:()=>blocked||!connected,
    disconnect:()=>{if(!connected)return false;connected=false;log.push('DIS');return true;},
    connect:()=>{if(connected)return false;connected=true;log.push('CON');return true;},
  });
  return {a,log,notes,setBlocked:v=>{blocked=v;}};
}

// #wa delays the rest of the chain, in order.
{const {a,log}=make();
 a.run('n;#wa 60;get all;s',null,{user:true});
 assert.deepEqual(log,['user:n']);
 await sleep(100);
 assert.deepEqual(log,['user:n','user:get all','user:s']);}

// 9-command cap counts real commands only; #3 repeats count.
{const {a,log,notes}=make();
 a.run('#wa 0;#5 e;#tr;#tr;#5 w',null,{user:true});
 await sleep(20);
 assert.equal(log.length,9);assert.ok(notes.includes('你的動作太快了...'));}

// #dis / #con, and chained reconnect after a wait.
{const {a,log,notes}=make();
 a.run('#dis;#dis;#wa 20;#con;#con;look',null,{user:true});
 assert.deepEqual(log,['DIS']);assert.ok(notes.includes('目前沒有連線。'));
 await sleep(60);
 assert.deepEqual(log,['DIS','CON','user:look']);assert.ok(notes.includes('已經連線中。'));}

// cancelPending and pause drop waiting commands.
{const {a,log}=make();
 a.run('e;#wa 30;w','trigger');a.cancelPending();
 a.run('e;#wa 30;w','trigger');a.setPaused(true);
 await sleep(60);
 assert.deepEqual(log,['auto:e','auto:e']);}

// Delayed parts respect isBlocked (password prompt / editor).
{const {a,log,setBlocked}=make();
 a.run('e;#wa 20;w',null,{user:true});setBlocked(true);
 await sleep(50);
 assert.deepEqual(log,['user:e']);}

// #t+ / #t- / #sh
{const {a,notes}=make();
 a.upsertTrigger({pattern:'x',command:'y',cls:'戰鬥'});
 a.run('#t- 戰鬥');assert.deepEqual(a.state.disabledClasses,['戰鬥']);
 a.run('#t+ 戰鬥');assert.deepEqual(a.state.disabledClasses,[]);
 a.run('#sh 哈囉');assert.ok(notes.includes('哈囉'));
 a.run('#t- 不存在');assert.ok(notes.some(m=>m.includes('沒有類別')));}

// Empty user line still sends a blank Enter; unknown # commands go to the server.
{const {a,log}=make();a.run('',null,{user:true});a.run('#foo',null,{user:true});
 assert.deepEqual(log,['user:','user:#foo']);}

console.log('automation zmud command tests passed');

// 背景也照常運作的計時器。
//
// 瀏覽器會放慢背景分頁（不在最上層、視窗縮小）的 setTimeout／setInterval：最快一秒一次，
// 在背景超過幾分鐘後 Chrome 甚至限制到約一分鐘一次，觸發、計時器、#wa 都會因此停擺。
// 改由 Web Worker（背景執行緒）計時，它不受這種限制，時間到了再通知網頁執行。
// 建立 Worker 失敗時（極舊的瀏覽器），自動退回一般的計時器。

let worker = null;
let seq = 0;
const callbacks = new Map();   // id -> {fn, repeat}

try {
  const src = `
    const timers = new Map();
    onmessage = e => {
      const {op, id, ms} = e.data;
      if (op === 'clear') { clearTimeout(timers.get(id)); clearInterval(timers.get(id)); timers.delete(id); return; }
      if (op === 'timeout') timers.set(id, setTimeout(() => { timers.delete(id); postMessage(id); }, ms));
      else if (op === 'interval') timers.set(id, setInterval(() => postMessage(id), ms));
    };`;
  const url = URL.createObjectURL(new Blob([src], {type: 'text/javascript'}));
  worker = new Worker(url);
  worker.onmessage = e => {
    const t = callbacks.get(e.data);
    if (!t) return;
    if (!t.repeat) callbacks.delete(e.data);
    try { t.fn(); } catch (err) { setTimeout(() => { throw err; }); }
  };
  worker.onerror = () => { worker = null; };
} catch (_) {
  worker = null;
}

function start(fn, ms, repeat) {
  ms = Math.max(0, Number(ms) || 0);
  if (!worker) {
    const id = repeat ? setInterval(fn, ms) : setTimeout(fn, ms);
    return {native: id, repeat};
  }
  const id = ++seq;
  callbacks.set(id, {fn, repeat});
  worker.postMessage({op: repeat ? 'interval' : 'timeout', id, ms});
  return {id};
}

export function bgTimeout(fn, ms) { return start(fn, ms, false); }
export function bgInterval(fn, ms) { return start(fn, ms, true); }
export function clearBg(handle) {
  if (!handle) return;
  if (handle.native !== undefined) { (handle.repeat ? clearInterval : clearTimeout)(handle.native); return; }
  callbacks.delete(handle.id);
  worker?.postMessage({op: 'clear', id: handle.id});
}

// 請瀏覽器不要凍結這個分頁：持有 Web Lock 的分頁，Chrome 不會在背景把它凍結。
// （記憶體節省模式仍可能把很久沒用的分頁整個卸載，那要在瀏覽器設定裡把網站加入「一律保持啟用」。）
export function keepPageAlive() {
  try {
    navigator.locks?.request('es2-webmud-keepalive', () => new Promise(() => {}));
  } catch (_) {}
}

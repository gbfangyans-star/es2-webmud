import assert from 'node:assert/strict';
import {AdminJobState} from '../server/admin_jobs.js';

const j=new AdminJobState(2);
const a=j.start('reindex',{x:1});
assert.equal(a.status,'running');
let busy=false;
try{j.start('reindex')}catch(e){busy=e.code==='JOB_BUSY' && e.job.id===a.id}
assert.equal(busy,true);
j.stage(a,'build_catalog');
j.finish(a,true,{result:'ok'});
assert.equal(j.snapshot().active.length,0);
assert.equal(j.snapshot().history[0].status,'succeeded');
const b=j.start('reindex');j.finish(b,false);
assert.equal(j.snapshot().history[0].status,'failed');
console.log('v2.3 admin single-flight tests passed');

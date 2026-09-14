export class AdminJobState {
  constructor(limit=20){
    this.limit=limit;
    this.seq=0;
    this.active=new Map();
    this.history=[];
  }
  start(kind,meta={}){
    if(this.active.has(kind)){
      const err=new Error(`${kind} already running`);
      err.code='JOB_BUSY';
      err.job=this.active.get(kind);
      throw err;
    }
    const job={id:`${kind}-${++this.seq}`,kind,status:'running',startedAt:new Date().toISOString(),stage:'start',...meta};
    this.active.set(kind,job);
    return job;
  }
  stage(job,stage,extra={}){
    if(!job || job.status!=='running')return job;
    job.stage=stage;Object.assign(job,extra);return job;
  }
  finish(job,ok,extra={}){
    if(!job)return null;
    job.status=ok?'succeeded':'failed';
    job.finishedAt=new Date().toISOString();
    Object.assign(job,extra);
    this.active.delete(job.kind);
    this.history.unshift({...job});
    this.history=this.history.slice(0,this.limit);
    return job;
  }
  snapshot(){
    return {active:[...this.active.values()].map(x=>({...x})),history:this.history.map(x=>({...x}))};
  }
}

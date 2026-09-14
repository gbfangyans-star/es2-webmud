// Minimal Telnet transport codec for browser sessions.
// This file handles protocol negotiation only. It contains no ES2 gameplay rules.
export const IAC=255, DONT=254, DO=253, WONT=252, WILL=251, SB=250, SE=240;
const OPT_ECHO=1, OPT_SGA=3, OPT_TTYPE=24, OPT_NAWS=31;

export class TelnetCodec {
  constructor(writeBack){
    this.writeBack=writeBack;
    this.state='data'; this.cmd=null; this.sbOpt=null; this.sb=[];
  }
  reject(cmd,opt){
    // We keep terminal policy conservative. ES2 remains authoritative.
    if(cmd===DO) this.writeBack(Buffer.from([IAC,WONT,opt]));
    else if(cmd===WILL) this.writeBack(Buffer.from([IAC,DONT,opt]));
  }
  feed(buf){
    const out=[];
    for(const b of buf){
      if(this.state==='data'){
        if(b===IAC)this.state='iac'; else out.push(b);
      } else if(this.state==='iac'){
        if(b===IAC){out.push(IAC);this.state='data'}
        else if([DO,DONT,WILL,WONT].includes(b)){this.cmd=b;this.state='opt'}
        else if(b===SB){this.state='sbopt'}
        else this.state='data';
      } else if(this.state==='opt'){
        // For browser bridge we reject option ownership cleanly instead of leaking IAC bytes.
        this.reject(this.cmd,b); this.state='data';
      } else if(this.state==='sbopt'){
        this.sbOpt=b;this.sb=[];this.state='sb';
      } else if(this.state==='sb'){
        if(b===IAC)this.state='sbiac'; else this.sb.push(b);
      } else if(this.state==='sbiac'){
        if(b===SE){this.state='data';this.sb=[]}
        else {this.sb.push(IAC,b);this.state='sb'}
      }
    }
    return Buffer.from(out);
  }
}

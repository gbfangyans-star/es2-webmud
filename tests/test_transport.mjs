import assert from 'node:assert/strict';
import {TelnetCodec,IAC,WILL,DO} from '../server/telnet.js';
const replies=[];const c=new TelnetCodec(b=>replies.push([...b]));
assert.equal(c.feed(Buffer.from([65,66,67])).toString(),'ABC');
assert.equal(c.feed(Buffer.from([65,IAC,WILL,1,66])).toString(),'AB');
assert.equal(c.feed(Buffer.from([IAC,DO,3])).length,0);
assert.ok(replies.length>=2);
console.log('telnet transport tests passed');

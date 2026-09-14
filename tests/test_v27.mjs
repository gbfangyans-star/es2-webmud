import assert from 'node:assert/strict';
import fs from 'node:fs';
import os from 'node:os';
import path from 'node:path';
import {execFileSync,spawnSync} from 'node:child_process';

const dir=fs.mkdtempSync(path.join(os.tmpdir(),'es2-v27-'));
const campaign=path.join(dir,'campaign.json'),plan=path.join(dir,'plan.json');
const c={
 format:'es2-validation-campaign-v1',
 campaignId:'campaign-js-1',
 projectVersion:'2.7.0',
 source:{commit:'a'.repeat(40),mudlibTreeSha256:'b'.repeat(64)}
};
fs.writeFileSync(campaign,JSON.stringify(c));
const tool=new URL('../tools/new_multiplayer_test_plan.mjs',import.meta.url).pathname;
execFileSync('node',[tool,'--out',plan,'--campaign',campaign],{stdio:'pipe'});
const p=JSON.parse(fs.readFileSync(plan,'utf8'));
assert.equal(p.campaignBinding.campaignId,'campaign-js-1');
assert.equal(p.campaignBinding.mudlibTreeSha256,'b'.repeat(64));
assert.ok(p.campaignBinding.campaignSha256);
console.log('v2.7 multiplayer provenance plan tests passed');

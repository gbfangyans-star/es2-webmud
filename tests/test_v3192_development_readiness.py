from pathlib import Path
import subprocess,sys,json
ROOT=Path(__file__).resolve().parents[1]
def test_version_consistency():
 version=(ROOT/'VERSION').read_text().strip()
 package=json.loads((ROOT/'server/package.json').read_text())
 assert version and package['version']==version
def test_readiness_is_source_only_and_nondestructive():
 s=(ROOT/'tools/development_readiness.py').read_text(encoding='utf-8')
 assert 'taedlar/es2_mudlib only' in s
 assert 'write_text' in s and 'DEVELOPMENT_READINESS.json' in s
 assert 'source/upstream/mudlib' not in s # constructed path, not alternate source
 assert 'unlink(' not in s and 'shutil' not in s
def test_launcher_exists(): assert (ROOT/'CHECK_DEVELOPMENT_READINESS.bat').exists()

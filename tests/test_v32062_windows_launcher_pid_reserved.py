from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PS = ROOT / "start_es2_internet_windows.ps1"

def test_launcher_does_not_bind_reserved_pid_variable():
    s = PS.read_text(encoding="utf-8-sig")
    assert "[int]$Pid" not in s
    assert "$pid=" not in s.lower()
    assert "[int]$ProcessId" in s
    assert "$listenerPid=$listener.OwningProcess" in s

def test_launcher_still_checks_listener_process_path():
    s = PS.read_text(encoding="utf-8-sig")
    assert "Get-ProcessPath $listener.OwningProcess" in s
    assert "Same-Path $listenerPath $neo" in s

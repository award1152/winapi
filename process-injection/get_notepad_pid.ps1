# get_notepad_pid.ps1

# Get the process ID of Notepad.exe
$notepadProcess = Get-Process -Name "notepad" -ErrorAction SilentlyContinue

# Check if Notepad.exe is running
if ($notepadProcess) {
    # Output the process ID as an integer
    Write-Output $notepadProcess.Id
} else {
    # If Notepad.exe is not running, output -1 or any other indicator
    Write-Output -1
}

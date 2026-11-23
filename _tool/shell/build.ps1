param([string]$Configuration = "Release")
& "$PSScriptRoot/../architecure_launcher/build.ps1" -Source "$PSScriptRoot/shell.cpp" -Name shell -Configuration $Configuration

param([string]$ToolRoot = (Resolve-Path "$PSScriptRoot/../../tool").Path,
      [string]$Configuration = "Release",
      [string]$Source = "$PSScriptRoot/launcher.cpp",
      [string]$Name = "architecture_launcher")
$ErrorActionPreference = 'Stop'
$vswhere = "${env:ProgramFiles(x86)}/Microsoft Visual Studio/Installer/vswhere.exe"
$installation = & $vswhere -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath
if (!$installation) { throw 'MSVC x86 tools are required' }
$build = Join-Path $env:TEMP ('architecture-launcher-' + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $build | Out-Null
$source = [IO.Path]::GetFullPath($Source)
$checkout = (Resolve-Path "$PSScriptRoot/../../../..").Path
$binary = Join-Path $checkout "../operating_system/storage-windows/x86/$Configuration/binary/$Name.exe"
New-Item -ItemType Directory -Force -Path (Split-Path $binary) | Out-Null
$batch = @"
@echo off
call "$installation\VC\Auxiliary\Build\vcvarsall.bat" x86 >nul
if errorlevel 1 exit /b %errorlevel%
cl /nologo /O1 /Oi /GS- /GR- /Zl /D_WIN32_WINNT=0x0501 /Fo"$build\launcher.obj" /Fe"$binary" "$source" /link /NODEFAULTLIB /ENTRY:launcher_main /SUBSYSTEM:WINDOWS,5.01 /MACHINE:X86 /INCREMENTAL:NO kernel32.lib user32.lib shell32.lib
exit /b %errorlevel%
"@
[IO.File]::WriteAllText("$build/build.cmd", $batch)
& cmd.exe /d /c "$build/build.cmd"
if ($LASTEXITCODE) { throw 'Architecture launcher compilation failed' }
New-Item -ItemType Directory -Force -Path "$ToolRoot/bin" | Out-Null
Copy-Item -LiteralPath $binary -Destination "$ToolRoot/bin/$Name.exe" -Force
Write-Output "Built $binary and deployed $ToolRoot/bin/$Name.exe"

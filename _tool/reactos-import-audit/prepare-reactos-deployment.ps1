param(
    [Parameter(Mandatory = $true)][string]$SourceDirectory,
    [Parameter(Mandatory = $true)][string]$DestinationDirectory,
    [string]$Objcopy = 'C:\mingw32\bin\objcopy.exe'
)
$ErrorActionPreference = 'Stop'
$source = (Resolve-Path -LiteralPath $SourceDirectory).Path.TrimEnd('\', '/')
$destination = [IO.Path]::GetFullPath($DestinationDirectory).TrimEnd('\', '/')
if ($source.Equals($destination, [StringComparison]::OrdinalIgnoreCase)) {
    throw 'Use a separate deployment directory to preserve the debugger binaries.'
}
$objcopyCommand = (Get-Command $Objcopy -ErrorAction Stop).Source
$files = @(Get-ChildItem -LiteralPath $source -File | Where-Object { $_.Extension -in '.dll', '.exe' })
if (!$files.Count) { throw 'No executable or DLL files found in the source directory.' }
New-Item -ItemType Directory -Path $destination -Force | Out-Null
[long]$originalBytes = 0
[long]$deploymentBytes = 0
foreach ($file in $files) {
    $output = Join-Path $destination $file.Name
    # Keep exports, imports, runtime unwind tables and base relocations.
    # Debugger information remains in the source binaries.
    & $objcopyCommand --strip-debug $file.FullName $output
    if ($LASTEXITCODE -ne 0) { throw "Could not prepare $($file.Name) (objcopy exit $LASTEXITCODE)." }
    $originalBytes += $file.Length
    $deploymentBytes += (Get-Item -LiteralPath $output).Length
}
foreach ($name in 'import-audit.exe', 'audit-imports.cmd', 'dll-load-probe.exe', 'probe-windowing.cmd', 'run-app-with-exit-code.cmd', 'capture-console.cmd') {
    Copy-Item -LiteralPath (Join-Path $PSScriptRoot $name) -Destination $destination -Force
}
Write-Output ('Prepared {0} binaries: {1:N1} MiB -> {2:N1} MiB on disk.' -f $files.Count, ($originalBytes / 1MB), ($deploymentBytes / 1MB))
Write-Output "Deployment: $destination"
Write-Output 'Copy these binaries together to ReactOS; retain existing application resources and configuration.'

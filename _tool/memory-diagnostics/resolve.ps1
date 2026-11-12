param(
    [Parameter(Mandatory=$true)][string]$LogPath,
    [Parameter(Mandatory=$true)][string]$ModulesCsv,
    [Parameter(Mandatory=$true)][string]$OutputPath,
    [string]$Addr2Line = 'C:/mingw32/bin/addr2line.exe'
)
$ErrorActionPreference = 'Stop'
$modules = Import-Csv -LiteralPath $ModulesCsv
$sites = @{}
foreach ($line in Get-Content -LiteralPath $LogPath) {
    if ($line -match '^site=(\d+) live_bytes=(\d+) live_count=(\d+) delta=(-?\d+) stack=(.*)$') {
        $sites[$matches[1]] = [PSCustomObject]@{
            Id=$matches[1]; Bytes=[long]$matches[2]; Count=[long]$matches[3]
            Delta=[long]$matches[4]; Stack=$matches[5].Trim().Split(' ')
        }
    }
}
$top = @($sites.Values | Sort-Object Bytes -Descending | Select-Object -First 12)
$frames = @{}
foreach ($site in $top) {
    foreach ($hex in $site.Stack) {
        if ($frames.ContainsKey($hex)) { continue }
        $pc = [Convert]::ToInt64($hex,16)
        $module = $modules | Where-Object {
            $pc -ge [long]$_.Base -and $pc -lt ([long]$_.Base+[long]$_.Size)
        } | Select-Object -First 1
        if (!$module) { continue }
        $frames[$hex] = [PSCustomObject]@{
            PC=$pc; Module=$module; Function=''; Location=''
        }
    }
}
foreach ($group in ($frames.Values | Group-Object {$_.Module.Path})) {
    $path = $group.Name
    # Resolve application debug binaries; keep system/runtime modules as offsets.
    if (!(Test-Path -LiteralPath $path) -or $path -notmatch '[\\/]output[\\/]') { continue }
    $reader = [IO.BinaryReader]::new([IO.File]::OpenRead($path))
    try {
        $reader.BaseStream.Position=0x3c
        $pe=$reader.ReadInt32()
        $reader.BaseStream.Position=$pe+24
        $magic=$reader.ReadUInt16()
        if ($magic -eq 0x10b) {
            $reader.BaseStream.Position=$pe+52; $preferred=$reader.ReadUInt32()
        } elseif ($magic -eq 0x20b) {
            $reader.BaseStream.Position=$pe+48; $preferred=$reader.ReadUInt64()
        } else { continue }
    } finally { $reader.Dispose() }
    $addresses=@($group.Group | ForEach-Object {
        '0x{0:x}' -f ($_.PC-[long]$_.Module.Base+$preferred)
    })
    $resolved=@(& $Addr2Line -f -C -e $path @addresses)
    if ($LASTEXITCODE -ne 0) { throw "addr2line failed for $path" }
    for ($i=0; $i -lt $group.Count; ++$i) {
        $group.Group[$i].Function=$resolved[$i*2]
        $group.Group[$i].Location=$resolved[$i*2+1]
    }
}
$report=[Collections.Generic.List[string]]::new()
$report.Add('# Retained Windows allocator block stacks')
$report.Add('')
$report.Add('Latest reported values for the twelve largest captured sites; small allocations are sampled. Use matching binaries from this run.')
foreach ($site in $top) {
    $report.Add('')
    $report.Add("## Site $($site.Id): $($site.Bytes) bytes, $($site.Count) blocks; last interval delta $($site.Delta)")
    $report.Add('')
    $report.Add('```text')
    foreach ($hex in $site.Stack) {
        if (!$frames.ContainsKey($hex)) { $report.Add("$hex <unmapped>"); continue }
        $frame=$frames[$hex]
        $offset=$frame.PC-[long]$frame.Module.Base
        $report.Add(('{0} {1}+0x{2:x} {3}' -f $hex,$frame.Module.Name,$offset,$frame.Function))
        if ($frame.Location) { $report.Add("    $($frame.Location)") }
    }
    $report.Add('```')
}
[IO.File]::WriteAllLines([IO.Path]::GetFullPath($OutputPath),$report,[Text.UTF8Encoding]::new($false))
Write-Output "Resolved report: $OutputPath"

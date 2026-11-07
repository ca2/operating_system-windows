[CmdletBinding()]
param(
    [ValidateSet('Debug', 'Release')]
    [string[]] $Configuration = @('Debug', 'Release'),
    [string] $SdkRoot,
    [string] $StorageRoot,
    [string] $RuntimeDirectory,
    [string] $PlatformToolset = 'v143',
    [switch] $BuildWrapper
)

$ErrorActionPreference = 'Stop'
$ProgressPreference = 'SilentlyContinue'
if ($RuntimeDirectory -and $Configuration.Count -ne 1) {
    throw '-RuntimeDirectory requires exactly one configuration'
}
$version = '109.1.13+g18f6895+chromium-109.0.5414.87'
$package = "cef_binary_${version}_windows64"
$checkoutRoot = [IO.Path]::GetFullPath((Join-Path $PSScriptRoot '..\..\..\..'))
if (!$StorageRoot) {
    $StorageRoot = [IO.Path]::GetFullPath((Join-Path $checkoutRoot '..\operating_system\storage-windows'))
}
$cache = Join-Path $PSScriptRoot 'cmake-build-prebuilt'
function Get-CefFileHash([string] $LiteralPath, [string] $Algorithm) {
    # Build environments can omit the PowerShell module providing Get-FileHash.
    $stream = [IO.File]::OpenRead($LiteralPath)
    $hasher = [Security.Cryptography.HashAlgorithm]::Create($Algorithm)
    try { return [BitConverter]::ToString($hasher.ComputeHash($stream)).Replace('-', '') }
    finally { $hasher.Dispose(); $stream.Dispose() }
}
function Copy-CefFile([string] $SourceFile, [string] $DestinationFile) {
    $item = Get-Item -LiteralPath $SourceFile
    if (Test-Path -LiteralPath $DestinationFile) {
        $existing = Get-Item -LiteralPath $DestinationFile
        if ($existing.Length -eq $item.Length -and $existing.LastWriteTimeUtc -eq $item.LastWriteTimeUtc) { return }
        if ($existing.Length -eq $item.Length -and
            (Get-CefFileHash $DestinationFile SHA256) -eq
            (Get-CefFileHash $SourceFile SHA256)) { return }
    }
    New-Item -ItemType Directory -Path (Split-Path $DestinationFile) -Force | Out-Null
    Copy-Item -LiteralPath $SourceFile -Destination $DestinationFile -Force
}
if (!$SdkRoot) {
    $SdkRoot = Join-Path $cache $package
    if (!(Test-Path (Join-Path $SdkRoot 'include\cef_version.h'))) {
        New-Item -ItemType Directory -Path $cache -Force | Out-Null
        $archive = Join-Path $cache "$package.tar.bz2"
        $sha1 = '3c4c025052cd14167e2289c6248302cb0cbc45bd'
        if ((Test-Path $archive) -and (Get-CefFileHash $archive SHA1) -ne $sha1) {
            Remove-Item -LiteralPath $archive
        }
        if (!(Test-Path $archive)) {
            $url = 'https://cef-builds.spotifycdn.com/' + [Uri]::EscapeDataString("$package.tar.bz2")
            Write-Host "Downloading official prebuilt CEF $version (Windows x64)..."
            $partial = "$archive.partial"
            if (Get-Command curl.exe -ErrorAction SilentlyContinue) {
                # Bounded range requests also work through proxies that buffer
                # a complete response before forwarding large downloads.
                $length = 272266263
                $chunkSize = 16MB
                $stream = [IO.File]::Create($partial)
                try {
                    for ($offset = 0; $offset -lt $length; $offset += $chunkSize) {
                        $end = [Math]::Min($length - 1, $offset + $chunkSize - 1)
                        $chunk = "$partial.chunk"
                        & curl.exe --fail --location --silent --show-error --retry 2 --connect-timeout 30 --max-time 180 --range "$offset-$end" --output $chunk $url
                        if ($LASTEXITCODE) { throw 'CEF SDK download failed' }
                        if ((Get-Item -LiteralPath $chunk).Length -ne ($end - $offset + 1)) { throw 'Unexpected CEF download range length' }
                        $inputStream = [IO.File]::OpenRead($chunk)
                        try { $inputStream.CopyTo($stream) } finally { $inputStream.Dispose() }
                        Remove-Item -LiteralPath $chunk
                    }
                } finally { $stream.Dispose() }
            } else {
                Invoke-WebRequest -UseBasicParsing -Uri $url -OutFile $partial -TimeoutSec 600
            }
            if ((Get-CefFileHash $partial SHA1) -ne $sha1) {
                throw "CEF archive checksum mismatch: $partial"
            }
            Move-Item -LiteralPath $partial -Destination $archive -Force
        }
        if ((Get-CefFileHash $archive SHA1) -ne $sha1) {
            throw "CEF archive checksum mismatch: $archive"
        }
        Push-Location $cache
        try {
            & cmake -E tar xjf $archive
            if ($LASTEXITCODE) { throw 'CEF SDK extraction failed' }
        } finally { Pop-Location }
    }
}
$SdkRoot = (Resolve-Path -LiteralPath $SdkRoot).Path
$sdkVersion = Get-Content (Join-Path $SdkRoot 'include\cef_version.h') -Raw
if ($sdkVersion -notmatch ('#define CEF_VERSION "' + [regex]::Escape($version) + '"')) {
    throw "Expected the prebuilt CEF $version SDK"
}

foreach ($config in $Configuration) {
    $source = Join-Path $SdkRoot $config
    if (!(Test-Path (Join-Path $source 'libcef.dll'))) {
        throw "SDK is missing $config\libcef.dll; supply the standard Windows x64 distribution"
    }
    $destination = Join-Path $StorageRoot "x64\$config"
    $binary = Join-Path $destination 'binary'
    $library = Join-Path $destination 'library'
    New-Item -ItemType Directory -Path $binary, $library -Force | Out-Null
    $runtimeDirectories = @($binary)
    if ($RuntimeDirectory) {
        $runtimeDirectories += [IO.Path]::GetFullPath($RuntimeDirectory)
    }
    Get-ChildItem -LiteralPath $source -File | ForEach-Object {
        if ($_.Extension -eq '.lib') {
            Copy-CefFile $_.FullName (Join-Path $library $_.Name)
        } elseif ($_.Extension -ne '.pdb') {
            foreach ($runtime in $runtimeDirectories) {
                Copy-CefFile $_.FullName (Join-Path $runtime $_.Name)
            }
        }
    }
    $resources = Join-Path $SdkRoot 'Resources'
    Get-ChildItem -LiteralPath $resources -Recurse -File | ForEach-Object {
        foreach ($runtime in $runtimeDirectories) {
            Copy-CefFile $_.FullName (Join-Path $runtime $_.FullName.Substring($resources.Length + 1))
        }
    }
    Copy-CefFile (Join-Path $SdkRoot 'LICENSE.txt') (Join-Path $binary 'LICENSE.cef.txt')

    if ($BuildWrapper) {
        # CEF itself is prebuilt. Only its C++ adapter needs our CRT/toolset.
        $build = Join-Path $cache "wrapper-$PlatformToolset"
        & cmake -S $SdkRoot -B $build -G 'Visual Studio 18 2026' -A x64 -T $PlatformToolset '-DUSE_SANDBOX=OFF' '-DUSE_ATL=OFF' '-DCEF_RUNTIME_LIBRARY_FLAG=/MD'
        if ($LASTEXITCODE) { throw 'CEF wrapper configuration failed' }
        & cmake --build $build --config $config --target libcef_dll_wrapper --parallel 8
        if ($LASTEXITCODE) { throw "CEF $config wrapper build failed" }
        Copy-CefFile (Join-Path $build "libcef_dll_wrapper\$config\libcef_dll_wrapper.lib") (Join-Path $library 'libcef_dll_wrapper.lib')
    }
    Write-Host "CEF $config runtime: $binary"
    Write-Host "CEF $config libraries: $library"
    if ($RuntimeDirectory) { Write-Host "CEF application runtime: $RuntimeDirectory" }
}

# Prebuilt CEF for Windows x64 and ARM64

From PowerShell:

```powershell
.\setup.ps1
.\setup.ps1 -Configuration Release
.\setup.ps1 -Architecture ARM64 -Configuration Debug -BuildWrapper
.\setup.ps1 -Configuration Release -RuntimeDirectory C:\Users\camilo\code\main\time-windows\x64\Release
```

The default installs both Debug and Release from the official **prebuilt** CEF
109.1.13 standard Windows SDK for the selected architecture, matching this checkout's headers. It verifies
the published archive checksum and caches the SDK in the sibling `operating_system/external_build/cef` directory. Chromium and
`libcef.dll` are never compiled.

Outputs:

- `C:\Users\camilo\code\operating_system\storage-windows\x64\Debug\binary`
- `C:\Users\camilo\code\operating_system\storage-windows\x64\Release\binary`
- Import/static libraries in each configuration's sibling `library` directory.

The binary directories include DLLs, snapshots, resource packs, and `locales`.
Existing unrelated files are preserved. `-Architecture` accepts x64 (default) or ARM64. `-ExternalBuildRoot` overrides the SDK/wrapper cache. `-CMakeExecutable` overrides CMake discovery (PATH, then the Visual Studio installation). `-StorageRoot` overrides the
`storage-windows` directory; `-SdkRoot` uses an already extracted SDK.
`-RuntimeDirectory` also stages the runtime assets beside an application. CEF
requires ICU data and resource packs at runtime, not just its DLLs. This option
accepts one configuration at a time; cefclient's project supplies its output
directory automatically.

CEF distributes its C++ wrapper as source. `-BuildWrapper` builds only that small
adapter using CMake 3.24+ and Visual Studio 2026, with `/MDd` for Debug and `/MD`
for Release. `-PlatformToolset` defaults to `v143`. The cefclient project invokes
this option automatically before linking; later builds reuse cached outputs.

ARM64 uses the matching 109.1.13 windowsarm64 distribution and its published checksum. The cache resolves directory symlinks before extraction so junction-based checkout paths work with CMake's archive security checks.

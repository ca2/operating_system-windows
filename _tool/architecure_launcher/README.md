# Architecture launcher

The folder spelling `architecure_launcher` is intentional. `launcher.h` contains
reusable Win32 dispatch, architecture detection, Windows argument quoting, and
child-process ownership code. `launcher.cpp` supplies the generic executable's
entry point; ../shell/shell.cpp includes the same header with fixed routing.

Build with ./build.ps1 on an MSVC host. The output is an x86 PE with subsystem
5.01 and no CRT/UCRT, ca2, or STL dependencies, staged in the sibling
operating_system/storage-windows/x86/<Configuration>/binary and deployed to
../../tool/bin. Newer architecture queries are loaded dynamically; all static
imports exist on XP. The same fallback code compiles with __REACTOS__.

Generic usage:

```
architecture_launcher.exe folder=PATH executable=NAME [-- ARGUMENTS]
```

Relative folders resolve against the checkout containing the launcher. If the
module directory ends with the supplied relative folder, removing that suffix
finds the enclosing checkout even with nested submodules. Otherwise it walks
ancestors to .git. Absolute folders are accepted. The selected child runs in the
checkout and its exit code is returned. Errors display a dialog for Explorer.

The x86 bootstrap uses Windows compatibility/emulation on x64 and ARM64 to
start a native payload. XP, ReactOS and ARM64 runtime verification still require
those systems; the payload and Git must independently support the target OS.

# ReactOS import audit

Copy `import-audit.exe` and `audit-imports.cmd` next to the deployed application
executable and DLLs **inside ReactOS**. Double-click `audit-imports.cmd`.
It defaults to `_app_app.exe`, also scans every DLL in that folder, and writes
`import-audit-report.txt` next to the launcher.

For another application, use a command prompt:

```
audit-imports.cmd my-program.exe
```

For automation without a pause:

```
import-audit.exe my-program.exe --all > import-audit-report.txt 2>&1
```

The tool needs no Python, PowerShell, MinGW DLLs, or installation. It is a
32-bit native executable linked to the legacy KERNEL32/MSVCRT libraries.
It reads files; it never loads or runs the audited DLLs. Trailing debug sections
are excluded from the retained file data to reduce memory use with large
Debug DLLs on 32-bit ReactOS.

## Reading the report

- `MISSING DLL`: the dependency could not be located/read.
- `WRONG ARCH`: the importing and imported files have different machine types.
- `MISSING SYMBOL`: a named or ordinal import could not be resolved, including
  its forwarded export chain.
- `MISSING DELAY SYMBOL`: a delay-loaded import could not be resolved; it may
  only fail when the application uses that feature.
- `FORWARD TARGET`: additional context for an unresolved forwarded export.
- `AUDIT ERROR`: parsing/read/resource-limit failure. The report is incomplete.
- `SUMMARY`: number of modules, checked imports, missing imports, and errors.

Exit status is 0 for no missing imports, 1 for missing dependencies/symbols,
and 2 for an incomplete audit. `--all` includes optional plugin DLLs that may
not be loaded at startup; omit it to audit only the executable dependency graph.

## Scope

Resolution searches the executable folder, the running OS's System32, then
its Windows directory. Do not use a modern Windows-host report as proof of
ReactOS compatibility. Always run against the actual deployed files on the
actual ReactOS installation.

The tool does not emulate KnownDLL registry overrides, manifest/SxS selection,
API-set mapping, custom DLL directories, PATH resolution, or LoadLibrary calls.
API-set imports can therefore produce false missing results on modern Windows.
GetProcAddress usage and runtime behavior require separate testing. PE files
must be ordinary, unbound named/ordinal imports; unresolved bound import tables
can produce an incomplete audit. Paths are ANSI and limited to MAX_PATH.
Forwarder chains are limited to 32 hops and module storage to 2048 files.
Trailing DWARF debug sections, including COFF long section names, are not
retained in memory. Large debug DLLs can therefore be audited on 32-bit ReactOS.

## Rebuilding

Run `build-audit.cmd` with a 32-bit MinGW GCC compiler on PATH. This does not
change the ca2 application build or its Windows/MSVC configuration.

The fixture test uses Python **only on the development host**:

```
python tests/test_audit.py
```

Verified on a Windows host: named and ordinal exports, forwarded exports,
missing DLLs and exports, and malformed input. Actual execution on ReactOS
remains unverified.

## Preparing a 32-bit ReactOS deployment

Large MinGW DWARF debug sections contribute to PE `SizeOfImage` even though
Windows does not need them to execute the code. A complete debug framework can
exhaust the 32-bit address space and fail before startup with `0xC0000018`.
A successful import audit does not test whether all images fit in memory.

For the 32-bit MinGW build with `__REACTOS__` enabled, CMake automatically prepares
separate deployment copies after linking each EXE and DLL. The default folder
is `../_stripped_output`, relative to the workspace root. Set the CMake
cache path `CA2_REACTOS_DEPLOY_DIRECTORY` to choose a different destination.
Executable builds also copy the available MinGW/OpenSSL runtime DLLs and audit
tools. Debugger binaries remain in the normal build output folder.

To refresh the deployment from all binaries already present in the build output
(for example after removing a deployment copy), run:

```powershell
cmake --build cmake-build-debug-mingw-reactos --target reactos_deploy
```

This refresh target stages existing binaries; it does not build unrelated
applications. Build the desired application target first. Recent Windows/MSVC
builds do not enable this deployment step.

For a manual deployment outside the CMake integration, run on the development host:

```powershell
.\tools\reactos-import-audit\prepare-reactos-deployment.ps1 `
  -SourceDirectory .\cmake-build-debug-mingw-reactos\output `
  -DestinationDirectory .\cmake-build-debug-mingw-reactos\reactos-deploy
```

The script removes debug sections from copies of the EXEs and DLLs, retaining
exports and base relocations. Original debug binaries stay intact for CLion.
Copy the generated binaries together to the ReactOS application folder, keeping
its resources/configuration, and rerun the import audit there. Stack addresses
can still be translated using the corresponding original debug binaries.
The preparation script runs on the development host; ReactOS needs no PowerShell.

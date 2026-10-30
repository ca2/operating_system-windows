# Dynamic-source compiler and linker stage

The Windows batch files in this directory are runtime templates for compiling generated dynamic-source DLLs. They are hand-maintained templates; MSBuild does not emit them automatically.

## How Netnode selects a template

`source/app/programming/dynamic_source/script_compiler.cpp` builds the Windows compile path as:

```text
operating_system/operating_system-windows/_stage/dynamic_source/<vstools>/<configuration>_c_<platform>.bat
```

The linker path uses the same parts with `_l_` instead of `_c_`. The configuration is chosen in `source/app/programming/programming/compiler.cpp`: `debug` for `_DEBUG`, `release` otherwise, or `memdleak` when `MEMDLEAK` is enabled. The integration context supplies the Visual Studio toolset folder and platform.

For the current Visual Studio v145, Debug x64 setup, the active pair is:

- `145/debug_c_x64.bat`
- `145/debug_l_x64.bat`

Release x64 selects `145/release_c_x64.bat` and `145/release_l_x64.bat`.

## Source of compiler settings

Use `source/app-core/netnode_dynamic_source_script/netnode_dynamic_source_script.vcxproj` as the baseline for compiler and PCH settings. The project builds `netnode_dynamic_source_script_platform.pch`, which the runtime compile template consumes. Its actual MSBuild invocation is recorded in the project's `CL.command.1.tlog`; its project-library link invocation is in `link.command.1.tlog`. After a clean Debug x64 build, these logs are under:

```text
time-windows/intermediate/x64/Debug/app-core/netnode_dynamic_source_script/netnode_*.tlog/
```

The stage templates are not byte-for-byte copies of those invocations: they substitute generated source, object and output paths, use runtime-specific include paths and libraries, and link a generated script DLL rather than the `netnode_dynamic_source_script.dll` library. Keep the shared compiler settings aligned with the project and review the generated tlog after changes to the project configuration.

The Debug x64 command was compared with the project after a clean build on 2026-10-28. The project emitted `/Od /Ob2`; `145/debug_c_x64.bat` has been aligned to `/Ob2`. Both use the Debug DLL runtime (`/MDd`), C++20, the same PCH header/output, and matching debug information settings. The runtime template also has stage-specific switches and include paths, so inspect the full tlog rather than assuming the entire command is identical.

The Debug x64 templates initialize the configured Visual Studio environment using `%VS_VARS_PLAT2%` (`x86_amd64` in the current integration context), matching the x86-hosted x64 compiler that MSBuild used to create the PCH. Both the toolset version and compiler host must match: the x64-hosted compiler from the same toolset rejected this PCH with C1853. Recheck the actual MSBuild compiler path after changing the project or Visual Studio configuration. Other templates may still resolve tools from the Netnode process PATH.

## Inactive files

In `145`, only the four Debug/Release x64 files listed above match the current selector. Other batch files have been retained in `145/_collection/` with an `aaa_` prefix to make clear that the current selector does not use them. They remain available as historical references; do not assume the legacy `memdleak_*` or `profiler_*` variants are wired to the current selector. Add a correctly named compile/link pair before enabling another configuration or platform.

# Windows build and diagnostic tools

The outer root adds this directory before configuring application components.
`CMakeLists.txt` registers the per-project manifest and deployment hooks and
defers creation of the deployment target until platform output paths are set.
It also loads `../runtime_dependencies.cmake`: 32-bit GCC MinGW builds attach
`mingw_runtime` to `acme`. Changed toolchain DLLs and missing destination copies
are staged into the binary output and stripped deployment directories as needed.
MSVC and 64-bit MinGW do not use this runtime target.

- `windows-common-controls`: themed controls manifest helper for Windows executables.
- `reactos-import-audit`: import auditing, loader probes, and deployment scripts.
- `reactos-layered-probe`: layered-window diagnostics.
- `windows-xp-compat`: shared Windows/XP adapter regression tests.
- `memory-diagnostics`: Windows heap tracking tests and address resolution.
- `openssl`, `ffmpeg`: parent-project Windows SDK build and staging adapters;
  standalone external build projects remain under `port/external_build`.

Platform-independent tools belong under `source/app/tools` when added.

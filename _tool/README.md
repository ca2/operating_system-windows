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
- OpenSSL, FFmpeg, and CEF now use the active formulas under
  `port/external_build`. Their former integrations are archived in
  `aaa_openssl`, `aaa_ffmpeg`, and `aaa_cefclient`.

Platform-independent tools belong under `source/app/tools` when added.

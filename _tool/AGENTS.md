# Windows tool build outputs

Projects and build scripts under this folder must stage their distributable
binaries into the checkout's sibling
`../operating_system/storage-windows/<architecture>/<configuration>/binary`
and static/import libraries into
`../operating_system/storage-windows/<architecture>/<configuration>/library`.
Paths above are relative to the top-level checkout, not this `_tool` folder.

For x64 Debug, use `storage-windows/x64/Debug/binary` and
`storage-windows/x64/Debug/library`. Do not introduce `third/binary` or
`third/library`; third-party dependencies use the same directories as other
projects built through these `_tool` scripts. Port projects using the shared
`port_debug.props` and `port_release.props` retain their existing `third/binary`
and `third/library` output layout; do not change those property sheets to apply
this `_tool` convention. Shared library search paths must continue to support
port libraries in `third/library`.

Select architecture and configuration from the active build rather
than hardcoding x64 or Debug for every build.

An SDK may retain its internal `bin`, `lib`, and `include` layout, but its
runtime files and link libraries must also be staged directly into the shared
`binary` and `library` directories. Keep application-local runtime copies and
explicit deployment copies where needed. Preserve explicit caller overrides.

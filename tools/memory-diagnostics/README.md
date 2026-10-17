# Windows memory diagnostics

Configure with `-DMEMORY_DIAGNOSTICS=ON`. The default is OFF. The option defines
`MEMORY_DIAGNOSTICS` only for the allocator and diagnostics translation units;
it does not change framework headers or object layouts.

This first layer tracks `windows_common::heap_allocator` blocks while its
existing allocator lock is held. These are pool backing blocks, not individual
C++ objects, CRT allocations, graphics resources, or process committed bytes.
Compare the log with process private bytes to determine coverage.

The file `ca2-memory-PID.log` is created beside the executable. Override its path
with `CA2_MEMORY_DIAGNOSTICS_LOG`. Totals are written at most once per second
when the allocator is active. Every five seconds the report ranks stack sites
by the change in their retained bytes. Call `ca2_memory_diagnostics_snapshot()`
from a paused debugger for a best-effort report; it returns immediately if a
stopped thread holds the tracking lock.

Stacks are captured for every block of at least 16 KiB and one in 32 smaller
blocks. Site totals describe captured allocations, without extrapolation.
All block sizes are counted until the bounded pointer table is full. `dropped`
and `unmatched_free` disclose lost coverage. Annotation strings are copied when
available; they describe the first captured allocation at that stack site.
Raw stack addresses must be resolved using the modules loaded in that run and
their matching debug binaries. Stack capture is looked up dynamically and may
be unavailable or incomplete on older systems.

`resolve.ps1` resolves the largest reported sites with MinGW `addr2line`. Supply
the log, a CSV with module `Name,Path,Base,Size` fields captured from the running
process, and an output Markdown path. Resolve before rebuilding the binaries.

Tracking uses fixed storage obtained directly with `VirtualAlloc`, a raw lock,
and a thread-local recursion guard. It never calls framework allocation or
logging. Storage and the file handle deliberately live until process exit to
permit late shutdown frees. Log output stops after 64 MiB. Allocation ownership,
failed-reallocation behavior, and the Windows last-error value are preserved.

The standalone tests can be built with the selected MinGW compiler:

```
g++ -std=c++17 -DMEMORY_DIAGNOSTICS=1 operating_system/operating_system-windows/tools/memory-diagnostics/tests.cpp source/app/acme/memory/diagnostics.cpp -o memory-diagnostics-test.exe
memory-diagnostics-test.exe memory-diagnostics-test.log
```

Disable the CMake option after the investigation to remove all tracking hooks.

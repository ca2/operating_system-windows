# Integer formatting on XP and current Windows

`acme/operating_system/windows/printf_format.h` provides
`CA2_PRINTF_FORMAT(format)`. The shared narrow/wide string formatting helpers
and framework console wrappers use it. Under `__REACTOS__` it translates C99
integer lengths before calling the legacy CRT:

| Input | XP format |
| --- | --- |
| `%lld`, `%llu`, `%llx`, `%jd` | `%I64d`, `%I64u`, `%I64x`, `%I64d` |
| `%zu`, `%td` on 32-bit | `%u`, `%d` |
| `%zu`, `%td` on 64-bit | `%I64u`, `%I64d` |

Flags, field widths, precision, escaped `%%`, and Windows wide `%s`/`%S`
remain intact. The non-ReactOS macro returns the original format expression.
It does not change the minimum Windows version or require UCRT/newer APIs.
This adapts ordinary sequential printf output, not scanf, positional arguments,
or a format string whose argument types are already incorrect.

For a direct legacy CRT call the fix is one line after including the header:

```cpp
_vscprintf(CA2_PRINTF_FORMAT(format), args);
```

The temporary owns a converted format until the end of that expression; do not
store the returned pointer. Conversion can allocate. Allocation-independent
Windows memory diagnostics instead use literal `%I64d`/`%I64u`, supported by
both legacy MSVCRT and current Windows CRT implementations.

Match arguments independently of the runtime adaptation:

```cpp
informationf("items=%lld", static_cast<long long>(items.get_count()));
informationf("bytes=%zu", static_cast<size_t>(bytes));
informationf("pointer=%p", static_cast<void *>(pointer));
```

The audit searched integer length macros, literal 64-bit and pointer-size
formats, legacy CRT entry points, pointer logging, collection counts, and time
values under `source` and `operating_system`. Confirmed mismatches in first-party
code were corrected. Third-party implementations and generated dependency
headers were not rewritten. Text searches do not establish that every variadic
call in the tree is type-correct, especially dynamically assembled formats.

`tests/printf_format.cpp` tests the weather exception pattern, integer limits,
pointer-sized values, widths/precision, escapes, and Windows wide-string
semantics. CMake exposes `printf_format_xp` and `printf_format_native`.
With a MinGW/MSVCRT toolchain the native test checks passthrough only; the full
native CRT test is intended for MSVC. Run the XP test on XP as well: passing on
a current Windows host does not prove XP runtime compatibility.

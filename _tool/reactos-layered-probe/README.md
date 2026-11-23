# ReactOS layered-window probe

The default mode creates **one real WS_EX_LAYERED top-level window**, with no
opaque backing window. The desktop and other applications below it in the
z-order should show through its half-transparent red pixels. White frame-counter
text updates continuously at approximately 20 FPS. Click the red window to stop.

Run `layered-probe.exe` in a writable folder. Keep it uncovered and watch whether
its red surface becomes opaque after repeated redraws. The log is written to
`layered-probe.log` beside the executable. In desktop mode, screen samples are
observations only: the changing desktop has no fixed expected color, so a run
without API errors does not automatically mean translucency passed.

An optional `--checkerboard` mode puts a known opaque checkerboard **behind** the
layered window. That is a controlled blending test, not a desktop transparency
test. A fixed sample patch lets that mode automatically check for buildup.

For bounded runs:

```bat
layered-probe.exe --frames 100
layered-probe.exe --checkerboard --frames 100
```

Every frame reconstructs the premultiplied BGRA source and changing white text.
The lower-right source sample stays `0x80800000`, away from the text. No ca2,
GDI+, external font files, network access, or external GCC runtime DLLs are used.
No system settings are changed and no screenshots are saved. The probe uses
legacy Win32 APIs; optional DPI awareness uses dynamic lookup on newer Windows.

Build with 32-bit MinGW:

```bat
g++ layered-probe.cpp -o layered-probe.exe -std=c++11 -O2 -Wall -Wextra -static -lgdi32 -luser32
```

The checkerboard mode passed 100 redraws on the Windows host. Desktop-mode
runtime validation on ReactOS remains pending.

# Windows themed common controls

The outer project automatically enables Common Controls v6 for executable targets
declared in `source/**/__implement/CMakeLists.txt`. Component sources are unchanged.
The helper can also be used explicitly after `add_executable`:

```cmake
include("${CMAKE_SOURCE_DIR}/operating_system/operating_system-windows/tools/windows-common-controls/common-controls.cmake")
ca2_enable_windows_common_controls(my_executable)
```

The function is idempotent and does nothing on other operating systems. MSVC uses
the linker's manifest dependency merging; MinGW embeds an application manifest as
resource type 24, ID 1. MinGW targets must not separately embed another manifest
at that same resource ID; merge any future manifest requirements into this file.
For GCC distributions that automatically insert `default-manifest.o`, a generated
target-specific specs file suppresses that default object while retaining all
other startup/end files. The installed compiler is unchanged.

Windows XP supports this same v6 activation mechanism. Controls follow the host's
active theme: XP appearance on XP, current Windows appearance on recent Windows.
This does not force a particular flat style or replace custom-drawn controls or
older dialog APIs with newer ones. Controls still need their normal initialization.
No new Windows API imports or minimum OS requirements are introduced.

Reference: https://learn.microsoft.com/en-us/windows/win32/sbscs/enabling-updated-common-controls-visual-styles-and-themes

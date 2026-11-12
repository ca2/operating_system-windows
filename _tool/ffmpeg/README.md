# windows-build-all FFmpeg integration

`windows-build-all.cmake` owns the parent project's FFmpeg dependency settings,
installation layout, runtime staging, and `port_all` dependencies. It is included
by `port/port.cmake` when `INCLUDE_AUDIO` is enabled.

The external project at `port/external_build/ffmpeg` stays usable independently.
The parent sets these cache defaults before adding that project; CLion profile
options or `cmake -D...` can override them without modifying external scripts:

| Variable | Parent default / purpose |
| --- | --- |
| `FFMPEG_VERSION` | 6.1.6 for `__REACTOS__`, otherwise 9.0.2 |
| `FFMPEG_INSTALL_DIR` | Configuration-specific ca2 storage SDK directory |
| `FFMPEG_BUILD_PROGRAMS` | OFF: application dependencies need libraries |
| `FFMPEG_NETWORK` | OFF: local media/resampling needs no network protocols |
| `FFMPEG_EXTRA_CONFIGURE_ARGS` | Empty: upstream built-in codec/format set; supply a semicolon-separated list to customize |
| `CA2_FFMPEG_SOURCE_DIRECTORY` | Location of the standalone CMake project |

The external project's other cache settings remain available: `FFMPEG_JOBS`,
`FFMPEG_BASH`, `FFMPEG_URL`, `FFMPEG_SHA256`, and `FFMPEG_SOURCE_DIR` (the latter
selects pristine FFmpeg C sources, rather than the wrapper project).

`CMAKE_BUILD_TYPE`, architecture and compiler are inherited from the parent.
Debug/Release SDKs go to separate storage directories. XP uses `Win32` storage
and the XP profile; recent Windows storage follows the compiler's pointer size.

The imported avutil, swresample, avcodec, avformat and swscale targets serve the
audio resampler and video decoder dependencies. Their runtime targets stage DLLs
beside applications and join `port_all`. XP deployment additionally passes those
DLLs through the existing stripping/deployment helper into
`CA2_REACTOS_DEPLOY_DIRECTORY`, whose default is `../_stripped_output`.
Existing application dependencies on `ffmpeg_xp_build` remain supported.

Do not disable required libraries or override the XP API/threading adaptations
through extra configure arguments. Changing FFmpeg major versions may require
source API changes in consuming projects; a selectable version does not migrate
their code automatically.

The audio resampler uses explicit channel layouts with `swr_alloc_set_opts2` for
FFmpeg 6.1 and recent releases. Older FFmpeg headers retain the legacy setup.
Normal Debug binaries keep their symbols in the build output. The separate
32-bit XP/ReactOS deployment helper strips a copied binary into `_stripped_output`;
it does not replace the original.

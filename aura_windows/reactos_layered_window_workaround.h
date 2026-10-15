#pragma once

#if defined(__REACTOS__)
#include <cstddef>
#include <cstdint>

namespace windowing_win32
{
   // Temporary workaround for ReactOS UpdateLayeredWindow blending new frames
   // onto previous screen contents. Flatten a COPY of premultiplied BGRA onto
   // an opaque, dark-mode-aware background; never alter the source render target.
   inline void _reactos_workaround_flatten_layered_window_onto_opaque_background(
      std::uint32_t * pixels, std::size_t count, bool darkMode, unsigned opacity)
   {
      const unsigned background = darkMode ? 32u : 255u;
      for (std::size_t i = 0; i < count; ++i)
      {
         const auto pixel = pixels[i];
         const unsigned alpha = (((pixel >> 24) & 255u) * opacity + 127u) / 255u;
         const unsigned behind = (background * (255u - alpha) + 127u) / 255u;
         unsigned channels[3];
         for (unsigned channel = 0; channel < 3; ++channel)
         {
            unsigned value = (((pixel >> (channel * 8)) & 255u) * opacity + 127u) / 255u + behind;
            channels[channel] = value > 255u ? 255u : value;
         }
         pixels[i] = 0xff000000u | (channels[2] << 16) | (channels[1] << 8) | channels[0];
      }
   }
}
#endif

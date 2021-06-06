#include "framework.h"


extern "C"
void write_text_win32_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::write_text_win32::fonts, ::write_text::fonts >();
   pfactorymap->create_factory < ::write_text_win32::write_text, ::write_text::write_text >();
   pfactorymap->create_factory < ::write_text_win32::font_enumeration, ::write_text::font_enumeration >();

}
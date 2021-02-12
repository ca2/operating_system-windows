#include "framework.h"


extern "C"
void write_text_direct2d_factory_exchange(::factory_map * pfactorymap)
{

   create_factory < ::write_text_direct2d::font_department, ::font_department >();
   create_factory < ::write_text_direct2d::write_text, ::write_text::write_text >();

}
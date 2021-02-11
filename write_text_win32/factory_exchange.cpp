#include "framework.h"


extern "C"
void write_text_win32_factory_exchange()
{

   create_factory < ::write_text_win32::font_department, ::font_department >();
   create_factory < ::write_text_win32::write_text, ::write_text::write_text >();

}
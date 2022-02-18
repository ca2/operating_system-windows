#include "framework.h"


//BEGIN_FACTORY(write_text_win32)
//FACTORY_ITEM(::write_text_win32::fonts)
//FACTORY_ITEM(::write_text_win32::write_text)
//FACTORY_ITEM(::write_text_win32::font_enumeration)
//END_FACTORY()


__FACTORY_EXPORT void write_text_win32_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::write_text_win32::fonts, ::write_text::fonts >();
   pfactory->add_factory_item < ::write_text_win32::write_text, ::write_text::write_text >();
   pfactory->add_factory_item < ::write_text_win32::font_enumeration, ::write_text::font_enumeration >();

}

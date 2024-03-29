#include "framework.h"
#include "fonts.h"
#include "write_text.h"
#include "font_enumeration.h"

//BEGIN_FACTORY(write_text_win32)
//FACTORY_ITEM(::write_text_win32::fonts)
//FACTORY_ITEM(::write_text_win32::write_text)
//FACTORY_ITEM(::write_text_win32::font_enumeration)
//END_FACTORY()


IMPLEMENT_FACTORY(write_text_win32)
{

   pfactory->add_factory_item < ::write_text_win32::fonts, ::write_text::fonts >();
   pfactory->add_factory_item < ::write_text_win32::write_text, ::write_text::write_text >();
   pfactory->add_factory_item < ::write_text_win32::font_enumeration, ::write_text::font_enumeration >();

}

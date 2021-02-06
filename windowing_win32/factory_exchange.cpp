#include "framework.h"


extern "C"
void windowing_win32_factory_exchange()
{

   create_factory < ::windowing_win32::windowing, ::windowing::windowing >();
   create_factory < ::windowing_win32::window, ::windowing::window >();
   create_factory < ::windowing_win32::display, ::windowing::display >();
   create_factory < ::windowing_win32::display >();
   create_factory < ::windowing_win32::buffer, ::graphics::graphics >();

}
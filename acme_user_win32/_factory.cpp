// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSorensen
// Renamed to _nano by camilo on 2021-02-01 13:44 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "window.h"
//#include "acme/operating_system/windows/nano/graphics/brush.h"
//#include "acme/operating_system/windows/nano/graphics/font.h"
//#include "acme/operating_system/windows/nano/graphics/pen.h"
//#include "acme/operating_system/windows/nano/graphics/device.h"
#include "user.h"
#include "acme/nano/nano.h"
#include "acme/platform/factory_function.h"
//#include "acme/prototype/prototype/_factory.h"


IMPLEMENT_FACTORY(nano_user_win32)
{


   pfactory->add_factory_item < ::windows::micro::window, ::acme::windowing::window >();
   //pfactory->add_factory_item < ::windows::nano::graphics::brush, ::nano::graphics::brush >();
   //pfactory->add_factory_item < ::windows::nano::graphics::font, ::nano::graphics::font >();
   //pfactory->add_factory_item < ::windows::nano::graphics::pen, ::nano::graphics::pen >();
   //pfactory->add_factory_item < ::windows::nano::graphics::device, ::nano::graphics::device >();

   pfactory->add_factory_item < ::windows::micro::user, ::micro::user >();

   //::int_rectangle rectangleMainScreen;

   //rectangleMainScreen.left() = 0;
   //rectangleMainScreen.top() = 0; 
   //rectangleMainScreen.right() = GetSystemMetrics(SM_CXSCREEN);
   //rectangleMainScreen.bottom() = GetSystemMetrics(SM_CYSCREEN); 

   //operating_system_set_main_screen_rectangle(rectangleMainScreen);

}


//_REFERENCE_FACTORY(nano_user_win32);




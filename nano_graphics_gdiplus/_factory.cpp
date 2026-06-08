// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSorensen
// Renamed to _nano by camilo on 2021-02-01 13:44 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "brush.h"
#include "font.h"
#include "font_family.h"
#include "icon.h"
#include "image.h"
#include "pen.h"
#include "context.h"
#include "path.h"
#include "graphics.h"
//#include "acme/operating_system/windows/nano/user/user.h"
//#include "acme/operating_system/windows/nano/user/window.h"
#include "acme/nano/nano.h"
#include "acme/platform/factory_function.h"
//#include "acme/windowing/window_base.h"

//#include "acme/prototype/prototype/_factory.h"


IMPLEMENT_FACTORY(nano_graphics_gdiplus)
{


   //pfactory->add_factory_item < ::windows::micro::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::nano_graphics_gdiplus::brush, ::nano::graphics::brush >();
   pfactory->add_factory_item < ::nano_graphics_gdiplus::font, ::nano::graphics::font >();
   pfactory->add_factory_item<::nano_graphics_gdiplus::font_family, ::nano::graphics::font_family>();
   pfactory->add_factory_item < ::nano_graphics_gdiplus::pen, ::nano::graphics::pen >();
   pfactory->add_factory_item < ::nano_graphics_gdiplus::icon, ::nano::graphics::icon >();
   pfactory->add_factory_item < ::nano_graphics_gdiplus::image, ::nano::graphics::image >();
   pfactory->add_factory_item < ::nano_graphics_gdiplus::context, ::nano::graphics::context >();
   pfactory->add_factory_item<::nano_graphics_gdiplus::path, ::nano::graphics::path>();


   pfactory->add_factory_item < ::nano_graphics_gdiplus::graphics, ::nano::graphics::graphics >();

   //pfactory->add_factory_item < ::windows::micro::user, ::micro::user >();
   //pfactory->add_factory_item < ::windows::micro::user, ::micro::user >();

   //::i32_rectangle rectangleMainScreen;

   //rectangleMainScreen.left = 0;
   //rectangleMainScreen.top = 0; 
   //rectangleMainScreen.right = GetSystemMetrics(SM_CXSCREEN);
   //rectangleMainScreen.bottom = GetSystemMetrics(SM_CYSCREEN); 

   //operating_system_set_main_screen_rectangle(rectangleMainScreen);

}


//_REFERENCE_FACTORY(nano_graphics_win32);




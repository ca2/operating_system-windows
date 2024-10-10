#include "framework.h"
#include "window.h"
#include "windowing.h"


IMPLEMENT_FACTORY(acme_windowing_win32)
{

   pfactory->add_factory_item < ::win32::acme::windowing::window, ::acme::windowing::window >();
   pfactory->add_factory_item < ::win32::acme::windowing::windowing, ::acme::windowing::windowing >();

}



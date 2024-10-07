#include "framework.h"
#include "windowing.h"


IMPLEMENT_FACTORY(nano_windowing_win32)
{

   pfactory->add_factory_item < ::win32::acme::windowing::windowing, ::acme::windowing::windowing >();

}



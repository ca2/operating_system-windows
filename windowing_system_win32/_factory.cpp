#include "framework.h"
#include "windowing_system.h"


IMPLEMENT_FACTORY(windowing_system_win32)
{

   pfactory->add_factory_item < ::windowing_system_win32::windowing_system, ::windowing_system::windowing_system >();

}



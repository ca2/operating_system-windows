#include "framework.h"
#include "input.h"


__FACTORY_EXPORT void input_win32_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::input_win32::input, ::input::input >();

}




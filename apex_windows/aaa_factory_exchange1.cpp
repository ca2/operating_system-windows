#include "framework.h"


extern "C"
void ([a-z0-9_]+)_factory(::factory::factory * pfactory)
{

   add_factory_item < node_windows::node, ::platform::node >();

}




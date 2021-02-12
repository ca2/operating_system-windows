#include "framework.h"


extern "C"
void node_windows_factory_exchange(::factory_map * pfactorymap)
{

   create_factory < node_windows::node, ::acme::node >();

}




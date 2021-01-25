#include "framework.h"


extern "C"
void node_windows_factory_exchange()
{

   create_factory < node_windows::node, ::acme::node >();

}



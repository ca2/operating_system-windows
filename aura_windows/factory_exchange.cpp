#include "framework.h"
#include "acme/node/windows/registry.h"
#include "acme_windows/acme.h"
#include "apex_windows/apex.h"
#include "node.h"


void apex_windows_factory_exchange(::factory_map* pfactorymap);


extern "C"
void aura_windows_factory_exchange(::factory_map * pfactorymap)
{

   apex_windows_factory_exchange(pfactorymap);

   pfactorymap->create_factory < ::windows::aura::node, ::acme::node >();

}




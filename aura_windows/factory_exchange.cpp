#include "framework.h"
#include "acme/node/windows/registry.h"
#include "acme_windows/acme.h"
#include "apex_windows/apex.h"
#include "aura.h"


extern "C"
void aura_windows_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::windows::aura, ::acme::node >();

}




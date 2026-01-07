// Created by camilo on 2026-01-06 22:24 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "typeface_factory.h"


__FACTORY_EXPORT void typeface_gdiplus_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item<::typeface_gdiplus::allocator, ::typeface::allocator>();

}




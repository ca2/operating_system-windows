//
// Created by camilo on 2026-04-08 18:50 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "Window.h"
#include "innate_subsystem_windows/_common_header.h"
#include "WindowCache.h"


namespace innate_subsystem_windows
{
   template < typename PARTICLE_INTERFACE, typename BASE = Particle >
   class window_implementation :
      virtual public Implementation<PARTICLE_INTERFACE, BASE >,
      virtual public WindowCache,
      virtual public ::innate_subsystem_windows::notification_handler
   {
   public:

   };
}
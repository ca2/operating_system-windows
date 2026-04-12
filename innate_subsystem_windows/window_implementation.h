//
// Created by camilo on 2026-04-08 18:50 <3ThomasBorregaardSørensen!!
//
#pragma once


#include "Window.h"
#include "innate_subsystem_win32/_common_header.h"
#include "WindowCache.h"


namespace innate_subsystem_win32
{
   template < typename PARTICLE_INTERFACE >
   class window_implementation :
      virtual public ::subsystem::implementation<PARTICLE_INTERFACE >,
      virtual public WindowCache,
      virtual public ::innate_subsystem_win32::notification_handler
   {
   public:

   };
}
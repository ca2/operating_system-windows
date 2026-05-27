// Created by camilo on 2026-04-07 08:42 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "SystemMetrics.h"


namespace innate_subsystem_windows
 {

     SystemMetrics::SystemMetrics()
     {



     }


     SystemMetrics::~SystemMetrics()
     {


     }

     ::i32_size SystemMetrics::get_small_icon_size_in_pixels()
     {
         ::i32 iSmallIconWidthInPixels = ::GetSystemMetrics(SM_CXSMICON);
         ::i32 iSmallIconHeightInPixels = ::GetSystemMetrics(SM_CYSMICON);
         return {iSmallIconWidthInPixels, iSmallIconHeightInPixels};
     }



 } // namespace innate_subsystem_windows

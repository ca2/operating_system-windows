//
// Created by camilo on 2026-04-06 10:58 <3ThomasBorregaardSørensen!!
//

#pragma once


#include "subsystem_win32/subsystem.h"
#include "apex/innate_subsystem_win32/subsystem.h"

namespace windows
{
   namespace innate_subsystem_win32
   {


      class CLASS_DECL_APEX subsystem :
         virtual public ::windows::subsystem::subsystem,
         virtual public ::innate_subsystem_win32::subsystem
      {
      public:



         subsystem();
         ~subsystem() override;





          int message_box(
            WindowInterface * pwindow,
            const ::scoped_string & scopedstrMessage,
            const ::scoped_string & scopedstrCaption,
            unsigned int uType) override;



      };



   } // namespace innate_subsystem_win32




} // namespace windows
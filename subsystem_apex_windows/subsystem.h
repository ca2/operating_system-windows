//
// Created by camilo on 2026-04-06 10:58 <3ThomasBorregaardSørensen!!
//

#pragma once


#include "subsystem_win32/subsystem.h"
#include "subsystem_apex/subsystem.h"

namespace innate_subsystem_win32
{


   class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 subsystem :
      virtual public ::subsystem_win32::subsystem,
      virtual public ::subsystem_apex::subsystem
   {
   public:



      subsystem();
      ~subsystem() override;





       int message_box(
       const ::user_interaction_sink & userinteractionsink,
         const ::scoped_string & scopedstrMessage,
         const ::scoped_string & scopedstrCaption,
         unsigned int uType) override;

        ::user::enum_key virtual_key_code_to_user_key(int iVirtualKeyCode) override;

   };



} // namespace innate_subsystem_win32





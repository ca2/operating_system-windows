#include "framework.h"
#include "system_interaction.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/platform/node.h"
#include "aura/message/user.h"
#include "aura/platform/system.h"


#include "acme/_operating_system.h"


namespace windowing_win32
{



   system_interaction::system_interaction()
   {

      m_ewindowflag -= e_window_flag_graphical;
      m_bCompositedFrameWindow = false;
      //m_bMessageWindow = true;


   }


   system_interaction::~system_interaction()
   {

   }


   void system_interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      //USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &system_interaction::on_message_create);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &system_interaction::on_message_destroy);
      USER_MESSAGE_LINK(::user::e_message_display_change, pchannel, this, &system_interaction::_001OnMessage);
      USER_MESSAGE_LINK(::user::e_message_setting_change, pchannel, this, &system_interaction::_001OnMessage);
      USER_MESSAGE_LINK(::user::e_message_font_change, pchannel, this, &system_interaction::_001OnMessage);
      

   }



   bool system_interaction::is_system_message_window()
   {

      return true;

   }


   void system_interaction::start_destroying_window()
   {

      //return 
      
      ::user::interaction::start_destroying_window();

   }


   void system_interaction::on_message_destroy(::message::message * pmessage)
   {

      //::finalize_windows_devices();

      system()->m_phardwaredevices.release();

      ::pointer<::user::message>pusermessage(pmessage);

      ::output_debug_string("system_interaction::on_message_destroy");

   }

   
   void system_interaction::_001OnMessage(::message::message * pmessage)
   {

      if (pmessage != nullptr)
      {

         wparam wparam = pmessage->m_wparam;

         lparam lparam = pmessage->m_lparam;

         string strLparamString;

         if (pmessage->m_eusermessage == (enum_message) WM_SETTINGCHANGE && wparam == 0)
         {

            strLparamString = (const WCHAR *)(LPARAM(lparam));

         }

         if (pmessage->m_eusermessage == (enum_message) WM_FONTCHANGE)
         {

            auto psystem = system();

            psystem->signal(id_operating_system_font_list_change);/*

            psystem->handle_subject(ptopic);*/

            //fork([this]()
              // {

                 // psession->call(e_routine_font_change);

               //});

         //}
         }
         else if (
            pmessage->m_eusermessage == (enum_message) WM_SETTINGCHANGE &&
            strLparamString == "ImmersiveColorSet")
         {

            auto psystem = system();

            psystem->m_pnode->fetch_user_color();

            /*auto ptopic = psystem->topic(id_os_dark_mode);

            psystem->handle_subject(ptopic);*/

         }
         else if (pmessage->m_eusermessage == ::user::e_message_display_change ||
            (pmessage->m_eusermessage == (enum_message) WM_SETTINGCHANGE &&
               (pmessage->m_wparam == SPI_SETWORKAREA)))
         {

            output_debug_string("WM_SETTINGCHANGE SPI_SETWORKAREA");

            //throw_todo();

            //psystem->enum_display_monitors();

            //::pointer<::user::interaction>puserinteraction;

            //while(psystem->get_frame(puserinteraction))
            //{

            //   try
            //   {

            //      puserinteraction->post_message(::user::e_message_display_change);

            //   }
            //   catch(...)
            //   {
            //   }

            //}


         }

      }


   }




   //void system_interaction::initialize_windows_devices()
   //{

   //   ::initialize_windows_devices(this);

   //}


} // namespace windowing_win32




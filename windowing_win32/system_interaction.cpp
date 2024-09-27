#include "framework.h"
#include "system_interaction.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/platform/node.h"
#include "acme/windowing_system/windowing_system.h"
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

      //MESSAGE_LINK(MESSAGE_CREATE, pchannel, this, &system_interaction::on_message_create);
      MESSAGE_LINK(MESSAGE_DESTROY, pchannel, this, &system_interaction::on_message_destroy);
      MESSAGE_LINK(e_message_display_change, pchannel, this, &system_interaction::_001OnMessage);
      MESSAGE_LINK(e_message_setting_change, pchannel, this, &system_interaction::_001OnMessage);
      MESSAGE_LINK(e_message_font_change, pchannel, this, &system_interaction::_001OnMessage);
      

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

      //system()->m_paurasystem->m_phardwaredevices.release();

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

         if (pmessage->m_atom == (enum_message) WM_SETTINGCHANGE && wparam == 0)
         {

            strLparamString = (const WCHAR *)(LPARAM(lparam));

         }

         if (pmessage->m_atom == (enum_message) WM_FONTCHANGE)
         {

            auto psystem = system()->m_paurasystem;

            psystem->signal(id_operating_system_font_list_change);/*

            psystem->handle_subject(ptopic);*/

            //fork([this]()
              // {

                 // psession->call(e_routine_font_change);

               //});

         //}
         }
         else if (
            pmessage->m_atom == (enum_message) WM_SETTINGCHANGE &&
            strLparamString == "ImmersiveColorSet")
         {

            system()->windowing_system()->fetch_system_background_color();

            /*auto ptopic = psystem->topic(id_os_dark_mode);

            psystem->handle_subject(ptopic);*/

         }
         else if (pmessage->m_atom == e_message_display_change ||
            (pmessage->m_atom == (enum_message) WM_SETTINGCHANGE &&
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

            //      puserinteraction->post_message(e_message_display_change);

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




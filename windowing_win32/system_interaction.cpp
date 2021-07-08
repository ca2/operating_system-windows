#include "framework.h"
#include "aura/message.h"
#include "aura/procedure.h"
#include "system_interaction.h"


namespace windowing_win32
{


   system_interaction::system_interaction()
   {

      m_ewindowflag -= e_window_flag_graphical;
      //m_bMessageWindow = true;

   }


   system_interaction::~system_interaction()
   {


   }


   void system_interaction::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_destroy, pchannel, this, &system_interaction::on_message_destroy);
      MESSAGE_LINK(e_message_display_change, pchannel, this, &system_interaction::_001OnMessage);
      MESSAGE_LINK(e_message_setting_change, pchannel, this, &system_interaction::_001OnMessage);
      MESSAGE_LINK(e_message_font_change, pchannel, this, &system_interaction::_001OnMessage);

   }


   bool system_interaction::is_system_message_window()
   {

      return true;

   }


   bool system_interaction::start_destroying_window()
   {

      return ::user::interaction::start_destroying_window();

   }


   void system_interaction::on_message_destroy(::message::message * pmessage)
   {

      __pointer(::user::message) pusermessage(pmessage);

      ::output_debug_string("system_interaction::on_message_destroy");

   }

   
   void system_interaction::_001OnMessage(::message::message * pmessage)
   {

      if (pmessage != nullptr)
      {

         wparam wparam = pmessage->m_wparam;

         lparam lparam = pmessage->m_lparam;

         string strLparamString;

         if (pmessage->m_id == WM_SETTINGCHANGE && wparam == 0)
         {

            strLparamString = (const WCHAR *)(LPARAM(lparam));

         }

         if (pmessage->m_id == WM_FONTCHANGE)
         {

            auto psystem = m_psystem->m_paurasystem;

            auto psubject = psystem->subject(id_os_font_change);

            psystem->handle_subject(psubject);

            //fork([this]()
              // {

                 // psession->call(e_routine_font_change);

               //});

         //}
         }
         else if (
            pmessage->m_id == WM_SETTINGCHANGE &&
            strLparamString == "ImmersiveColorSet")
         {

            auto psystem = m_psystem->m_paurasystem;

            auto psubject = psystem->subject(id_os_dark_mode);

            psystem->handle_subject(psubject);

         }
         else if (pmessage->m_id == e_message_display_change ||
            (pmessage->m_id == WM_SETTINGCHANGE &&
               (pmessage->m_wparam == SPI_SETWORKAREA)))
         {

            output_debug_string("test");

            //throw_todo();

            //psystem->enum_display_monitors();

            //__pointer(::user::interaction) puserinteraction;

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


} // namespace windowing_win32




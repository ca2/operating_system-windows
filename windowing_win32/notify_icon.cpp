#include "framework.h"
#include "notify_icon.h"
#include "icon.h"
#include "acme/constant/id.h"
#include "acme/constant/user_message.h"
#include "acme/exception/exception.h"
#include "acme/handler/topic.h"
#include "acme_windowing_win32/activation_token.h"


static ::user::notify_icon * g_pnotifyiconLast = nullptr;


#ifdef LINUX

#include "aura/os/linux/appindicator.h"

#endif


namespace windowing_win32
{


   notify_icon::notify_icon()
   {

      g_pnotifyiconLast = this;

#ifdef WINDOWS_DESKTOP

      m_nid.cbSize = sizeof(m_nid);

#elif defined(LINUX)

      m_pindicator = nullptr;

#endif

      m_bCreated = false;

   }


   notify_icon::~notify_icon()
   {

      destroy_window();

      if (g_pnotifyiconLast == this)
      {

         g_pnotifyiconLast = nullptr;

      }

   }


   void notify_icon::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      USER_MESSAGE_LINK(::user::e_message_notify_icon, pchannel, this, &notify_icon::on_message_notify_icon);
      USER_MESSAGE_LINK(::user::e_message_destroy, pchannel, this, &notify_icon::on_message_destroy);

   }


   void notify_icon::create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon)
   {

      if (!is_window())
      {

         string strId = "notify_icon_" + atom;

         m_strId = "ca2-" + picon->get_tray_icon_name() + "-" + strId;

         create_message_queue(m_strId);

         //if (!create_message_queue(m_strId))
         //{

         //   return false;

         //}

         id() = atom;

      }

      if (m_bCreated)
      {

         m_nid.uFlags = 0;

         if (!Shell_NotifyIcon(NIM_DELETE, &m_nid))
         {

            ::output_debug_string("failed to delete existing Shell Notify Icon");

         }

      }



      m_nid.hWnd = (HWND)HWND_from_acme_windowing_window(m_pacmewindowingwindow);
      m_nid.uID = as_hash32((const ::string &) atom).m_u;
      m_nid.hIcon = (HICON) picon->get_os_data(::int_size(16, 16));
      m_nid.uFlags = NIF_ICON | NIF_MESSAGE;
      m_nid.uCallbackMessage = ::user::e_message_notify_icon;

      m_puserinteractionNotify = puserinteractionNotify;

      if (!Shell_NotifyIcon(NIM_ADD, &m_nid))
      {

         m_puserinteractionNotify.release();

         destroy_window();

         throw ::exception(error_null_pointer);

         //return false;

      }

      m_bCreated = true;

      //return true;

   }


   void notify_icon::modify_icon(::windowing::icon * picon)
   {

      if (!m_bCreated)
      {

         //return error_failed;

         throw ::exception(error_null_pointer);

      }

      m_nid.hIcon = (HICON) picon->get_os_data(::int_size(16, 16));

      m_nid.uFlags = NIF_ICON;

      if (!Shell_NotifyIcon(NIM_MODIFY, &m_nid))
      {

         throw ::exception(error_null_pointer);

      }

      m_piconCurrent = picon;

      //return ::success;

   }


   void notify_icon::add_hidden_window(::user::interaction * puserinteraction)
   {

      //auto estatus = 
      
      ::user::notify_icon::add_hidden_window(puserinteraction);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }




   void notify_icon::destroy_window()
   {

      if (!m_bCreated)
      {

         return;

      }

      main_send([this]()
         {

            m_bCreated = false;

            m_nid.uFlags = 0;

            if (!Shell_NotifyIcon(NIM_DELETE, &m_nid))
            {

               //return false;

            }

            ::user::interaction::destroy_window();

         });

   }


   void notify_icon::erase_all_routes()
   {

      ::user::interaction::erase_all_routes();

   }


   void notify_icon::destroy()
   {

      ::user::interaction::destroy();

   }



//   void notify_icon::destroy_window()
//   {
//
//      if (!m_bCreated)
//      {
//
//         return;
//
//      }
//
//      m_bCreated = false;
//
//
//      ::user::interaction::destroy_window();
//
////      //return true;
////
////
////#elif defined(LINUX) && !defined(RASPBIAN)
////
////      if (m_pindicator)
////      {
////
////         auto pnode = Node;
////
////         pnode->appindicator_destroy(m_pindicator);
////
////         m_pindicator = nullptr;
////
////      }
////
////      return true;
////
////#elif defined(MACOS)
////
////      notify_icon_destroy();
////
////      return true;
////
////#else
////
////
////      throw ::exception(todo);
////
////      return true;
////
////#endif
//
//   }


   void notify_icon::on_message_destroy(::message::message * pmessage)
   {

      output_debug_string("notify_icon::on_message_destroy");

   }


   void notify_icon::on_message_notify_icon(::message::message * pmessage)
   {

      enum_message emessage = (enum_message) pmessage->m_lparam.m_lparam;

      if (emessage == ::user::e_message_left_button_down)
      {

         while (m_userinteractionaHidden.get_size() > 0)
         {

            try
            {

               ::pointer<::user::interaction>pframe = (m_userinteractionaHidden.element_at(0));

               if (pframe != nullptr)
               {

                  pframe->display(e_display_normal);

               }
               else
               {

                  m_userinteractionaHidden.element_at(0)->display(e_display_normal);

               }

            }
            catch (...)
            {

            }

            m_userinteractionaHidden.erase_at(0);

         }

      }

      ::topic_pointer ptopic;

      if (emessage == ::user::e_message_right_button_down)
      {

         ptopic = create_topic(::id_context_menu);

      }
      else if (emessage == ::user::e_message_left_button_double_click)
      {

         ptopic = create_topic(::id_left_button_double_click);

      }
      else if (emessage == ::user::e_message_left_button_down)
      {

         ptopic = create_topic(::id_left_button_down);

      }
      else
      {

         ptopic = create_topic(emessage);

      }

      ptopic->m_puserelement = this;

      if (!pmessage->m_actioncontext.m_puseractivationtoken)
      {

         pmessage->m_actioncontext.m_puseractivationtoken = øallocate::win32::acme::windowing::activation_token(::get_task());

      }

      ptopic->m_actioncontext.m_pmessage = pmessage;

      m_puserinteractionNotify->handle(ptopic, nullptr);

   }


   //void notify_icon::notify_icon_play(const ::scoped_string & scopedstrAction)
   //{


   //}


   bool notify_icon::notify_icon_step()
   {

#if defined(LINUX)

      //      main_async([&]
      //      {
      //
      //         linux_g_direct_app_indicator_step(m_pindicator);
      //
      //      });

#endif

      return true;

   }


//#if defined(LINUX) || defined(MACOS)
//
//
//   int notify_icon::_get_notification_area_action_count()
//   {
//
//      return m_plistener->_get_notification_area_action_count();
//
//   }
//
//
//   const_char_pointer notify_icon::_get_notification_area_action_name(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_name(iIndex);
//
//   }
//
//
//   const_char_pointer notify_icon::_get_notification_area_action_id(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_id(iIndex);
//
//   }
//
//
//   const_char_pointer notify_icon::_get_notification_area_action_label(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_label(iIndex);
//
//   }
//
//
//   const_char_pointer notify_icon::_get_notification_area_action_accelerator(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_accelerator(iIndex);
//
//   }
//
//
//   const_char_pointer notify_icon::_get_notification_area_action_description(int iIndex)
//   {
//
//      return m_plistener->_get_notification_area_action_description(iIndex);
//
//   }
//
//
//   void notify_icon::call_notification_area_action(const ::scoped_string & scopedstrId)
//   {
//
//      m_plistener->call_notification_area_action(pszId);
//
//   }
//
//
//#endif


} // namespace windowing_win32




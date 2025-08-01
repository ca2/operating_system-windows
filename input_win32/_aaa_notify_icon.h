#pragma once


#include "aura/user/user/notify_icon.h"


#include "acme/_operating_system.h"


#include <shellapi.h>


//#if defined (__APPLE__)
//#include "notify_icon_mm_bridge.h"
//#endif
//
//
//
//
//#ifdef LINUX
//#include "apex/user/notify_icon_bridge.h"
//namespace linux { class appindicator; }
//#endif
//

namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 notify_icon :
      virtual public ::user::notify_icon
   {
   public:


      //__creatable_from_base(notify_icon, ::user::notify_icon);


      enum e_message
      {

         MessageNotifyIcon = WM_USER + 100,

      };


      /*unsigned int     m_uiId;
      bool     m_bCreated;
      string   m_strId;
#ifdef WINDOWS_DESKTOP*/
      NOTIFYICONDATA m_nid;
//#elif defined(LINUX)
//      ::linux::appindicator * m_pindicator;
//#endif
//      notify_icon_listener * m_plistener;
//      pointer_array < ::user::interaction >   m_wndptraHidden;
//      ::pointer<::image::icon>          m_piconCurrent;


      notify_icon();
      ~notify_icon() override;


      void add_hidden_window(::user::interaction * puserinteraction) override;

#ifdef WINDOWS_DESKTOP

      virtual void erase_all_routes() override;

      virtual void start_destroying_window() override;

      virtual void destroy_window() override;

      virtual void post_non_client_destroy() override;

#else

      virtual bool DestroyWindow();

#endif


      void modify_icon(::windowing::icon * picon) override;

      
      void create_notify_icon(const ::atom & atom, ::user::interaction * puserinteractionNotify, ::windowing::icon * picon) override;


      DECLARE_MESSAGE_HANDLER(on_message_notify_icon);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      void install_message_routing(::channel * pchannel) override;

      bool step() override;

//#if defined(APPLE_IOS) || defined(WINDOWS_DESKTOP) || defined(ANDROID) || defined(UNIVERSAL_WINDOWS)
//      virtual void notify_icon_play(const ::scoped_string & scopedstrAction);
//#else
//#if defined(LINUX)
//      virtual void notify_icon_play(const ::scoped_string & scopedstrAction);
//#else
//      virtual void notify_icon_play(const ::scoped_string & scopedstrAction) override;
//#endif
//      virtual int _get_notification_area_action_count() override;
//      virtual const_char_pointer _get_notification_area_action_name(int iIndex) override;
//      virtual const_char_pointer _get_notification_area_action_id(int iIndex) override;
//      virtual const_char_pointer _get_notification_area_action_label(int iIndex) override;
//      virtual const_char_pointer _get_notification_area_action_accelerator(int iIndex) override;
//      virtual const_char_pointer _get_notification_area_action_description(int iIndex) override;
//      virtual void call_notification_area_action(const ::scoped_string & scopedstrId) override;
//#endif


   };


} // namespace user



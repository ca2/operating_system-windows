// created by Camilo <3ThomasBorregaardSoerensen_!!
// recreated by Camilo 2021-02-02 16:49
#pragma once


#include "aura/windowing/display.h"
#include "aura/hardware/device_listener.h"
#include "acme_windowing_win32/display.h"


#include "acme/_operating_system.h"


namespace windowing_win32
{

   // X11 contribution : a display may contain more than one monitor

   class CLASS_DECL_WINDOWING_WIN32 display :
      virtual public ::windowing::display,
      virtual public ::hardware::device_listener,
      virtual public ::win32::acme::windowing::display
   {
   public:


      //__creatable_and_from_base(display, ::windowing::display);


#ifdef WINDOWS_DESKTOP

      
#else

      //::i32_rectangle_array_base                                         m_rectangleaMonitor;
      //::i32_rectangle_array_base                                             m_rectangleaWork;

      ::i32_rectangle_array_base                                               m_rectangleaMonitor;
      ::i32_rectangle_array_base                                               m_rectangleaWkspace;
#endif
      //#pragma message("at macos??")
      raw_array_base < MONITORINFO >                     m_monitorinfoa;
      comparable_array < HMONITOR >                      m_hmonitora;
      raw_array_base < MONITORINFO >                     m_monitorinfoaDesk;


      display();
      ~display() override;


      void open_display() override;
      void finalize_display() override;

      virtual void update_dpi();

      void enum_display_monitors() override;

      ::collection::index get_main_monitor_index() override;

      ::collection::index get_main_monitor(::i32_rectangle & rectangle) override;

      ::collection::count get_monitor_count() override;
      //virtual bool  get_monitor_rect(::collection::index iMonitor, ::i32_rectangle * prectangle) override;

      ::collection::count get_desk_monitor_count() override;
      //virtual bool  get_desk_monitor_rect(::collection::index iMonitor, ::i32_rectangle * prectangle) override;


      ::collection::index get_main_workspace(::i32_rectangle & rectangle) override;

      ///::collection::count get_workspace_count() override;
      //virtual bool  get_wkspace_rect(::collection::index iWkspace, ::i32_rectangle * prectangle) override;

      //::collection::count get_desk_workspace_count() override;
      //virtual bool  get_desk_wkspace_rect(::collection::index iWkspace, ::i32_rectangle * prectangle) override;

      //virtual ::collection::index get_ui_wkspace(::user::interaction * pinteraction) override;


      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT prcMonitor, LPARAM dwData);


      virtual void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT prcMonitor);

      bool set_main_monitor(::collection::index iMonitor) override;

      //virtual bool wkspace_to_monitor(::i32_rectangle * prectangle, ::collection::index iMonitor, ::collection::index iWkspace) override;

      //virtual bool monitor_to_wkspace(::i32_rectangle * prectangle, ::collection::index iWkspace, ::collection::index iMonitor) override;

      //virtual bool wkspace_to_monitor(::i32_rectangle * prectangle) override;

      //virtual bool monitor_to_wkspace(::i32_rectangle * prectangle) override;


      virtual void _get_monitor(::i32_rectangle_array_base & rectaMonitor, ::i32_rectangle_array_base& rectaIntersect, const i32_rectangle & rectangleParam);

      virtual ::collection::index _get_best_zoneing(::e_display * pedisplay, ::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, bool bPreserveSize = false) override;

      ::collection::index get_best_monitor(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, const ::user::activation & useractivation = {}, ::user::interaction * puserinteractionCursorPosition = nullptr) override;

      ::collection::index get_best_workspace(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, const ::user::activation & useractivation = {}, ::user::interaction * puserinteractionCursorPosition = nullptr) override;

      ::collection::index get_good_iconify(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle) override;

      //virtual ::collection::index get_window_restore_1(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore);

      //virtual ::collection::index get_window_restore_2(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore);

      //virtual ::collection::index get_good_move(::i32_rectangle * prectangle, const ::i32_rectangle & rectangle, ::user::interaction * pinteraction);


      void _set_wallpaper(::collection::index iScreen, const ::scoped_string & scopedstrLocalImagePath) override;
      string _get_wallpaper(::collection::index iScreen) override;

      void on_device_plugged(::hardware::enum_device edevice) override;
      void on_device_unplugged(::hardware::enum_device edevice) override;

      
      ::i32_point _get_mouse_cursor_position() override;


      virtual bool _get_monitor_rectangle(::collection::index iMonitor, ::i32_rectangle & rectangle);
      virtual bool _get_workspace_rectangle(::collection::index iMonitor, ::i32_rectangle & rectangle);


      ::i32_size get_main_screen_size() override;


   };


} // namespace windowing_win32




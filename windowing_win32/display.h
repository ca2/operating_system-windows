// created by Camilo <3ThomasBorregaardSoerensen_!!
// recreated by Camilo 2021-02-02 16:49
#pragma once


namespace windowing_win32
{

   // X11 contribution : a display may contain more than one monitor

   class CLASS_DECL_WINDOWING_WIN32 display :
      virtual public ::windowing::display
   {
   public:



#ifdef WINDOWS_DESKTOP


#else

      //rect_array                                         m_rectaMonitor;
      //rect_array                                             m_rectaWork;

      rect_array                                               m_rectaMonitor;
      rect_array                                               m_rectaWkspace;
#endif
      //#pragma message("at macos??")
      raw_array < MONITORINFO >                          m_monitorinfoa;
      comparable_array < HMONITOR >                      m_hmonitora;
      raw_array < MONITORINFO >                          m_monitorinfoaDesk;





      display();
      virtual ~display();


      virtual ::e_status initialize_display(::windowing::windowing * pwindowing) override;


      virtual void update_dpi();

      virtual void enum_display_monitors() override;

      virtual ::index get_main_monitor(RECTANGLE_I32 * prectangle = nullptr) override;

      virtual ::count get_monitor_count() override;
      virtual bool  get_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle) override;

      virtual ::count get_desk_monitor_count() override;
      virtual bool  get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle) override;


      virtual index get_main_wkspace(RECTANGLE_I32 * prectangle = nullptr) override;

      virtual ::count get_wkspace_count() override;
      virtual bool  get_wkspace_rect(index iWkspace, RECTANGLE_I32 * prectangle) override;

      virtual ::count get_desk_wkspace_count() override;
      virtual bool  get_desk_wkspace_rect(index iWkspace, RECTANGLE_I32 * prectangle) override;

      //virtual index get_ui_wkspace(::user::interaction * pinteraction) override;


      static BOOL CALLBACK monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT prcMonitor, LPARAM dwData);


      virtual void monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT prcMonitor);


      virtual bool set_main_monitor(index iMonitor);


      virtual bool wkspace_to_monitor(RECTANGLE_I32 * prectangle, index iMonitor, index iWkspace) override;

      virtual bool monitor_to_wkspace(RECTANGLE_I32 * prectangle, index iWkspace, index iMonitor) override;

      virtual bool wkspace_to_monitor(RECTANGLE_I32 * prectangle) override;

      virtual bool monitor_to_wkspace(RECTANGLE_I32 * prectangle) override;


      virtual void get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const rectangle_i32 & rectParam) override;


      virtual index _get_best_zoneing(edisplay * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, bool bPreserveSize = false);

      virtual index get_best_monitor(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation = e_activation_default);

      virtual index get_best_wkspace(::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangle, ::e_activation eactivation = e_activation_default);

      virtual index get_good_iconify(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle);

      //virtual index get_window_restore_1(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore);

      //virtual index get_window_restore_2(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction, edisplay edisplayRestore);

      //virtual index get_good_move(RECTANGLE_I32 * prectangle, const ::rectangle_i32 & rectangle, ::user::interaction * pinteraction);


      virtual bool impl_set_wallpaper(index iScreen, string strLocalImagePath) override;
      virtual string impl_get_wallpaper(index iScreen) override;


   };


} // namespace windowing_win32




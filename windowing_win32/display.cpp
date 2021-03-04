// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard S�rensen MY ONLY LORD
// recreated by Camilo 2021-02-02 20:55
#include "framework.h"


namespace windowing_win32
{


   display::display()
   {


   }
   
   
   display::~display()
   {


   }


   void display::enum_display_monitors()
   {

#ifdef WINDOWS_DESKTOP

      m_monitorinfoa.remove_all();

      ::EnumDisplayMonitors(nullptr, nullptr, &display::monitor_enum_proc, (LPARAM)this);

      synchronization_lock synchronizationlock(mutex());

      m_monitora.remove_all();

      for (index iMonitor = 0; iMonitor < m_monitorinfoa.get_count(); iMonitor++)
      {

         auto pmonitor = __new(monitor(m_hmonitora[iMonitor]));

         pmonitor->m_iIndex = iMonitor;

         m_monitora.add(pmonitor);

         __copy(pmonitor->m_rectangle, m_monitorinfoa[iMonitor].rcMonitor);

         __copy(pmonitor->m_rectangleWorkspace, m_monitorinfoa[iMonitor].rcWork);

      }

#elif defined(LINUX)

      ::enum_display_monitors(this);

#endif

   }



   index display::get_main_monitor(RECTANGLE_I32 * prectangle)
   {

      index iMainMonitor = 0;

      HMONITOR hmonitorPrimary = get_primary_monitor_handle();

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         if (m_hmonitora[iMonitor] == hmonitorPrimary)
         {

            iMainMonitor = iMonitor;

            break;

         }

      }

      if (prectangle != nullptr)
      {

         auto pmonitor = get_monitor(iMainMonitor);

         if (::is_null(pmonitor))
         {

            return -1;

         }

         if (!pmonitor->get_monitor_rectangle(prectangle))
         {

            return -1;

         }

      }

      return iMainMonitor;

   }


   ::count display::get_monitor_count()
   {

#ifdef WINDOWS_DESKTOP

      return m_monitorinfoa.get_count();

#elif defined(MACOS)

      return GetScreenCount();

#elif defined(LINUX)

      synchronization_lock synchronizationlock(mutex());

      return m_rectaMonitor.get_count();

#else

      return 1;

#endif

   }


//   bool display::get_monitor_rectangle(index iMonitor, RECTANGLE_I32 * prectangle)
//   {
//
//#ifdef _UWP
//
//      return false;
//
//      //prectangle->left = 0;
//
//      //prectangle->top = 0;
//
//      //auto puserinteraction = __user_interaction(m_puiHost);
//
//      //prectangle->right = puserinteraction->layout().sketch().width();
//
//      //prectangle->bottom = puserinteraction->layout().sketch().height();
//
//      //return true;
//
//#elif MOBILE_PLATFORM
//
//      GetMainScreenRect(prectangle);
//
//      return true;
//
//#elif defined(WINDOWS_DESKTOP)
//
//      if (iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//
//      __copy(prectangle, m_monitorinfoa[iMonitor].rcMonitor);
//
//
//#elif defined(_UWP)
//
//
//      return false;
//
//
//#elif defined(LINUX)
//
//      synchronization_lock synchronizationlock(mutex());
//
//      if (iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//
//      *prectangle = m_rectaMonitor[iMonitor];
//
//
//#elif defined(__APPLE__)
//
//      if (iMonitor < 0 || iMonitor >= get_monitor_count())
//      {
//
//         return false;
//
//      }
//
//      GetScreenRect(prectangle, (int)iMonitor);
//
//
//#else
//
//      prectangle->left = 0;
//
//      prectangle->top = 0;
//
//      prectangle->right = oslocal().m_iScreenWidth;
//
//      prectangle->bottom = oslocal().m_iScreenHeight;
//
//
//#endif
//
//      return true;
//
//   }
//

   ::count display::get_desk_monitor_count()
   {

      return get_monitor_count();

   }


   //bool display::get_desk_monitor_rect(index iMonitor, RECTANGLE_I32 * prectangle)

   //{

   //   return get_monitor_rect(iMonitor, prectangle);


   //}


   index display::get_main_workspace(RECTANGLE_I32 * prectangle)

   {

      index iMainWkspace = 0;

      HMONITOR hwkspacePrimary = get_primary_monitor_handle();

      for (index iWkspace = 0; iWkspace < get_workspace_count(); iWkspace++)
      {

         if (m_hmonitora[iWkspace] == hwkspacePrimary)
         {

            iMainWkspace = iWkspace;

            break;

         }

      }


      if (prectangle != nullptr)
      {

         auto pmonitor = get_monitor(iMainWkspace);

         if (::is_null(prectangle))
         {

            return -1;

         }

         pmonitor->get_workspace_rectangle(prectangle);

      }

      return iMainWkspace;

   }


   ::count display::get_workspace_count()
   {

#ifdef WINDOWS_DESKTOP

      return m_monitorinfoa.get_count();

#else

      return get_monitor_count();

#endif

   }


//   bool display::get_wkspace_rect(index iWkspace, RECTANGLE_I32 * prectangle)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//         return false;
//
//      __copy(prectangle, m_monitorinfoa[iWkspace].rcWork);
//
//
//#elif defined(_UWP)
//
//      return get_monitor_rect(iWkspace, prectangle);
//
//
//      //#elif defined(LINUX)
//      //
//      //return false;
//      //
//#elif defined(__APPLE__)
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//      {
//
//         return false;
//
//      }
//
//      GetWkspaceRect(prectangle, (int)iWkspace);
//
//
//      //      prectangle->top += ::mac::get_system_main_menu_bar_height();
//
//      //    prectangle->bottom -= ::mac::get_system_dock_height();
//
//#elif defined(LINUX)
//
//      synchronization_lock synchronizationlock(mutex());
//
//      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
//      {
//
//         return false;
//
//      }
//
//      *prectangle = m_rectaWkspace[iWkspace];
//
//
//      return true;
//
//#else
//
//      //__throw(todo);
//
//      //::get_window_rect(::get_desktop_window(),prectangle);
//
//
//      get_monitor_rect(iWkspace, prectangle);
//
//
//#endif
//
//      return true;
//
//   }


   ::count display::get_desk_workspace_count()
   {

      return get_workspace_count();

   }


   //bool display::get_desk_wkspace_rect(index iWkspace, RECTANGLE_I32 * prectangle)

   //{

   //   return get_wkspace_rect(iWkspace, prectangle);


   //}


   bool display::set_main_monitor(index iMonitor)
   {

      if (iMonitor == -1)
      {

         m_iMainMonitor = -1;

         return true;

      }
      else if (iMonitor < 0 || iMonitor >= get_monitor_count())
      {

         return false;

      }
      else
      {

         m_iMainMonitor = iMonitor;

         return true;

      }

   }


   //bool display::wkspace_to_monitor(RECTANGLE_I32 * prectangle, index iMonitor, index iWkspace)
   //{

   //   ::rectangle_i32 rectangle(*prectangle);

   //   ::rectangle_i32 rectWkspace;

   //   if (!get_wkspace_rect(iWkspace, rectWkspace))
   //   {

   //      return false;

   //   }

   //   rectangle -= rectWkspace.top_left();

   //   ::rectangle_i32 rectMonitor;

   //   if (!get_monitor_rect(iMonitor, rectMonitor))
   //   {

   //      return false;

   //   }

   //   rectangle += rectMonitor.top_left();

   //   *prectangle = rectangle;

   //   return true;

   //}


   //bool display::wkspace_to_monitor(RECTANGLE_I32 * prectangle)
   //{

   //   index iWkspace = get_best_wkspace(nullptr, rectangle_i32(prectangle));

   //   return wkspace_to_monitor(prectangle, iWkspace, iWkspace);

   //}


   //bool display::monitor_to_wkspace(RECTANGLE_I32 * prectangle)
   //{

   //   index iMonitor = get_best_monitor(nullptr, rectangle_i32(prectangle));

   //   return monitor_to_wkspace(prectangle, iMonitor, iMonitor);

   //}


   //bool display::monitor_to_wkspace(RECTANGLE_I32 * prectangle, index iWkspace, index iMonitor)
   //{

   //   ::rectangle_i32 rectangle(prectangle);

   //   ::rectangle_i32 rectMonitor;

   //   if (!get_monitor_rect(iMonitor, rectMonitor))
   //   {

   //      return false;

   //   }

   //   rectangle -= rectMonitor.top_left();

   //   ::rectangle_i32 rectWkspace;

   //   if (!get_wkspace_rect(iWkspace, rectWkspace))
   //   {

   //      return false;

   //   }

   //   rectangle += rectWkspace.top_left();

   //   *prectangle = rectangle;

   //   return true;

   //}


   void display::_get_monitor(rect_array & rectaMonitor, rect_array & rectaIntersect, const rectangle_i32 & rectParam)
   {

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectIntersect;

         ::rectangle_i32 rectMonitor;

         auto pmonitor = get_monitor(iMonitor);

         if (pmonitor->get_monitor_rectangle(rectMonitor))
         {

         }

         if (rectIntersect.top_left_null_intersect(&rectParam, rectMonitor))
         {

            if (rectIntersect.area() >= 0)
            {

               rectaMonitor.add(rectMonitor);

               rectaIntersect.add(rectIntersect);

            }

         }

      }

   }




   ::mutex g_monitor_adjust;



   #define ZONEING_COMPARE ::comparison

   i64 g_i_get_best_zoneing = 0;

   
   index display::_get_best_zoneing(edisplay * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectRequest, bool bPreserveSize)
   {

      ::rectangle_i32 rectangle(rectRequest);

      ::rectangle_i32 rectWkspace;

      index iBestWkspace = get_best_wkspace(&rectWkspace, rectangle);

      edisplay edisplay;

      ::e_display edisplayPrevious = *pedisplay;

      double dMargin = System->m_dpi;

      if (ZONEING_COMPARE::is_equal(rectangle.top, rectWkspace.top, dMargin, !(edisplayPrevious & e_display_top)))
      {

         edisplay |= e_display_top;

         if (bPreserveSize)
         {

            rectangle.move_top_to(rectWkspace.top);

         }
         else
         {

            rectangle.top = rectWkspace.top;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectangle.bottom, rectWkspace.bottom, dMargin, !(edisplayPrevious & e_display_bottom)))
      {

         edisplay |= e_display_bottom;

         if (bPreserveSize)
         {

            rectangle.move_bottom_to(rectWkspace.bottom);

         }
         else
         {

            rectangle.bottom = rectWkspace.bottom;

         }

      }

      if (ZONEING_COMPARE::is_equal(rectRequest.left, rectWkspace.left, dMargin, !(edisplayPrevious & e_display_left)))
      {

         edisplay |= e_display_left;

         if (bPreserveSize)
         {

            rectangle.move_left_to(rectWkspace.left);

         }
         else
         {

            rectangle.left = rectWkspace.left;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectRequest.right, rectWkspace.right, dMargin, !(edisplayPrevious & e_display_right)))
      {

         edisplay |= e_display_right;

         if (bPreserveSize)
         {

            rectangle.move_right_to(rectWkspace.right);

         }
         else
         {

            rectangle.right = rectWkspace.right;

         }

      }

      if (!(edisplay & e_display_top || edisplay & e_display_bottom)
         && is_different(edisplay & e_display_left, edisplay & e_display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.top, rectangle.top, rectangle.bottom, rectWkspace.bottom))
         {

            edisplay |= e_display_bottom;

            edisplay |= e_display_top;

            rectangle.bottom = rectWkspace.bottom;

            rectangle.top = rectWkspace.top;

         }

      }

      if (!(edisplay & e_display_left || edisplay & e_display_right)
         && is_different(edisplay & e_display_top, edisplay & e_display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectWkspace.left, rectangle.left, rectangle.right, rectWkspace.right))
         {

            edisplay |= e_display_left;

            edisplay |= e_display_right;

            rectangle.left = rectWkspace.left;

            rectangle.right = rectWkspace.right;

         }

      }

      bool bLeftXorRight = is_different(edisplay & e_display_left, edisplay & e_display_right);

      bool bTopXorBottom = is_different(edisplay & e_display_top, edisplay & e_display_bottom);

      bool bTopAndBottom = edisplay & e_display_top && edisplay & e_display_bottom;

      bool bLeftAndRight = edisplay & e_display_left && edisplay & e_display_right;

      if (bLeftXorRight && bTopXorBottom)
      {

      }
      else if (bTopAndBottom && bLeftAndRight)
      {

         edisplay = e_display_zoomed;

      }
      else
      {

         if (bLeftXorRight && !bTopAndBottom)
         {

            edisplay = e_display_none;

         }

         if (bTopXorBottom && !bLeftAndRight)
         {

            edisplay = e_display_none;

         }

         if (bTopAndBottom)
         {

            edisplay -= e_display_top;

            edisplay -= e_display_bottom;

         }

         if (bLeftAndRight)
         {

            edisplay -= e_display_left;

            edisplay -= e_display_right;

         }

      }

      if (edisplay == e_display_none)
      {

         edisplay = e_display_normal;

      }

      if (is_docking_appearance(edisplay))
      {

         *prectangle = rectangle;

      }
      else if (edisplay == e_display_zoomed)
      {

         *prectangle = rectWkspace;

      }
      else
      {

         *prectangle = rectRequest;

      }

      if (pedisplay)
      {

         *pedisplay = edisplay;

      }

      //if (g_i_get_best_zoneing % 10 == 0)
      //{

      //   string strE("e");
      //   if (edisplay & e_display_left)
      //      strE += "L";
      //   if (edisplay & e_display_top)
      //      strE += "T";
      //   if (edisplay & e_display_right)
      //      strE += "R";
      //   if (edisplay & e_display_bottom)
      //      strE += "B";

      //   string strP("p");
      //   if (edisplayPrevious & e_display_left)
      //      strP += "L";
      //   if (edisplayPrevious & e_display_top)
      //      strP += "T";
      //   if (edisplayPrevious & e_display_right)
      //      strP += "R";
      //   if (edisplayPrevious & e_display_bottom)
      //      strP += "B";

      //   ::output_debug_string(
      //      "w" + ::str::from(rectWkspace.left) + ","
      //      + ::str::from(rectWkspace.top) + ","
      //      + ::str::from(rectWkspace.right) + ","
      //      + ::str::from(rectWkspace.bottom) + " " +
      //      "r" + ::str::from(prectangle->left) + ","
      //      + ::str::from(prectangle->top) + ","
      //      + ::str::from(prectangle->right) + ","
      //      + ::str::from(prectangle->bottom) + " " +
      //      strE + " " + strP + "\n");

      //}


      //g_i_get_best_zoneing++;

      //   rectWkspace.left,
      //   rectWkspace.top,
      //   rectWkspace.right,
      //   rectWkspace.bottom,
      //   (edisplay & e_display_left)?'L':' ',
      //   (edisplay & e_display_top) ? 'T':' ',
      //   (edisplay & e_display_right) ? 'R':' ',
      //   (edisplay & e_display_bottom) ? 'B':' ',
      //   (edisplayPrevious & e_display_left) ? 'L':' ',
      //   (edisplayPrevious & e_display_top) ? 'T':' ',
      //   (edisplayPrevious & e_display_right) ? 'R':' ',
      //   (edisplayPrevious & e_display_bottom) ? 'B':' ');

      return iBestWkspace;

   }


   index display::get_best_monitor(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam, ::e_activation eactivation)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectMatch;

      ::rectangle_i32 rectangle(rectParam);

      if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      {

         ::point_i32 pointCursor = m_pwindowing->get_cursor_position();

         rectangle.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

      }

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectIntersect;

         ::rectangle_i32 rectMonitor;

         auto pmonitor = get_monitor(iMonitor);

         if (pmonitor->get_monitor_rectangle(rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rectangle, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rectangle))
            {

               iMatchingMonitor = iMonitor;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingMonitor >= 0)
      {

         if (prectangle != nullptr)
         {

            *prectangle = rectMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(prectangle);

      return iMatchingMonitor;

   }


   index display::get_best_wkspace(::rectangle_i32 * prectangle, const rectangle_i32 & rectParam, ::e_activation eactivation)
   {

      index iMatchingWkspace = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectMatch;

      ::rectangle_i32 rectangle(rectParam);

      if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      {

         ::point_i32 pointCursor = m_pwindowing->get_cursor_position();

         rectangle.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

      }

      for (index iWorkspace = 0; iWorkspace < get_workspace_count(); iWorkspace++)
      {

         ::rectangle_i32 rectIntersect;

         ::rectangle_i32 rectMonitor;

         auto pmonitor = get_monitor(iWorkspace);

         if (pmonitor->get_workspace_rectangle(rectMonitor))
         {

            if (rectIntersect.top_left_null_intersect(rectangle, rectMonitor))
            {

               if (rectIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWorkspace;

                  iBestArea = rectIntersect.area();

                  rectMatch = rectMonitor;

               }

            }
            else if (rectMonitor.contains(rectangle))
            {

               iMatchingWkspace = iWorkspace;

               rectMatch = rectMonitor;

            }

         }

      }

      if (iMatchingWkspace >= 0)
      {

         if (prectangle != nullptr)
         {

            *prectangle = rectMatch;

         }

         return iMatchingWkspace;

      }

      iMatchingWkspace = get_main_workspace(prectangle);

      return iMatchingWkspace;

   }


   index display::get_good_iconify(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectParam)
   {

      ::rectangle_i32 rectMonitor;

      index iMatchingMonitor = get_best_monitor(rectMonitor, rectParam);

      prectangle->left = rectMonitor.left;

      prectangle->top = rectMonitor.top;

      prectangle->right = rectMonitor.left;

      prectangle->bottom = rectMonitor.top;

      return iMatchingMonitor;

   }


   ::e_status display::initialize_display(::windowing::windowing * pwindowing)
   {

      auto estatus = ::windowing::display::initialize_display(pwindowing);

      if (!estatus)
      {

         return estatus;

      }

      m_pwindowing = pwindowing;

      if (!m_pwindowing)
      {
         
         return error_no_interface;

      }

      enum_display_monitors();

      return estatus;

   }


   void display::update_dpi()
   {


#ifdef WINDOWS_DESKTOP

      {

         auto hdc = CreateCompatibleDC(NULL);

         m_dpi = (float)GetDeviceCaps(hdc, LOGPIXELSX);

         ::DeleteDC(hdc);

      }

#else

      m_dpi = 96.0;

#endif


   }



   BOOL CALLBACK display::monitor_enum_proc(HMONITOR hmonitor, HDC hdcMonitor, LPRECT prcMonitor, LPARAM dwData)
   {

      display * pdisplay = (display *)dwData;


      pdisplay->monitor_enum(hmonitor, hdcMonitor, prcMonitor);


      return true; // to enumerate all

   }


   void display::monitor_enum(HMONITOR hmonitor, HDC hdcMonitor, LPRECT prcMonitor)
   {

      UNREFERENCED_PARAMETER(hdcMonitor);
      UNREFERENCED_PARAMETER(prcMonitor);

      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);

      __zero(m_monitorinfoa.last());

      m_hmonitora.add(hmonitor);

      m_monitorinfoa.last().cbSize = sizeof(MONITORINFO);

      ::GetMonitorInfo(hmonitor, &m_monitorinfoa.last());

      MONITORINFO mi = m_monitorinfoa.last();

      TRACE("display::monitor_enum\n");
      TRACE("upper_bound %d\n", m_monitorinfoa.get_upper_bound());
      TRACE("rcMonitor(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom);
      TRACE("rcWork(left, top, right, bottom) %d, %d, %d, %d\n", mi.rcWork.left, mi.rcWork.top, mi.rcWork.right, mi.rcWork.bottom);


   }


   //::index display::get_main_monitor(RECTANGLE_I32 * prectangle)
   //{

   //   const POINT pointZero = { 0, 0 };

   //   HMONITOR hmonitor = MonitorFromPoint(pointZero, MONITOR_DEFAULTTOPRIMARY);

   //   auto iIndex = m_hmonitora.find_first(hmonitor);

   //   if (prectangle)
   //   {

   //      __copy(prectangle, m_monitorinfoa[iIndex].rcMonitor);

   //   }

   //   return iIndex;

   //}


   bool display::impl_set_wallpaper(index iScreen, string strLocalImagePath)
   {

      return SystemParametersInfoW(SPI_SETDESKWALLPAPER, 0, wstring(strLocalImagePath), SPIF_UPDATEINIFILE | SPIF_SENDCHANGE) != false;

   }


   string display::impl_get_wallpaper(index iScreen)
   {

      wstring  wstr;

      wstr.get_string_buffer(MAX_PATH * 8);
      //::u32 uLen = pwsz.memsize();

      if (!SystemParametersInfoW(SPI_GETDESKWALLPAPER, (::u32)wstr.get_storage_length(), wstr.m_pdata, 0))
      {
         return "";

      }
      wstr.release_string_buffer();

      return wstr;

   }


   //string user::impl_get_os_desktop_theme()
   //{

   //   return "";

   //}


   //bool user::impl_set_os_desktop_theme(string strTheme)
   //{

   //   UNREFERENCED_PARAMETER(strTheme);

   //   return true;

   //}



} // namespace windowing_win32




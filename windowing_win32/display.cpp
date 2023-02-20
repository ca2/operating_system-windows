// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard Sørensen MY ONLY LORD
// recreated by Camilo 2021-02-02 20:55
#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "display.h"
#include "monitor.h"
#include "windowing.h"
#include "window.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/primitive/geometry2d/rectangle_array.h"
#include "aura/platform/system.h"


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

      m_monitorinfoa.erase_all();

      ::EnumDisplayMonitors(nullptr, nullptr, &display::monitor_enum_proc, (LPARAM)this);

      synchronous_lock synchronouslock(synchronization());

      m_monitora.erase_all();

      for (index iMonitor = 0; iMonitor < m_monitorinfoa.get_count(); iMonitor++)
      {

         auto pmonitor = __new(::windowing_win32::monitor());

         pmonitor->initialize(this);

         pmonitor->m_hmonitor = m_hmonitora[iMonitor];

         pmonitor->m_iIndex = iMonitor;

         m_monitora.add(pmonitor);

         copy(pmonitor->m_rectangle, m_monitorinfoa[iMonitor].rcMonitor);

         copy(pmonitor->m_rectangleWorkspace, m_monitorinfoa[iMonitor].rcWork);

      }

   }


   index display::get_main_monitor_index()
   {

      index iMainMonitor = 0;

      HMONITOR hmonitorPrimary = ::windows::get_primary_monitor_handle();

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         if (m_hmonitora[iMonitor] == hmonitorPrimary)
         {

            iMainMonitor = iMonitor;

            break;

         }

      }

      return iMainMonitor;

   }


   index display::get_main_monitor(RECTANGLE_I32 & rectangle)
   {

      auto iMainMonitor = get_main_monitor_index();

      auto pmonitor = get_monitor(iMainMonitor);

      rectangle = pmonitor->monitor_rectangle();

      return iMainMonitor;

   }


   ::count display::get_monitor_count()
   {

#ifdef WINDOWS_DESKTOP

      return m_monitorinfoa.get_count();

#elif defined(MACOS)

      return GetScreenCount();

#elif defined(LINUX)

      synchronous_lock synchronouslock(synchronization());

      return m_rectangleaMonitor.get_count();

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
   //      //auto puserinteraction = __user_interaction(m_puserinteractionHost);
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
   //      synchronous_lock synchronouslock(synchronization());
   //
   //      if (iMonitor < 0 || iMonitor >= get_monitor_count())
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      *prectangle = m_rectangleaMonitor[iMonitor];
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
   //      prectangle->right = operating_system_driver::get().m_iScreenWidth;
   //
   //      prectangle->bottom = operating_system_driver::get().m_iScreenHeight;
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


   index display::get_main_workspace(RECTANGLE_I32 & rectangle)
   {

      index iMainWkspace = 0;

      HMONITOR hwkspacePrimary = ::windows::get_primary_monitor_handle();

      for (index iWkspace = 0; iWkspace < get_workspace_count(); iWkspace++)
      {

         if (m_hmonitora[iWkspace] == hwkspacePrimary)
         {

            iMainWkspace = iWkspace;

            break;

         }

      }

      auto pmonitor = get_monitor(iMainWkspace);

      if (::is_null(rectangle))
      {

         return -1;

      }

      rectangle = pmonitor->workspace_rectangle();

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
   //      synchronous_lock synchronouslock(synchronization());
   //
   //      if (iWkspace < 0 || iWkspace >= get_wkspace_count())
   //      {
   //
   //         return false;
   //
   //      }
   //
   //      *prectangle = m_rectangleaWkspace[iWkspace];
   //
   //
   //      return true;
   //
   //#else
   //
   //      //throw ::exception(todo);
   //
   //      //::window_rectangle(::get_desktop_window(),prectangle);
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

   //   ::rectangle_i32 rectangleWkspace;

   //   if (!get_wkspace_rect(iWkspace, rectangleWkspace))
   //   {

   //      return false;

   //   }

   //   rectangle -= rectangleWkspace.top_left();

   //   ::rectangle_i32 rectangleMonitor;

   //   if (!get_monitor_rect(iMonitor, rectangleMonitor))
   //   {

   //      return false;

   //   }

   //   rectangle += rectangleMonitor.top_left();

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

   //   ::rectangle_i32 rectangleMonitor;

   //   if (!get_monitor_rect(iMonitor, rectangleMonitor))
   //   {

   //      return false;

   //   }

   //   rectangle -= rectangleMonitor.top_left();

   //   ::rectangle_i32 rectangleWkspace;

   //   if (!get_wkspace_rect(iWkspace, rectangleWkspace))
   //   {

   //      return false;

   //   }

   //   rectangle += rectangleWkspace.top_left();

   //   *prectangle = rectangle;

   //   return true;

   //}


   void display::_get_monitor(rectangle_i32_array & rectaMonitor, rectangle_i32_array & rectaIntersect, const rectangle_i32 & rectangleParam)
   {

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectangleIntersect;

         ::rectangle_i32 rectangleMonitor;

         auto pmonitor = get_monitor(iMonitor);

         rectangleMonitor = pmonitor->monitor_rectangle();

         //if (pmonitor->get_monitor_rectangle(rectangleMonitor))
         //{

         //}

         if (rectangleIntersect.top_left_null_intersect(rectangleParam, rectangleMonitor))
         {

            if (rectangleIntersect.area() >= 0)
            {

               rectaMonitor.add(rectangleMonitor);

               rectaIntersect.add(rectangleIntersect);

            }

         }

      }

   }






#define ZONEING_COMPARE ::comparison

   i64 g_i_get_best_zoneing = 0;


   index display::_get_best_zoneing(::e_display * pedisplay, ::rectangle_i32 * prectangle, const ::rectangle_i32 & rectangleRequest, bool bPreserveSize)
   {

      ::rectangle_i32 rectangle(rectangleRequest);

      ::rectangle_i32 rectangleWkspace;

      index iBestWkspace = get_best_workspace(&rectangleWkspace, rectangle);

      ::e_display edisplay;

      ::e_display edisplayPrevious = *pedisplay;

      auto psystem = acmesystem()->m_paurasystem;

      double dMargin = psystem->m_dDpi;

      if (ZONEING_COMPARE::is_equal(rectangle.top, rectangleWkspace.top, dMargin, !(edisplayPrevious & e_display_top)))
      {

         edisplay |= e_display_top;

         if (bPreserveSize)
         {

            rectangle.move_top_to(rectangleWkspace.top);

         }
         else
         {

            rectangle.top = rectangleWkspace.top;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectangle.bottom, rectangleWkspace.bottom, dMargin, !(edisplayPrevious & e_display_bottom)))
      {

         edisplay |= e_display_bottom;

         if (bPreserveSize)
         {

            rectangle.move_bottom_to(rectangleWkspace.bottom);

         }
         else
         {

            rectangle.bottom = rectangleWkspace.bottom;

         }

      }

      if (ZONEING_COMPARE::is_equal(rectangleRequest.left, rectangleWkspace.left, dMargin, !(edisplayPrevious & e_display_left)))
      {

         edisplay |= e_display_left;

         if (bPreserveSize)
         {

            rectangle.move_left_to(rectangleWkspace.left);

         }
         else
         {

            rectangle.left = rectangleWkspace.left;

         }

      }
      else if (ZONEING_COMPARE::is_equal(rectangleRequest.right, rectangleWkspace.right, dMargin, !(edisplayPrevious & e_display_right)))
      {

         edisplay |= e_display_right;

         if (bPreserveSize)
         {

            rectangle.move_right_to(rectangleWkspace.right);

         }
         else
         {

            rectangle.right = rectangleWkspace.right;

         }

      }

      if (!(edisplay & e_display_top || edisplay & e_display_bottom)
         && is_different(edisplay & e_display_left, edisplay & e_display_right))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWkspace.top, rectangle.top, rectangle.bottom, rectangleWkspace.bottom))
         {

            edisplay |= e_display_bottom;

            edisplay |= e_display_top;

            rectangle.bottom = rectangleWkspace.bottom;

            rectangle.top = rectangleWkspace.top;

         }

      }

      if (!(edisplay & e_display_left || edisplay & e_display_right)
         && is_different(edisplay & e_display_top, edisplay & e_display_bottom))
      {

         if (ZONEING_COMPARE::is_centered(rectangleWkspace.left, rectangle.left, rectangle.right, rectangleWkspace.right))
         {

            edisplay |= e_display_left;

            edisplay |= e_display_right;

            rectangle.left = rectangleWkspace.left;

            rectangle.right = rectangleWkspace.right;

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

         edisplay = e_display_restored;

      }

      if (is_docking_appearance(edisplay))
      {

         *prectangle = rectangle;

      }
      else if (edisplay == e_display_zoomed)
      {

         *prectangle = rectangleWkspace;

      }
      else
      {

         *prectangle = rectangleRequest;

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
      //      "w" + ::as_string(rectangleWkspace.left) + ","
      //      + ::as_string(rectangleWkspace.top) + ","
      //      + ::as_string(rectangleWkspace.right) + ","
      //      + ::as_string(rectangleWkspace.bottom) + " " +
      //      "r" + ::as_string(prectangle->left) + ","
      //      + ::as_string(prectangle->top) + ","
      //      + ::as_string(prectangle->right) + ","
      //      + ::as_string(prectangle->bottom) + " " +
      //      strE + " " + strP + "\n");

      //}


      //g_i_get_best_zoneing++;

      //   rectangleWkspace.left,
      //   rectangleWkspace.top,
      //   rectangleWkspace.right,
      //   rectangleWkspace.bottom,
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


   index display::get_best_monitor(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectangleParam, ::e_activation eactivation, ::windowing::window * pwindowCursorPosition)
   {

      index iMatchingMonitor = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectangleMatch;

      ::rectangle_i32 rectangle(rectangleParam);

      if (eactivation & e_activation_under_mouse_cursor || rectangle.is_null())
      {

         ::point_i32 pointCursor;

         if (::is_null(pwindowCursorPosition))
         {

            auto pwindowing = m_pwindowing;

            pointCursor = pwindowing->get_cursor_position();

         }
         else
         {

            pointCursor = pwindowCursorPosition->get_cursor_position();

         }

         rectangle.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

      }

      for (index iMonitor = 0; iMonitor < get_monitor_count(); iMonitor++)
      {

         ::rectangle_i32 rectangleIntersect;

         ::rectangle_i32 rectangleMonitor;

         auto pmonitor = get_monitor(iMonitor);

         rectangleMonitor = pmonitor->monitor_rectangle();

         //if ()
         {

            if (rectangleIntersect.top_left_null_intersect(rectangle, rectangleMonitor))
            {

               if (rectangleIntersect.area() > iBestArea)
               {

                  iMatchingMonitor = iMonitor;

                  iBestArea = rectangleIntersect.area();

                  rectangleMatch = rectangleMonitor;

               }

            }
            else if (rectangleMonitor.contains(rectangle))
            {

               iMatchingMonitor = iMonitor;

               rectangleMatch = rectangleMonitor;

            }

         }

      }

      if (iMatchingMonitor >= 0)
      {

         if (prectangle != nullptr)
         {

            *prectangle = rectangleMatch;

         }

         return iMatchingMonitor;

      }

      iMatchingMonitor = get_main_monitor(rectangle);

      return iMatchingMonitor;

   }


   index display::get_best_workspace(::rectangle_i32 * prectangle, const rectangle_i32 & rectangleParam, ::e_activation eactivation, ::windowing::window * pwindowCursorPosition)
   {

      index iMatchingWkspace = -1;

      i64 iBestArea = -1;

      ::rectangle_i32 rectangleMatch;

      ::rectangle_i32 rectangle(rectangleParam);

      if (eactivation & e_activation_under_mouse_cursor)
      {

         ::point_i32 pointCursor = pwindowCursorPosition->get_cursor_position();

         rectangle.set(pointCursor - ::size_i32(5, 5), ::size_i32(10, 10));

      }

      for (index iWorkspace = 0; iWorkspace < get_workspace_count(); iWorkspace++)
      {

         ::rectangle_i32 rectangleIntersect;

         ::rectangle_i32 rectangleMonitor;

         auto pmonitor = get_monitor(iWorkspace);

         rectangleMonitor = pmonitor->workspace_rectangle();

         //if ()
         {

            if (rectangleIntersect.top_left_null_intersect(rectangle, rectangleMonitor))
            {

               if (rectangleIntersect.area() > iBestArea)
               {

                  iMatchingWkspace = iWorkspace;

                  iBestArea = rectangleIntersect.area();

                  rectangleMatch = rectangleMonitor;

               }

            }
            else if (rectangleMonitor.contains(rectangle))
            {

               iMatchingWkspace = iWorkspace;

               rectangleMatch = rectangleMonitor;

            }

         }

      }

      if (iMatchingWkspace >= 0)
      {

         if (prectangle != nullptr)
         {

            *prectangle = rectangleMatch;

         }

         return iMatchingWkspace;

      }

      iMatchingWkspace = get_main_workspace(*prectangle);

      return iMatchingWkspace;

   }


   index display::get_good_iconify(RECTANGLE_I32 * prectangle, const rectangle_i32 & rectangleParam)
   {

      ::rectangle_i32 rectangleMonitor;

      index iMatchingMonitor = get_best_monitor(rectangleMonitor, rectangleParam);

      prectangle->left = rectangleMonitor.left;

      prectangle->top = rectangleMonitor.top;

      prectangle->right = rectangleMonitor.left;

      prectangle->bottom = rectangleMonitor.top;

      return iMatchingMonitor;

   }


   void display::initialize_display(::windowing::windowing * pwindowing)
   {

      ::windowing::display::initialize_display(pwindowing);

      m_pwindowing = pwindowing;

      enum_display_monitors();

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

      __UNREFERENCED_PARAMETER(hdcMonitor);
      __UNREFERENCED_PARAMETER(prcMonitor);

      m_monitorinfoa.allocate(m_monitorinfoa.get_size() + 1);

      memset(&m_monitorinfoa.last(), 0, sizeof(MONITORINFO));

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

      if (!SystemParametersInfoW(SPI_GETDESKWALLPAPER, (::u32)wstr.storage_character_count(), wstr.data(), 0))
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

   //   __UNREFERENCED_PARAMETER(strTheme);

   //   return true;

   //}


   void display::on_device_plugged(::hardware::enum_device edevice)
   {

      ASSERT(edevice == ::hardware::e_device_monitor);

      enum_display_monitors();

   }


   void display::on_device_unplugged(::hardware::enum_device edevice)
   {

      ASSERT(edevice == ::hardware::e_device_monitor);

      enum_display_monitors();


   }



} // namespace windowing_win32




#include "framework.h"
#include "acme/operating_system.h"

//
//bool CLASS_DECL_ACME __is_combo_box_control(HWND hwnd, unsigned int nStyle)
//{
//   if (hwnd == nullptr)
//      return false;
//   // do cheap style compare first
//   if ((unsigned int)(::GetWindowLong(hwnd, GWL_STYLE) & 0x0F) != nStyle)
//      return false;
//
//   // do expensive classname compare next
//   wchar_t szCompare[_countof("combobox")+1];
//   ::GetClassNameW(hwnd, szCompare, _countof(szCompare));
//   return ::wcsicmp(szCompare, L"combobox") == 0;
//}

//
//bool CLASS_DECL_ACME __compare_class_name(HWND hwnd, const scoped_string & strClassName)
//{
//
//   ASSERT(::IsWindow(hwnd));
//
//   wchar_t szTemp[32];
//
//   ::GetClassNameW(hwnd, szTemp, _countof(szTemp));
//
//   return ::wcsicmp(szTemp, wstring(pszClassName)) == 0;
//
//}


//HWND CLASS_DECL_ACME __child_window_from_point(HWND hwnd, const ::int_point & pointParam)
//{
//   
//   ASSERT(hwnd != nullptr);
//   
//   ::int_point point(pointParam);
//   
//   // check child windows
//   ::ClientToScreen(hwnd, (POINT *) &point);
//
//   HWND oswindow_Child = ::GetWindow(hwnd, GW_CHILD);
//   for (; oswindow_Child != nullptr; oswindow_Child = ::GetWindow(oswindow_Child, GW_HWNDNEXT))
//   {
//      if (::GetDlgCtrlID(oswindow_Child) != (unsigned short)0 &&
//            (::GetWindowLong(oswindow_Child, GWL_STYLE) & WS_VISIBLE))
//      {
//         // see if int_point hits the child interaction_impl
//         ::int_rectangle rectangle;
//         ::GetWindowRect(oswindow_Child, (RECT *) &rectangle);
//         if (rectangle.contains(point))
//            return oswindow_Child;
//      }
//   }
//
//   return nullptr;    // not found
//}
//
//






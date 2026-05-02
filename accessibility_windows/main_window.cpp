// Created by camilo on 2023-04-15 19:31 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "node.h"
#include "main_window.h"
#include "application.h"
#include "acme/constant/user_message.h"
#include "acme/parallelization/mutex.h"
#include "acme/_operating_system.h"


namespace accessibility_windows
{


   main_window::main_window()
   {

      m_hwnd = nullptr;

   }


   main_window::~main_window()
   {

   }


   
   BOOL hwnd_is_main_window(HWND handle)
   {

      return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);

   }


   struct process_identifier_hwnd
   {

      DWORD       m_dwProcessId;

      HWND        m_hwnd;

   };


   BOOL CALLBACK enum_windows_callback(HWND hwnd, LPARAM lParam)
   {
      
      process_identifier_hwnd & processidentifierhwnd = *(process_identifier_hwnd *)lParam;

      DWORD dwProcessId = 0;
      
      ::GetWindowThreadProcessId(hwnd, &dwProcessId);
   
      if (processidentifierhwnd.m_dwProcessId != dwProcessId || !hwnd_is_main_window(hwnd))
      {
      
         return TRUE;

      }
   
      processidentifierhwnd.m_hwnd = hwnd;

      return FALSE;

   }


   HWND process_identifier_main_window(DWORD dwProcessId)
   {

      process_identifier_hwnd processidentifierhwnd;
      
      processidentifierhwnd.m_dwProcessId = dwProcessId;
      
      processidentifierhwnd.m_hwnd = 0;
      
      EnumWindows(enum_windows_callback, (LPARAM)&processidentifierhwnd);

      return processidentifierhwnd.m_hwnd;

   }


   void main_window::from_application(::accessibility::application * papplication)
   {

      auto processidentifier = papplication->m_processidentifier;

      DWORD dwProcess = (DWORD) processidentifier;

      m_hwnd = process_identifier_main_window(dwProcess);

   }


   bool main_window::is_window()
   {

      return ::IsWindow(m_hwnd);

   }
   
   void main_window::post_close()
   {

      ::PostMessage(m_hwnd, WM_CLOSE, 0, 0);

   }


   void main_window::post_application_exit()
   {

      ::PostMessage(m_hwnd, ::user::e_message_application_exit, 0, 0);

   }


   ::string main_window::get_window_text(const ::iptr_array & idPath)
   {

      ::collection::index i = 0;

      HWND hwnd = m_hwnd;

      while (i < idPath.size())
      {

         hwnd = ::GetDlgItem(hwnd, (int) idPath[i]);

         if (!hwnd)
         {

            throw ::exception(error_not_found);

         }

         i++;

      }

      auto operatingsystemwindow = ::as_operating_system_window(hwnd);

      return ::windows::get_window_text_timeout(operatingsystemwindow);

   }


   ::string main_window::indexed_get_window_text(const ::iptr_array & idPath)
   {

      ::collection::index i = 0;

      HWND hwnd = m_hwnd;

      auto operatingsystemwindow = ::as_operating_system_window(hwnd);

      while (i < idPath.size())
      {

         operatingsystemwindow = ::windows::child_at(operatingsystemwindow, idPath[i]);

         if (operatingsystemwindow.is_null())
         {

            throw ::exception(error_not_found);

         }

         i++;

      }

      return ::windows::get_window_text_timeout(operatingsystemwindow);

   }


   void main_window::activate()
   {

      ::SetForegroundWindow(m_hwnd);

      ::BringWindowToTop(m_hwnd);

   }

} // namespace accessibility_windows





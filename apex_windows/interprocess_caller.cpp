// created by Camilo 2021-01-31 05:36 BRT <3CamiloSasukeThomasBorregaardSoerensen
// From interprocess_communcation by camilo on 2022-10-11 15:33 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "interprocess_caller.h"
#include "launcher.h"
#include "acme/exception/exception.h"
#include "apex/platform/launcher.h"


#include "acme/_operating_system.h"


namespace apex_windows
{


   //ATOM rx_register_class(HINSTANCE hInstance);
   //LRESULT CALLBACK s_rx_message_queue_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);



   interprocess_caller::interprocess_caller()
   {

   }


   interprocess_caller::~interprocess_caller()
   {

   }


   void interprocess_caller::open(const ::string & strKey, ::launcher * plauncher)
   {

      if (get_hwnd() != nullptr)
      {

         close();

      }

      int jCount = 23;

      int iCount;

      if (plauncher != nullptr)
      {

         iCount = plauncher->m_iStart + 1;

      }
      else
      {

         iCount = 2;

      }

      set_hwnd(nullptr);

      for (int i = 0; i < iCount; i++)
      {

         for (int j = 0; j < jCount; j++)
         {

            set_hwnd(::FindWindowW(nullptr, wstring(strKey)));

            if (get_hwnd() != nullptr)
            {

               break;

            }

            //         get_hwnd() = FindDesktopWindow(strKey);
            //       if(get_hwnd() != nullptr)
            //        break;
            if (i <= 0)
            {

               break;

            }
            
            int k = 40;

            while (k > 0)
            {
               
               if (!task_get_run())
               {
                  
                  ///return error_failed;
                  throw ::exception(error_failed);

               }
               
               preempt(25_ms);
               
               k--;

            }

         }

         if (get_hwnd() != nullptr)
         {

            break;

         }

         if (plauncher != nullptr)
         {

            if (plauncher->m_iStart <= 0)
            {

               throw ::exception(error_failed);

            }

            plauncher->start();

            plauncher->m_iStart--;

         }

      }
      
      m_strBaseChannel = strKey;

      //return ::success;

   }


   void interprocess_caller::close()
   {

      if (get_hwnd() == nullptr)
      {

         return;
         //return ::success;

      }

      set_hwnd(nullptr);

      m_strBaseChannel = "";

      //return ::success;

   }


   void interprocess_caller::call(const ::string & strUri, const class time & timeTimeout)
   {

      if (!is_caller_ok())
      {

         //return false;
         throw ::exception(error_failed);

      }

      COPYDATASTRUCT cds;

      cds.dwData = 0x80000000;
      cds.cbData = (unsigned int) strUri.length();
      cds.lpData = (void *) strUri.c_str();

      HWND hwnd = get_hwnd();

      if (timeTimeout.is_infinite())
      {

         SendMessage(hwnd, WM_COPYDATA, (WPARAM)0, (LPARAM)&cds);

      }
      else
      {

         DWORD_PTR dwptr;

         if (!::SendMessageTimeout(hwnd, WM_COPYDATA, (WPARAM)0, (LPARAM)&cds, SMTO_ABORTIFHUNG, ::windows::wait(timeTimeout), &dwptr))
         {

            throw ::exception(error_failed);

         }

         unsigned int dwError = ::GetLastError();

         if (dwError == ERROR_TIMEOUT)
         {

            throw ::exception(error_failed);

         }

      }

      //return true;

   }


   //void interprocess_caller::send(int message, void * pdata, int len, const class time & timeTimeout)
   //{

   //   if (message == 0x80000000)
   //   {

   //      throw ::exception(error_failed);

   //   }

   //   if (!is_tx_ok())
   //   {

   //      throw ::exception(error_failed);

   //   }

   //   COPYDATASTRUCT cds;

   //   cds.dwData = (unsigned int)message;
   //   cds.cbData = (unsigned int)maximum(0, len);
   //   cds.lpData = (void *)pdata;


   //   if (timeTimeout.is_pos_infinity())
   //   {

   //      if (message >= WM_APP)
   //      {

   //         SendMessage((HWND)get_hwnd(), message, 0, 0);

   //      }
   //      else
   //      {

   //         SendMessage((HWND)get_hwnd(), WM_COPYDATA, (WPARAM)0, (LPARAM)&cds);

   //      }

   //   }
   //   else
   //   {

   //      DWORD_PTR dwptr;

   //      if (!::SendMessageTimeout((HWND)get_hwnd(), WM_COPYDATA, (WPARAM)0, (LPARAM)&cds, SMTO_BLOCK, (class ::wait)timeTimeout, &dwptr))
   //      {

   //         throw ::exception(error_failed);

   //      }

   //      unsigned int dwError = ::GetLastError();

   //      if (dwError == ERROR_TIMEOUT)
   //      {

   //         throw ::exception(error_failed);

   //      }

   //   }

   //   //return ::success;

   //}



   bool interprocess_caller::is_caller_ok()
   {

      return ::IsWindow((HWND)get_hwnd()) != false;

   }


} // namespace apex_windows




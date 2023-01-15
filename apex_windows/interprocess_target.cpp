// created by Camilo 2021-01-31 05:36 BRT <3CamiloSasukeThomasBorregaardSoerensen
// From interprocess_communcation by camilo on 2022-10-11 15:32 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "launcher.h"
#include "acme/exception/exception.h"
#include "interprocess_target.h"
#include "apex/platform/launcher.h"
#include "apex/platform/system.h"


namespace apex_windows
{


   ATOM rx_register_class(HINSTANCE hInstance);
   //LRESULT CALLBACK s_rx_message_queue_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);


   //interprocess_communication_base::interprocess_communication_base()
   //{

   //   set_hwnd(nullptr);

   //}


   //interprocess_communication_base::~interprocess_communication_base()
   //{

   //   if (get_hwnd() != nullptr)
   //   {

   //      ::DestroyWindow((HWND)get_hwnd());

   //      set_hwnd(nullptr);

   //   }

   //}


   //interprocess_caller::interprocess_caller()
   //{

   //}


   //interprocess_caller::~interprocess_caller()
   //{

   //}


   //void interprocess_caller::open(const ::string & strKey, ::launcher * plauncher)
   //{

   //   if (get_hwnd() != nullptr)
   //   {

   //      close();

   //   }

   //   int jCount = 23;

   //   int iCount;

   //   if (plauncher != nullptr)
   //   {

   //      iCount = plauncher->m_iStart + 1;

   //   }
   //   else
   //   {

   //      iCount = 2;

   //   }

   //   set_hwnd(nullptr);

   //   for (int i = 0; i < iCount; i++)
   //   {

   //      for (int j = 0; j < jCount; j++)
   //      {

   //         set_hwnd(::FindWindowW(nullptr, wstring(strKey)));

   //         if (get_hwnd() != nullptr)
   //         {

   //            break;

   //         }

   //         //         get_hwnd() = FindDesktopWindow(strKey);
   //         //       if(get_hwnd() != nullptr)
   //         //        break;
   //         if (i <= 0)
   //         {

   //            break;

   //         }
   //         
   //         int k = 40;

   //         while (k > 0)
   //         {
   //            
   //            if (!task_get_run())
   //            {
   //               
   //               ///return error_failed;
   //               throw ::exception(error_failed);

   //            }
   //            
   //            preempt(25_ms);
   //            
   //            k--;

   //         }

   //      }

   //      if (get_hwnd() != nullptr)
   //      {

   //         break;

   //      }

   //      if (plauncher != nullptr)
   //      {

   //         if (plauncher->m_iStart <= 0)
   //         {

   //            throw ::exception(error_failed);

   //         }

   //         plauncher->start();

   //         plauncher->m_iStart--;

   //      }

   //   }
   //   
   //   m_strBaseChannel = strKey;

   //   //return ::success;

   //}


   //void interprocess_caller::close()
   //{

   //   if (get_hwnd() == nullptr)
   //   {

   //      return;
   //      //return ::success;

   //   }

   //   set_hwnd(nullptr);

   //   m_strBaseChannel = "";

   //   //return ::success;

   //}


   //void interprocess_caller::send(const ::string & strMessage, const class time & timeTimeout)
   //{

   //   if (!is_tx_ok())
   //   {

   //      //return false;
   //      throw ::exception(error_failed);

   //   }

   //   COPYDATASTRUCT cds;

   //   cds.dwData = 0x80000000;
   //   cds.cbData = (unsigned int) strMessage.length();
   //   cds.lpData = (void *) strMessage.c_str();

   //   HWND hwnd = get_hwnd();

   //   if (timeTimeout.is_pos_infinity())
   //   {

   //      SendMessage(hwnd, WM_COPYDATA, (WPARAM)0, (LPARAM)&cds);

   //   }
   //   else
   //   {

   //      DWORD_PTR dwptr;

   //      if (!::SendMessageTimeout(hwnd, WM_COPYDATA, (WPARAM)0, (LPARAM)&cds, SMTO_ABORTIFHUNG, (class ::wait)timeTimeout, &dwptr))
   //      {

   //         throw ::exception(error_failed);

   //      }

   //      unsigned int dwError = ::GetLastError();

   //      if (dwError == ERROR_TIMEOUT)
   //      {

   //         throw ::exception(error_failed);

   //      }

   //   }

   //   //return true;

   //}


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



   //bool interprocess_caller::is_tx_ok()
   //{

   //   return ::IsWindow((HWND)get_hwnd()) != false;

   //}


   interprocess_target::interprocess_target()
   {

      //m_preceiver = nullptr;

   }


   interprocess_target::~interprocess_target()
   {

   }


   void interprocess_target::create(const ::string & strKey)
   {


      /*    if(g_pfnChangeWindowMessageFilter != nullptr)
          {
             g_pfnChangeWindowMessageFilter(WM_COPYDATA,MSGFLT_ADD);
          }*/

          //HINSTANCE hinstance = ::GetModuleHandleA("apex.dll");

          //if(hinstance == nullptr)
          //{

          //   hinstance = ::GetModuleHandleA(nullptr);

          //}

          //auto pappcore = psystem->m_pappcore;

          //auto pmaindata = pappcore->m_pmaindata;

      ::pointer<::apex::system>psystem = acmesystem();

      HINSTANCE hinstance = (HINSTANCE)psystem->m_psubsystem->m_hinstanceThis;

      ATOM atom = rx_register_class(hinstance);

      wstring wstrKey(strKey);

      set_hwnd(::CreateWindowExW(0, L"small_ipc_rx_::color::e_channel_message_queue_class", wstrKey, 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, hinstance, nullptr));

      if (get_hwnd() == nullptr)
      {
         
         unsigned int dwLastError = ::GetLastError();
         
         throw ::exception(error_failed);

      }

      if (!ChangeWindowMessageFilterEx((HWND)get_hwnd(), WM_COPYDATA, MSGFLT_ADD, NULL))
      {

         INFORMATION("Failed to change WM_COPYDATA message filter");

      }

      SetTimer((HWND)get_hwnd(), 888888, 84, nullptr);

      SetWindowLongPtr((HWND)get_hwnd(), GWLP_USERDATA, (LONG_PTR)this);

      //m_strWindowProcModule = pszWindowProcModule;

      //return true;

   }


   void interprocess_target::destroy()
   {

      if (get_hwnd() != nullptr)
      {
         
         ::DestroyWindow((HWND)get_hwnd());
         
         set_hwnd(nullptr);

      }

      //return ::success;

   }


   //void * interprocess_target::on_interprocess_receive(::inteprocess::handler * prx, const ::string & strMessage)
   //{

   //   if (strMessage.case_insensitive_begins("synch_"))
   //   {

   //      if (m_preceiver != nullptr)
   //      {

   //         m_preceiver->on_interprocess_receive(prx, strMessage);

   //      }

   //   }
   //   else
   //   {

   //      get_application()->fork([=]()
   //         {

   //            if (m_preceiver != nullptr)
   //            {

   //               m_preceiver->on_interprocess_receive(prx, strMessage);

   //            }

   //         });

   //   }

   //   // ODOW - on date of writing : return ignored by this windows implementation

   //   return nullptr;

   //}


   //void * interprocess_target::on_interprocess_receive(::inteprocess::handler * prx, int message, void * pdata, memsize len)
   //{

   //   if (m_preceiver != nullptr)
   //   {

   //      m_preceiver->on_interprocess_receive(prx, message, pdata, len);

   //   }

   //   // ODOW - on date of writing : return ignored by this windows implementation

   //   return nullptr;

   //}


   //void * interprocess_target::on_interprocess_post(::inteprocess::handler * prx, long long int a, long long int b)
   //{

   //   if (m_preceiver != nullptr)
   //   {

   //      m_preceiver->on_interprocess_post(prx, a, b);

   //   }

   //   // ODOW - on date of writing : return ignored by this windows implementation

   //   return nullptr;

   //}


   LRESULT CALLBACK s_rx_message_queue_proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   {

      int iRet = 0;

      interprocess_target * pchannel = (interprocess_target *)GetWindowLongPtr((HWND)hwnd, GWLP_USERDATA);

      if (pchannel == nullptr)
      {

         return ::DefWindowProcW((HWND)hwnd, message, wparam, lparam);

      }
      else
      {

         return pchannel->message_queue_proc((enum_message)message, wparam, lparam);

      }

   }


   ATOM rx_register_class(HINSTANCE hInstance)
   {

      WNDCLASSEXW wcex = {};

      wcex.cbSize = sizeof(WNDCLASSEX);

      wcex.style = 0;
      wcex.lpfnWndProc = &s_rx_message_queue_proc;

      wcex.cbClsExtra = 0;
      wcex.cbWndExtra = 40;
      wcex.hInstance = hInstance;
      wcex.hIcon = nullptr;
      //wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
      wcex.hCursor = nullptr;
      wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
      wcex.lpszMenuName = nullptr;

      wcex.lpszClassName = L"small_ipc_rx_::color::e_channel_message_queue_class";

      wcex.hIconSm = nullptr;

      return RegisterClassExW(&wcex);

   }


   LRESULT interprocess_target::message_queue_proc(UINT message, WPARAM wparam, LPARAM lparam)
   {

      //if (message == WM_USER + 100)
      //{

      //   on_interprocess_post(wparam, lparam);

      //}
      if (message == WM_COPYDATA)
      {

         COPYDATASTRUCT * pcopydatastruct = (COPYDATASTRUCT *)lparam;

         if (pcopydatastruct == nullptr)
         {

            return 0;

         }
         else if (pcopydatastruct->dwData == 0x80000000)
         {

            auto pszData = (const char *)pcopydatastruct->lpData;

            auto szLen = (strsize)pcopydatastruct->cbData;

            _handle_uri({pszData, szLen});

         }
         //else
         //{

         //   auto pdata = (void *) pcopydatastruct->lpData;

         //   auto size = (memsize) pcopydatastruct->cbData;

         //   memory memory(pdata, size);

         //   on_interprocess_receive((int)pcopydatastruct->dwData, ::move(memory));

         //}

      }
      //else if (message >= WM_APP)
      //{

      //   auto pdata = (void *)pcopydatastruct->lpData;

      //   auto size = (memsize)pcopydatastruct->cbData;

      //   memory memory(pdata, size);

      //   on_interprocess_receive(message, (void *)wparam, lparam);

      //}
      else
      {

         return ::DefWindowProcW((HWND) get_hwnd(), message, wparam, lparam);

      }

      return 0;

   }


   bool interprocess_target::on_idle()
   {

      return false;

   }


   bool interprocess_target::is_target_ok()
   {

      return ::IsWindow((HWND) get_hwnd()) != false;

   }


} // namespace apex_windows




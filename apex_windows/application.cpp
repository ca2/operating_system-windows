#include "framework.h"
#include "apex/operating_system.h"


//namespace apex
//{
//
//
//
//   //void application::impl_term1()
//   //{
//
//
//   //}
//
//   //
//   //
//   //   application::application() :
//   //      ::object(pobject)
//   //   {
//   //
//   //      //m_pthreadimpl.create(this);
//   //
//   //      //m_pthreadimpl->m_pthread = this;
//   //
//   //      psystem                    =  papp->get_application()->psystem;
//   //
//   //      m_atomApp = m_atomSystemTopic    = nullptr;
//   //
//   //   }
//
//
//   //application::~application()
//   //{
//
//   //}
//
//
//   //void application::_001OnFileNew()
//   //{
//
//   //}
//
//
//   //::user::document *  application::_001OpenDocumentFile(::payload payloadFile)
//   //{
//
//   //   return nullptr;
//
//   //}
//
//
//
//   //bool application::_001OnDDECommand(const ::string & pcsz)
//
//   //{
//
//   //   __UNREFERENCED_PARAMETER(pcsz);
//
//
//   //   return false;
//
//   //}
//
//
//   //HINSTANCE application::GetHinstance()
//   //{
//
//   //   return nullptr;
//
//   //}
//
//   string application::get_version()
//   {
//
//      unichar pszModuleFilePath[MAX_PATH + 1];
//
//      GetModuleFileNameW(nullptr, pszModuleFilePath, MAX_PATH + 1);
//
//      DWORD dw;
//
//      ::u32 dwResSize = GetFileVersionInfoSizeW(
//                        pszModuleFilePath,
//                        &dw);
//
//      if (dwResSize > 0)
//      {
//       
//         memory memory;
//         
//         memory.set_size(dwResSize);
//
//         if (GetFileVersionInfoW(
//               pszModuleFilePath,
//
//               0,
//               dwResSize,
//            memory.get_data()))
//
//         {
//            ::u32 cbTranslate;
//            struct LANGANDCODEPAGE
//            {
//               ::u16 wLanguage;
//               ::u16 wCodePage;
//            } *pTranslate;
//
//
//            // read the list of languages and code pages.
//
//            VerQueryValue(memory.get_data(),
//                          TEXT("\\VarFileInfo\\Translation"),
//                          (LPVOID*)&pTranslate,
//                          &cbTranslate);
//
//            string strKey;
//
//            for( ::u32 u = 0; u < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); u++ )
//            {
//
//               WCHAR * psz;
//
//               UINT uSize;
//
//               //strKey.Format(
//               //"\\StringFileInfo\\%04x%04x\\FileDescription",
//               //pTranslate[u].wLanguage,
//               //pTranslate[u].wCodePage);
//
//               strKey.Format(
//               "\\StringFileInfo\\%04x%04x\\FileVersion",
//               pTranslate[u].wLanguage,
//               pTranslate[u].wCodePage);
//
//               wstring wstrKey(strKey);
//
//               // Retrieve file description for language and code page "i".
//               if (VerQueryValueW(memory.get_data(),
//                  (WCHAR *)(const WCHAR*)wstrKey,
//                  (LPVOID *)&psz,
//                  &uSize))
//               {
//
//                  string strVersion(psz, uSize);
//
//                  return strVersion;
//
//               }
//
//            }
//
//         }
//
//      }
//
//      return "";
//
//   }
//
//
//   void application::show_wait_cursor(bool bShow)
//   {
//
//      if (bShow)
//      {
//
//         HCURSOR hcursorWait = ::LoadCursor(nullptr, IDC_WAIT);
//
//         HCURSOR hcursorPrevious = ::SetCursor(hcursorWait);
//
//         //     if(hcursorPrevious != hcursorWait)
//         //         m_hcurWaitCursorRestore = hcursorPrevious;
//
//      }
//      else
//      {
//
//         //         ::SetCursor(m_hcurWaitCursorRestore);
//      }
//
//   }
//
//
//} // namespace windows





//
//void __node_init_main_data(::object * pobject, HINSTANCE hInstance, HINSTANCE hPrevInstance, char * pCmdLine, ::display edisplay)

//{
//
//
//   ::comm::command * pmaininitdata = new ::windows::command;
//
//
//   pmaininitdata->m_hInstance = hInstance;
//   pmaininitdata->m_hPrevInstance = hPrevInstance;
//   pmaininitdata->m_strCommandLine = ::str::international::unicode_to_utf8(::GetCommandLineW());
//   pmaininitdata->m_nCmdShow = nCmdShow;
//
//   papp->startup_command(pmaininitdata);
//
//}
//


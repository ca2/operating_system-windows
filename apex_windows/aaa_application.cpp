#include "framework.h"
#include "apex/operating_system.h"


namespace apex
{



   //void application::impl_term1()
   //{


   //}

   //
   //
   //   __IMPLEMENT_APPLICATION_RELEASE_TIME();


   application::application() :
   //      ::object(pobject)
   //   {
   //
   //      //m_pthreadimpl.create(this);
   //
   //      //m_pthreadimpl->m_pthread = this;
   //
   //      psystem                    =  papp->get_application()->psystem;
   //
   //      m_atomApp = m_atomSystemTopic    = nullptr;
   //
   //   }


   //application::~application()
   //{

   //}


   //void application::_001OnFileNew()
   //{

   //}


   //::user::document *  application::_001OpenDocumentFile(::payload payloadFile)
   //{

   //   return nullptr;

   //}


   void application::_001InitializeShellOpen()
   {

      //ASSERT(m_atomApp == nullptr && m_atomSystemTopic == nullptr); // do once

      //m_atomApp            = ::GlobalAddAtomW(utf8_to_unicode(m_strAppName));

      //m_atomSystemTopic    = ::GlobalAddAtomW(L"system");

      return ::success;

   }


   //bool application::_001OnDDECommand(const ::string & pcsz)

   //{

   //   __UNREFERENCED_PARAMETER(pcsz);


   //   return false;

   //}


   //HINSTANCE application::GetHinstance()
   //{

   //   return nullptr;

   //}

   string application::get_version()
   {

      unichar pszModuleFilePath[MAX_PATH + 1];

      GetModuleFileNameW(nullptr, pszModuleFilePath, MAX_PATH + 1);

      DWORD dw;

      ::u32 dwResSize = GetFileVersionInfoSizeW(
                        pszModuleFilePath,
                        &dw);

      if (dwResSize > 0)
      {
       
         memory memory;
         
         memory.set_size(dwResSize);

         if (GetFileVersionInfoW(
               pszModuleFilePath,

               0,
               dwResSize,
            memory.get_data()))

         {
            ::u32 cbTranslate;
            struct LANGANDCODEPAGE
            {
               ::u16 wLanguage;
               ::u16 wCodePage;
            } *pTranslate;


            // read the list of languages and code pages.

            VerQueryValue(memory.get_data(),
                          TEXT("\\VarFileInfo\\Translation"),
                          (LPVOID*)&pTranslate,
                          &cbTranslate);

            string strKey;

            for( ::u32 u = 0; u < (cbTranslate/sizeof(struct LANGANDCODEPAGE)); u++ )
            {

               WCHAR * psz;

               UINT uSize;

               //strKey.Format(
               //"\\StringFileInfo\\%04x%04x\\FileDescription",
               //pTranslate[u].wLanguage,
               //pTranslate[u].wCodePage);

               strKey.Format(
               "\\StringFileInfo\\%04x%04x\\FileVersion",
               pTranslate[u].wLanguage,
               pTranslate[u].wCodePage);

               wstring wstrKey(strKey);

               // Retrieve file description for language and code page "i".
               if (VerQueryValueW(memory.get_data(),
                  (WCHAR *)(const WCHAR*)wstrKey,
                  (LPVOID *)&psz,
                  &uSize))
               {

                  string strVersion(psz, uSize);

                  return strVersion;

               }

            }

         }

      }

      return "";

   }


   void application::show_wait_cursor(bool bShow)
   {

      if (bShow)
      {

         HCURSOR hcursorWait = ::LoadCursor(nullptr, IDC_WAIT);

         HCURSOR hcursorPrevious = ::SetCursor(hcursorWait);

         //     if(hcursorPrevious != hcursorWait)
         //         m_hcurWaitCursorRestore = hcursorPrevious;

      }
      else
      {

         //         ::SetCursor(m_hcurWaitCursorRestore);
      }

   }


   string application::veriwell_multimedia_music_midi_get_default_implementation_name()
   {
      return system()->implementation_name("music_midi", "mmsystem");
   }

   string application::multimedia_audio_mixer_get_default_implementation_name()
   {
      return system()->implementation_name("audio_mixer", "mmsystem");
   }

   string application::multimedia_audio_get_default_implementation_name()
   {

      string str;

      if (acmefile()->exists(::dir::system() / "config\\system\\audio.txt"))
      {

         str = acmefile()->as_string(::dir::system() / "config\\system\\audio.txt");

      }
      else
      {

         ::file::path strPath;

         strPath = ::dir::appdata() / "audio.txt";

         str = acmefile()->as_string(strPath);

      }

      if (str.has_char())
         return "audio_" + str;
      else
         return system()->implementation_name("audio", "mmsystem");

   }


} // namespace windows





//
//void __node_init_main_data(::particle * pparticle, HINSTANCE hInstance, HINSTANCE hPrevInstance, char * pCmdLine, ::display edisplay)

//{
//
//
//   ::comm::command * pmaininitdata = new ::windows::command;
//
//
//   pmaininitdata->m_hInstance = hInstance;
//   pmaininitdata->m_hPrevInstance = hPrevInstance;
//   pmaininitdata->m_strCommandLine = unicode_to_utf8(::GetCommandLineW());
//   pmaininitdata->m_nCmdShow = nCmdShow;
//
//   papp->startup_command(pmaininitdata);
//
//}
//


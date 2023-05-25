// From node.cpp by camilo on 2023-05-17 23:16 <3ThomasBorregaardSorensen!!
#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "node.h"
#include "acme_directory.h"
#include "acme_file.h"
#include "registry.h"
#include "process.h"
#include "exclusive.h"
#include "application.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/operating_system/process.h"
#include "acme/operating_system/summary.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/platform/scoped_restore.h"
#include "acme/platform/system.h"
#include "acme/primitive/primitive/memory.h"
#include "acme/primitive/string/__wide.h"
#include "acme/primitive/string/adaptor.h"
#include "acme/primitive/string/international.h"
#include "acme/primitive/string/str.h"


#include "acme/_operating_system.h"


#include "acme_windows_common/hresult_exception.h"
#include "acme_windows_common/comptr.h"
#include "acme_windows_common/cotaskptr.h"
#include "acme_windows_common/security_attributes.h"
#include "acme_windows_common/bstring.h"
#include "acme_windows_common/variant.h"
#include <Shldisp.h>
#include <shellapi.h>



#if defined(_WIN32)
#  ifndef NOMINMAX
#  define NOMINMAX 1
#  endif
//#  include <windows.h>
#include <commdlg.h>
#endif

//#include <shobjidl.h>
//#include <ShellApi.h>
//#include <Security.h>
//#include <wincred.h>
#include <shobjidl_core.h>


namespace acme_windows
{


   void node::_node_folder_dialog(::file::folder_dialog* pdialogParameter)
   {

      ::pointer < ::file::folder_dialog > pdialog(pdialogParameter);

      main_asynchronous([this, pdialog]
         {


            ::file::path_array patha;

            bool bOk = false;

            acmenode()->defer_co_initialize_ex(false);

            comptr < IFileOpenDialog > pfileopen;

            // Create the FileOpenDialog object.
            HRESULT hr = pfileopen.CoCreateInstance(CLSID_FileOpenDialog, nullptr, CLSCTX_ALL);

            if (SUCCEEDED(hr))
            {

               if (pdialog->m_path.has_char())
               {

                  wstring wstr(pdialog->m_path);

                  comptr < IShellItem > psi;

                  hr = SHCreateItemFromParsingName(wstr, nullptr, IID_IShellItem, (void**)&psi);

                  if (SUCCEEDED(hr))
                  {

                     pfileopen->SetFolder(psi);

                  }

               }

               pfileopen->SetOptions(FOS_PICKFOLDERS);

               // Show the Open dialog box.
               hr = pfileopen->Show(nullptr);

               if (SUCCEEDED(hr))
               {

                  // Get the file name from the dialog box.
                  comptr < IShellItem > pitem;

                  hr = pfileopen->GetResult(&pitem);

                  if (SUCCEEDED(hr))
                  {

                     ::cotaskptr < PWSTR > pwszFilePath;

                     hr = pitem->GetDisplayName(SIGDN_FILESYSPATH, &pwszFilePath);

                     // Display the file name to the user.
                     if (SUCCEEDED(hr))
                     {

                        pdialog->m_path = ::string((PWSTR)pwszFilePath);

                        pdialog->m_function(::transfer(pdialog));

                        bOk = true;

                     }

                  }

               }

            }


            if (!bOk)
            {

               pdialog->m_function({});

            }



         });

   }


} // namespace acme_windows




// From node.cpp by camilo on 2023-05-17 23:17 <3ThomasBorregaardSorensen!!
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


   void node::_node_file_dialog(::file::file_dialog* pdialogParameter)
   {

      if (pdialogParameter->m_bSave && pdialogParameter->m_bMultiple)
      {

         throw ::exception(error_bad_argument, "save and multiple must not both be true.");

      }

      ::pointer < ::file::file_dialog > pdialog(pdialogParameter);

      main_asynchronous([pdialog]
         {

            //::file::path_array patha;

            OPENFILENAME openfilename;

            ZeroMemory(&openfilename, sizeof(OPENFILENAME));

            openfilename.lStructSize = sizeof(OPENFILENAME);
            
            memory memoryFileNames;
            
            const auto FILE_DIALOG_MAX_BUFFER = 16KiB;

            memoryFileNames.set_size(FILE_DIALOG_MAX_BUFFER);

            memoryFileNames.zero();

            wchar_t* wszFileNames = (wchar_t*)memoryFileNames.data();

            openfilename.lpstrFile = wszFileNames;
            
            //;; ZeroMemory(tmp, FILE_DIALOG_MAX_BUFFER);

            openfilename.nMaxFile = (DWORD)memoryFileNames.size();

            openfilename.nFilterIndex = 1;

            memory memoryFilter;

            if (!pdialog->m_bSave && pdialog->m_filedialogfiltera.size() > 1) 
            {

               __wide_append(memoryFilter, "Supported file types (");

               for (::index i = 0; i < pdialog->m_filedialogfiltera.size(); ++i) 
               {
                  
                  //__wide_append(memoryFilter, "*.");

                  ::string strPatternList = pdialog->m_filedialogfiltera[i].m_strPatternList;
                  
                  __wide_append(memoryFilter, strPatternList);

                  if (i + 1 < pdialog->m_filedialogfiltera.size())
                  {

                     __wide_append(memoryFilter, ";");

                  }

               }

               __wide_append(memoryFilter, ")");

               __wide_append_null(memoryFilter);

               for (::index i = 0; i < pdialog->m_filedialogfiltera.size(); ++i) 
               {
               
                  //__wide_append(memoryFilter, "*.");

                  ::string strPatternList = pdialog->m_filedialogfiltera[i].m_strPatternList;

                  __wide_append(memoryFilter, strPatternList);

                  if (i + 1 < pdialog->m_filedialogfiltera.size())
                  {

                     __wide_append(memoryFilter, ";");

                  }

               }
               
               __wide_append_null(memoryFilter);

            }
            
            for (auto pair : pdialog->m_filedialogfiltera) 
            {

               __wide_append(memoryFilter, pair.m_strName.c_str());

               //__wide_append(memoryFilter, " (*.");

               __wide_append(memoryFilter, " (");
               __wide_append(memoryFilter, pair.m_strPatternList.c_str());
               __wide_append(memoryFilter, ")");
               __wide_append_null(memoryFilter);

               //__wide_append(memoryFilter, "*.");
               __wide_append(memoryFilter, pair.m_strPatternList.c_str());
               __wide_append_null(memoryFilter);

            }

            __wide_append_null(memoryFilter);

            openfilename.lpstrFilter = (LPWSTR)memoryFilter.data();

            if (pdialog->m_bSave) 
            {

               openfilename.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;

               if (GetSaveFileNameW(&openfilename) == FALSE)
               {

                  pdialog->m_function({});

                  return;

               }

            }
            else 
            {

               openfilename.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

               if (pdialog->m_bMultiple)
               {

                  openfilename.Flags |= OFN_ALLOWMULTISELECT;

               }
               
               if (GetOpenFileNameW(&openfilename) == FALSE)
               {

                  pdialog->m_function({});

                  return;

               }

            }

            while (*wszFileNames != L'\0') 
            {

               wstring wstr(wszFileNames);

               ::string str(wstr);

               ::file::path path(str);

               pdialog->m_patha.add(path);

               wszFileNames += wcslen(wszFileNames) + 1;

            }

            //if (result.size() > 1) {
            //   for (i = 1; i < result.size(); ++i) {
            //      result[i] = result[0] + "\\" + result[i];
            //   }
            //   result.erase(begin(result));
            //}

      //#elif defined(LINUX)
      //
      //
      //      throw ::exception(todo);
      //
      //      //         static const int FILE_DIALOG_MAX_BUFFER = 16384;
      //      //
      //      //         char buffer[FILE_DIALOG_MAX_BUFFER];
      //      //
      //      //         buffer[0] = '\0';
      //      //
      //      //         std::string cmd = "zenity --file-selection ";
      //      //         // The safest separator for multiple selected paths is /, since / can never occur
      //      //         // in file names. Only where two paths are concatenated will there be two / following
      //      //         // each other.
      //      //         if (multiple)
      //      //            cmd += "--multiple --separator=\"/\" ";
      //      //         if (save)
      //      //            cmd += "--save ";
      //      //         cmd += "--file-memoryFilter=\"";
      //      //         for (auto pair : filetypes)
      //      //            cmd += "\"*." + pair.first + "\" ";
      //      //         cmd += "\"";
      //      //         FILE * output = popen(cmd.c_str(), "r");
      //      //         if (output == nullptr)
      //      //            throw std::runtime_error("popen() failed -- could not launch zenity!");
      //      //         while (fgets(buffer, FILE_DIALOG_MAX_BUFFER, output) != NULL)
      //      //            ;
      //      //         pclose(output);
      //      //         std::string paths(buffer);
      //      //         paths.erase(std::remove(paths.begin(), paths.end(), '\n'), paths.end());
      //      //
      //      //         while (!paths.empty()) {
      //      //            size_t end = paths.find("//");
      //      //            if (end == std::string::npos) {
      //      //               result.emplace_back(paths);
      //      //               paths = "";
      //      //            }
      //      //            else {
      //      //               result.emplace_back(paths.substr(0, end));
      //      //               paths = paths.substr(end + 1);
      //      //            }
      //      //         }
      //
      //#endif
            //pdialog->m_patha = patha;
            pdialog->m_function(pdialog);

         });

   }


} // namespace acme_windows




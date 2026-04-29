// From node.cpp by camilo on 2023-05-17 23:17 <3ThomasBorregaardSorensen!!
#include "framework.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "node.h"
#include "directory_system.h"
#include "file_system.h"
#include "registry.h"
#include "process.h"
#include "exclusive.h"
#include "application.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/file_dialog.h"
#include "acme/filesystem/filesystem/folder_dialog.h"
#include "acme/operating_system/process.h"
#include "acme/operating_system/summary.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/parallelization/install_mutex.h"
#include "acme/platform/scoped_restore.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/prototype/string/__wide.h"
#include "acme/prototype/string/adaptor.h"
#include "acme/prototype/string/international.h"
#include "acme/prototype/string/str.h"


#include "acme/_operating_system.h"


#include "acme/operating_system/windows_common/com/hresult_exception.h"
#include "acme/operating_system/windows_common/com/comptr.h"
#include "acme/operating_system/windows_common/com/cotaskptr.h"
#include "acme_windows_common/security_attributes.h"
#include "acme/operating_system/windows_common/com/bstring.h"
#include "acme/operating_system/windows_common/com/variant.h"
#include <Shldisp.h>
#include <shellapi.h>
#include <commdlg.h>
#include <shlwapi.h>  // for PathFindExtension
#include <dlgs.h>

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
#include <windows.h>
#include <shlobj.h>  // For SHGetKnownFolderPath
#include <iostream>
#include <filesystem>
void NotifyRecentItemsChanged();
bool EraseRecentItem(const ::wstring& fileName) {
   PWSTR recentPath = nullptr;
   HRESULT hr = SHGetKnownFolderPath(FOLDERID_Recent, 0, NULL, &recentPath);
   if (FAILED(hr)) {
      std::wcerr << L"Failed to get Recent folder path\n";
      return false;
   }

   std::filesystem::path recentFolder(recentPath);
   CoTaskMemFree(recentPath);

   auto name = std::filesystem::path(fileName.c_str()).filename();

   for (const auto& entry : std::filesystem::directory_iterator(recentFolder)) {
      if (entry.path().extension() == L".lnk") {
         if (entry.path().filename().wstring().find(name) != std::wstring::npos) {
            std::filesystem::remove(entry.path());
            std::wcout << L"Removed: " << entry.path() << std::endl;
            return true;
         }
      }
   }

   std::wcout << L"Item not found in recent items\n";
   return false;
}
#include <shlobj.h>
#include <iostream>

void NotifyRecentItemsChanged() {
   PWSTR recentPath = nullptr;
   if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Recent, 0, nullptr, &recentPath))) {
      SHChangeNotify(SHCNE_UPDATEDIR, SHCNF_PATH, recentPath, NULL);
      CoTaskMemFree(recentPath);
   }
}

bool AddToRecentItems(const ::wstring& targetPath, const ::wstring& title = L"") 
{

   HRESULT hr;
   CoInitialize(NULL);

   // Get the Recent Items folder path
   PWSTR pszRecent = nullptr;
   hr = SHGetKnownFolderPath(FOLDERID_Recent, 0, NULL, &pszRecent);
   if (FAILED(hr)) {
      std::wcerr << L"Failed to get Recent folder path\n";
      return false;
   }

   ::file::path recentFolder(pszRecent);
   CoTaskMemFree(pszRecent);

   // Build shortcut path
   ::wstring linkName = title.is_empty() ? ::wstring(::file::path(targetPath).name()) : title;
   ::file::path linkPath = recentFolder / (linkName + L".lnk");

   // Create shortcut
   comptr<IShellLink> pShellLink;
   hr = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pShellLink));
   if (FAILED(hr)) return false;

   pShellLink->SetPath(targetPath.c_str());
   pShellLink->SetDescription(L"Recent item");

   auto pPersistFile=pShellLink.as< IPersistFile>();
   if (!pPersistFile) return false;

   hr = pPersistFile->Save(linkPath.windows_path().path().c_str(), TRUE);
   return SUCCEEDED(hr);

}


namespace acme_windows
{

   thread_local OPENFILENAME * t_popenfilename;

   UINT_PTR CustomOFNHookProc(
      HWND unnamedParam1,
      UINT unnamedParam2,
      WPARAM unnamedParam3,
      LPARAM unnamedParam4
   )
   {
      if (unnamedParam2 == WM_INITDIALOG)
      {

         t_popenfilename = (OPENFILENAME*)(void*)(uptr)unnamedParam4;

      }

      ::file::file_dialog* pfiledialog = nullptr;

      if (t_popenfilename)
      {

         pfiledialog = (::file::file_dialog*)t_popenfilename->lCustData;

      }

      if (unnamedParam2 == WM_NOTIFY)
      {

         auto lpnmhdr = (LPNMHDR)unnamedParam4;

         UINT code = lpnmhdr->code;

//         CDN_TYPECHANGE             uint32 = 0xfffffda1

         /*typedef struct _OFNOTIFYA {
            NMHDR           hdr;
            LPOPENFILENAMEA lpOFN;
            LPSTR           pszFile;
         } OFNOTIFYA, * */;
         HWND hwndParent = GetParent(unnamedParam1);
         if (code == CDN_TYPECHANGE)
         {

            //printf_line("CDN_TYPECHANGE code %d", code);

            auto pofnotify = (LPOFNOTIFYW)lpnmhdr;

            auto iFilterIndex = t_popenfilename->nFilterIndex;

            iFilterIndex--;

            auto & filter = pfiledialog->m_filedialogfilter[iFilterIndex];

            // Get file name from edit control
            WCHAR fileName[MAX_PATH * 4];
            
            //GetDlgItemText(hwndParent, edt1, fileName, MAX_PATH);
            CommDlg_OpenSave_GetFilePathW(hwndParent, fileName, MAX_PATH *4);

            wstring wstrFileName(fileName);

            ::file::path path(wstrFileName);

            path.defer_set_extension(filter.get_preserve_extensions(),
               pfiledialog->m_filedialogfilter.get_all_related_extensions());

            auto strName = path.name();

            ::wstring wstrName;

            wstrName = strName;

            // Set updated file name
            CommDlg_OpenSave_SetControlText(hwndParent, edt1, wstrName.c_str());

                  //// Append new extension based on selected filter
                  //switch (iFilterIndex)
                  //{
                  //case 1: _tcscat_s(fileName, _T(".txt")); break;
                  //case 2: _tcscat_s(fileName, _T(".csv")); break;
                  //}

               //}

//            }

            //printf_line("WM_NOTIFY code %d", code);

         }
         

      }

      return 0;

   }


   void node::defer_add_to_system_recent_file_list(const ::file::path& pathNew)
   {

      if (file()->exists(pathNew))
      {

         auto wstrNew = pathNew.windows_path().path();

         SHAddToRecentDocs(SHARD_PATHW, wstrNew); 

      }

   }


   void node::_node_file_dialog(::file::file_dialog* pdialogParameter)
   {

      if (pdialogParameter->m_bSave && pdialogParameter->m_bMultiple)
      {

         throw ::exception(error_bad_argument, "save and multiple must not both be true.");

      }

      ::pointer < ::file::file_dialog > pdialog(pdialogParameter);

      user_post([pdialog]
         {

            //::file::path_array_base patha;

            OPENFILENAME openfilename;

            ZeroMemory(&openfilename, sizeof(OPENFILENAME));

            openfilename.lStructSize = sizeof(OPENFILENAME);
            
            memory memoryFileNames;
            
            const auto FILE_DIALOG_MAX_BUFFER = 256_MiB;

            memoryFileNames.set_size(FILE_DIALOG_MAX_BUFFER);

            memoryFileNames.zero();

            wchar_t* wszFileNames = (wchar_t*)memoryFileNames.data();

            openfilename.lpstrFile = wszFileNames;
            
            //;; ZeroMemory(tmp, FILE_DIALOG_MAX_BUFFER);

            openfilename.nMaxFile = (DWORD)memoryFileNames.size();

            openfilename.nFilterIndex = 1;

            memory memoryFilter;

            if (pdialog->m_bSave)
            {

               if (pdialog->m_filedialogfilter.has_element())
               {

                  pdialog->m_iFilter = 0;

               }
               else
               {

                  pdialog->m_iFilter = -1;

               }

            }

            if (!pdialog->m_bSave && pdialog->m_filedialogfilter.size() > 1) 
            {

               __wide_append(memoryFilter, "Supported file types (");

               for (::collection::index i = 0; i < pdialog->m_filedialogfilter.size(); ++i) 
               {
                  
                  //__wide_append(memoryFilter, "*.");

                  ::string strPatternList = pdialog->m_filedialogfilter[i].m_strPatternList;
                  
                  __wide_append(memoryFilter, strPatternList);

                  if (i + 1 < pdialog->m_filedialogfilter.size())
                  {

                     __wide_append(memoryFilter, ";");

                  }

               }

               __wide_append(memoryFilter, ")");

               __wide_append_null(memoryFilter);

               for (::collection::index i = 0; i < pdialog->m_filedialogfilter.size(); ++i) 
               {
               
                  //__wide_append(memoryFilter, "*.");

                  ::string strPatternList = pdialog->m_filedialogfilter[i].m_strPatternList;

                  __wide_append(memoryFilter, strPatternList);

                  if (i + 1 < pdialog->m_filedialogfilter.size())
                  {

                     __wide_append(memoryFilter, ";");

                  }

               }
               
               __wide_append_null(memoryFilter);

            }

            wstring wstrDefExt;

            bool bHasAllFiles = false;
            
            for (auto pair : pdialog->m_filedialogfilter) 
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

               string strDefExt = pair.m_strPatternList;

               strDefExt.begins_eat("*.");

               if (wstrDefExt.is_empty())
               {
                  
                  wstrDefExt = strDefExt;

               }

               if (strDefExt == "*")
               {

                  bHasAllFiles = true;

               }

            }

            __wide_append_null(memoryFilter);

            openfilename.lCustData = (LPARAM) pdialog.m_p;

            openfilename.lpfnHook = &CustomOFNHookProc;

            openfilename.lpstrFilter = (LPWSTR)memoryFilter.data();

            if (bHasAllFiles)
            {

               openfilename.lpstrDefExt = NULL;

            }
            else
            {

               openfilename.lpstrDefExt = wstrDefExt;

            }

            if (pdialog->m_bSave) 
            {

               //openfilename.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_OVERWRITEPROMPT;
               
               openfilename.Flags = OFN_EXPLORER | OFN_NOVALIDATE | OFN_OVERWRITEPROMPT | OFN_ENABLEHOOK;

               if (bHasAllFiles)
               {

                  openfilename.Flags |= OFN_EXTENSIONDIFFERENT;

               }

               openfilename.Flags |= OFN_DONTADDTORECENT;

               if (GetSaveFileNameW(&openfilename) == FALSE)
               {

                  t_popenfilename = nullptr;

                  pdialog->on_dialog_response();

                  return;

               }

               if (openfilename.nFilterIndex >= 1)
               {

                  auto iFilterIndex = openfilename.nFilterIndex - 1;

                  pdialog->m_iFilter = iFilterIndex;

               }

            }
            else 
            {

               openfilename.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

               if (pdialog->m_bMultiple)
               {

                  openfilename.Flags |= OFN_ALLOWMULTISELECT;

               }

               openfilename.Flags |= OFN_DONTADDTORECENT;
               
               if (GetOpenFileNameW(&openfilename) == FALSE)
               {

                  t_popenfilename = nullptr;

                  DWORD dwError = CommDlgExtendedError();

                  pdialog->on_dialog_response();

                  return;

               }

            }

            pdialog->set_ok_flag();

            t_popenfilename = nullptr;

            if (openfilename.Flags & OFN_ALLOWMULTISELECT)
            {

               if (*wszFileNames != L'\0')
               {

                  wstring wstrFolder(wszFileNames);

                  ::string strFolder(wstrFolder);

                  ::file::path pathFolder(strFolder);

                  wszFileNames += wcslen(wszFileNames) + 1;

                  if (*wszFileNames == L'\0')
                  {

                     auto path = pathFolder;

                     pdialog->m_patha.add(path);

                  }
                  else
                  {

                     while (*wszFileNames != L'\0')
                     {

                        wstring wstr(wszFileNames);

                        ::string str(wstr);

                        ::file::path path;

                        path = pathFolder / str;

                        pdialog->m_patha.add(path);

                        wszFileNames += wcslen(wszFileNames) + 1;

                     }

                  }

               }

            }
            else
            {

               while (*wszFileNames != L'\0')
               {

                  wstring wstr(wszFileNames);

                  ::string str(wstr);

                  ::file::path path(str);

                  pdialog->m_patha.add(path);

                  wszFileNames += wcslen(wszFileNames) + 1;

               }

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
      //      //            throw ::exception(error_failed, "popen() failed -- could not launch zenity!");
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
            pdialog->on_dialog_response();

         });

   }


} // namespace acme_windows




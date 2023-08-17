// Created by camilo on 2023-01-15 16:16 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "integration_context.h"
#include "acme_windows/registry.h"
#include "node.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
//#include "acme/filesystem/filesystem/file_context.h"
#include "acme/operating_system/process.h"
#include "acme/platform/application.h"
#include "acme/platform/system.h"


namespace acme_windows
{


   namespace integration
   {


      context::context()
      {

#ifdef WINDOWS

#if OSBIT == 64

         m_strPlatform = "x64";

#else

         m_strPlatform = "Win32";

#endif

#endif

      }


      context::~context()
      {


      }


      void context::prepare()
      {

         if (acmedirectory()->is("C:\\operating_system"))
         {

            m_pathOperatingSystemIncludeFolder = "C:\\operating_system\\operating_system-windows";

            m_pathOperatingSystemStorageFolder = "C:\\operating_system\\storage-windows";

            auto pathOperatingSystemIncludeFolder = m_pathOperatingSystemIncludeFolder;

            auto pathOperatingSystemStorageFolder = m_pathOperatingSystemStorageFolder / m_strPlatform / m_strConfiguration;

            acmedirectory()->create(pathOperatingSystemIncludeFolder / "include");

            acmedirectory()->create(pathOperatingSystemStorageFolder / "binary");

            acmedirectory()->create(pathOperatingSystemStorageFolder / "library");

            m_pathFolder = "C:\\port\\";

            ::integration::context::prepare();

         }

      }


      void context::prepare_compile_and_link_environment()
      {

         ::integration::context::prepare_compile_and_link_environment();

         //auto pacmedirectory = acmedirectory();

         //acmedirectory()->create(pacmedirectory->system() / "netnode_desktop/symbols");

         ::file::path strVars;

#ifdef WINDOWS_DESKTOP

         auto pacmedirectory = acmedirectory();

         ::file::path path;

         path = pacmedirectory->config() / "programming/vs.txt";

         auto pcontext = m_pcontext;

         m_strVs = acmefile()->as_string(path);

         m_strVs.trim();

         if (m_strVs == "2015")
         {

            payload("vstools") = "140";

            payload("sdk1") = "vc140";

         }
         else if (m_strVs == "2017")
         {

            payload("vstools") = "141";

            payload("sdk1") = "vc141";

         }
         else if (m_strVs == "2019")
         {

            payload("vstools") = "142";

            payload("sdk1") = "vc142";

         }
         else if (m_strVs == "2022")
         {

            payload("vstools") = "143";

            payload("sdk1") = "vc143";

         }
         else
         {

            string strMessage;

            strMessage = "There is a hole here. You should fill it with fullfillment. Missing f**k " + path;

            fatal() <<strMessage;

         }


#endif

         auto papp = acmeapplication();

#ifdef WINDOWS_DESKTOP

         try
         {

            if (m_strVs == "2022")
            {

               m_strContext = "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Auxiliary/Build/vcvarsall.bat";

               m_strVCVersion = papp->get_visual_studio_build();

            }
            else if (m_strVs == "2019")
            {

               m_strContext = "C:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat";

               m_strVCVersion = papp->get_visual_studio_build();

            }
            else if (m_strVs == "2017")
            {

               m_strContext = "C:/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat";

               ::acme_windows::registry::key key;

               key.open(HKEY_LOCAL_MACHINE, "SOFTWARE\\WOW6432Node\\Microsoft\\VisualStudio\\SxS\\VS7", false);

               string strPath;

               key.get("15.0", strPath);

               ::file::path path = strPath;

               m_strContext = path / "VC/Auxiliary/Build/vcvarsall.bat";

               m_strVCVersion = papp->get_visual_studio_build();

            }
            else if (m_strVs == "2015")
            {

               m_strContext = strVars.ascend(2);

               m_strContext = m_strContext / "vc\\vcvarsall.bat";

            }

         }
         catch (const ::e_status & estatus)
         {

            output_debug_string("failed to setup visual studio environment " + ::as_string(estatus.as_i64()));

         }

#endif

         //m_strTime = amcdir()->install() / ("time-" OPERATING_SYSTEM_NAME);


         if (m_strPlatform == "x64")
         {

#ifdef LINUX

            m_strPlat1 = "64";
            m_strStagePlatform = "x86";
            m_strLibPlatform = "x86/";

#else

            m_strPlat1 = "64";
            m_strPlat2 = "x86_amd64";
            //m_strPlat2 = "amd64";
            m_strStagePlatform = "x64";
            m_strLibPlatform = "x64/";

#endif

         }
         else if (m_strPlatform == "Win32")
         {

            m_strPlat1 = "32";
            m_strPlat2 = " x86";
            m_strStagePlatform = "x86";
            m_strLibPlatform = "x86/";

         }
         else
         {

            throw ::exception(error_wrong_state);

         }


#if defined(LINUX) || defined(MACOS)

         prepare1(m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash",
            m_strDynamicSourceConfiguration + "_cl" + m_strPlat1 + ".bash");
         prepare1(m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash",
            m_strDynamicSourceConfiguration + "_libc" + m_strPlat1 + ".bash");
         prepare1(m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash",
            m_strDynamicSourceConfiguration + "_libl" + m_strPlat1 + ".bash");

#else

         prepare1(m_strPlat1, m_strPlat1);

#endif

         if (m_bMsys)
         {
            //s += "set CHERE_INVOKING=1\n";
            //s += "set MSYSTEM=MSYS\n";
            //s += "set MSYS2_PATH_TYPE=inherit\n";


            acmenode()->set_environment_variable("CHERE_INVOKING", "1");
            acmenode()->set_environment_variable("MSYSTEM", "MSYS");
            acmenode()->set_environment_variable("MSYS2_PATH_TYPE", "inherit");

         }

      }


      void context::prepare1(const ::scoped_string & scopedstrSource, const ::string & scopedstrTarget)
      {

         //string_array stra;


         //string strLog;


         auto papp = acmeapplication();


#ifdef WINDOWS
         //sleep(15000_ms);

         string strBuildCmd = m_strContext;

         if (m_strVs == "2015")
         {

            strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;

         }
         else if (m_strVs == "2017")
         {

            strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();

         }
         else if (m_strVs == "2019")
         {

            strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();

         }
         else if (m_strVs == "2022")
         {

            //strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2 + " " + papp->get_visual_studio_build();

            strBuildCmd = "\""+m_strContext+"\" " + m_strStagePlatform;

         }

         //::operating_system::process_pointer process(e_create, this);

         //::file::path pathEnvTxt;

         auto pacmedirectory = acmedirectory();

         string strRel = prepare_path(m_pathFolder / m_pathBase / m_pathPlatformConfiguration);

         //pathEnvTxt = pacmedirectory->system() / strRel / "env.txt";

         //acmefile()->put_contents(pacmedirectory->system() / strRel / "env1.bat", pacmedirectory->system() / strRel / "env.bat > \"" + pathEnvTxt + "\"");

         //acmefile()->put_contents(pacmedirectory->system() / strRel / "env.bat", "@call " + strBuildCmd + "\r\n@set");

         auto psystem = acmesystem();

         auto pnode = psystem->node();

         //pnode->run_silent(pacmedirectory->system() / strRel / "env1.bat", "");

         int iExitCode = 0;

         string strCommand;

         //strCommand = "cmd.exe /c \"" + (pacmedirectory->system() / strRel / "env.bat") + "\"";
         ::string strCmd = acmenode()->get_environment_variable("ComSpec");
         strCommand = "\""+strCmd+"\" /c \"@call " + strBuildCmd + " && @set\"";

         string_array straOut;
         string_array straErr;

         auto functionTrace = [&](auto etracelevel, auto& str)
         {

            if (etracelevel <= e_trace_level_information)
            {

               straOut.add(str);

            }
            else
            {

               straErr.add(str);

            }

            std_inline_log()(etracelevel, str);

         };

         //int iStart = m_straLog.size();
         pnode->command_system(strCommand, functionTrace);
         //int iCount = m_straLog.size() - iStart;

         //m_straOutput.each([](auto & str) { str.case_insensitive_begins_eat("i: "); });
         //m_straOutput.each([](auto & str) { str.case_insensitive_begins_eat("e: "); });

         //m_straOutput.trim();
         //m_straOutput.erase_empty();

         straOut.trim();
         straOut.erase_empty();

         //strLog = acmefile()->as_string(pacmedirectory->system() / strRel / "env.txt");

         //stra.add_lines(strLog);

         //sleep(10000_ms);

#ifdef WINDOWS_DESKTOP

         property_set setEnvironment;

         setEnvironment.parse_environment_variable(straOut);

         for (auto & pproperty : setEnvironment)
         {

            auto strAtom = pproperty->m_atom.as_string();

            wstring wstrItem(strAtom);

            if (m_bMsys && strAtom.case_insensitive_equals("PATH"))
            {

               ::string strPath = pproperty->as_string();

               strPath = "C:\\msys64\\usr\\bin;" + strPath;

               SetEnvironmentVariableW(wstrItem, wstring(strPath));

               /*wstring wstrClPath;

               auto pszClPath = wstrClPath.get_buffer(4096);

               auto dwClPath  = SearchPathW(
  wstring(strPath),
  L"CL",
  L".EXE",
  4096,
  pszClPath,
  nullptr
               );

               wstrClPath.release_buffer(dwClPath);*/

               SetEnvironmentVariableW(L"CC", L"cl");

               auto pathPkgConfig = m_pathPrefix / "lib/pkgconfig";

               ::wstring wstrPkgConfigPath(pathPkgConfig);

               SetEnvironmentVariableW(L"PKG_CONFIG_PATH", wstrPkgConfigPath);

               //if (m_strPlatform.case_insensitive_equals("Win32"))
               //{

               //   SetEnvironmentVariableW(L"MSYSTEM", L"MINGW32");

               //}
               //else if (m_strPlatform.case_insensitive_equals("Win32"))
               //{

               //   SetEnvironmentVariableW(L"MSYSTEM", L"MINGW64");

               //}

            }
            else
            {

               wstring wstrPayload(pproperty->as_string());

               auto pszItem = wstrItem.c_str();

               auto pszPayload = wstrPayload.c_str();

               SetEnvironmentVariableW(pszItem, pszPayload);

            }

         }

#endif
#endif

         //   ::file::path strFolder;
         //   strFolder = dir()->install();
         //   if (!string_ends(strFolder, "/") && !string_ends(strFolder, "\\"))
         //      strFolder += "/";
         //   string strTemplate;
         //   string strSource = "platform/time-" OPERATING_SYSTEM_NAME"/dynamic_source/";
         //   strSource += lpcszSource;
         //
         //::file::path pathN = m_pathProjectDir;
         //pathN -= 3;
         //string strN = pathN;
         //strN.find_replace("\\", "/");
         //strN += "/";
         //
         //
         //   //#ifdef _DEBUG
         //   strTemplate = strFolder / strSource;
         //   //#else
         //   // strTemplate = strFolder, "app/time-" OPERATING_SYSTEM_NAME"/aura/account/app/main/matter/dynamic_source_cl.bat", false);
         //   //#endif
         //   string str;
         //   str = file()->as_string(strTemplate);
         //   /*string strVars = getenv("VS100COMNTOOLS");
         //   file()->path().eat_end_level(strVars, 2, "/");
         //   strVars += "vc/bin/vcvars32.bat";*/
         //   str.replace("%VS_VARS%", m_strContext);
         //   str.replace("%VS_VARS_PLAT2%", m_strPlat2);
         //
         //   string strV(dir()->install());
         //   strV.replace("\\", "/");
         //   if (!string_ends(strV, "/") && !string_ends(strV, "\\"))
         //      strV += "/";
         //   str.replace("%CA2_ROOT%", strV);
         //   str.replace("%PROJECT_DIR%", m_pathProjectDir);
         //   str.replace("%NETNODE_ROOT%", strN);
         //   str.replace("%SDK1%", m_strSdk1);
         //   string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
         //   ::file::path strCmd;
         //   //#ifdef _DEBUG
         //   strCmd = strFolder / strDest;
         //   //#else
         //   // strCmd = strFolder, "app\\time-" OPERATING_SYSTEM_NAME"\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
         //   //#endif
         //   dir()->create(strCmd.folder());
         //   //file()->put_text_utf8(strCmd, str);
         //   file()->put_contents(strCmd, str);
         //   dir()->create(m_strTime / "dynamic_source");
         //
         //
         //   string strBuildCmd = m_strContext;
         //
         //   strBuildCmd = "\"" + strBuildCmd + "\" " + m_strPlat2;
         //
         //   ::process::process_pointer process(e_create);
         //
         //
         //   acmefile()->put_contents(pacmedirectory->system() / "env.bat","@call " + strBuildCmd + " "+m_strVCVersion+"\r\n@set");
         //
         //   set_thread_priority(::e_priority_highest);
         //   process->prop("inherit") = false;
         //
         //   ::file::path pathCommand =          auto psystem = acmesystem();

         //         auto pacmedirectory = psystem->m_pacmedirectory;
         //
         //pacmedirectory->system() / "env.bat";
         //
         //   ::file::path pathFolder = ::file::path(m_strContext).folder();
         //
         //#ifdef WINDOWS_DESKTOP
         //   {
         //      u32 dwSize = GetEnvironmentVariable("PATH", nullptr, 0);
         //      char * lpsz = memory_new char[dwSize + 1];
         //      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1);
         //      delete lpsz;
         //   }
         //
         //   #endif
         //
         //   process->create_child_process(pathCommand,true,pathFolder,::e_priority_highest);
         //   string strLog;
         //
         //   //   EnvVarValArray arrEnvVarVal;
         //
         //   //   ::time tickStart= ::time::now();
         //
         //   //   u32 dwExitCode;
         //
         //   //   string strLog;
         //
         //   //   string_array m_strArray;
         //   //   // Open the process for further operations
         //   //   HANDLE hProcess = CProcessEnvReader::OpenProcessToRead(process->m_iPid);
         //   //   if(hProcess)
         //   //   {
         //   //      _ENVSTRING_t stEnvData;
         //   //      // Read the process environment block
         //   //      if(!CProcessEnvReader::ReadEnvironmentBlock(hProcess,stEnvData))
         //   //      {
         //   //         return;
         //   //      }
         //
         //   //      // Parse the retrieved data
         //   //      CProcessEnvReader::ParseEnvironmentStrings(stEnvData.pData,
         //   //         stEnvData.nSize / 2,
         //   //         m_strArray);
         //
         //
         //   //      // Seperate values and variables
         //   //      CProcessEnvReader::SeparateVariablesAndValues(m_strArray,arrEnvVarVal);
         //
         //   //      // UpdateProcessMiscInfo( hProcess, pNMItemActivate->iItem);
         //   //      CProcessEnvReader::ReleaseHandle(hProcess);
         //   //   }
         //   //process->write("\n");
         //   u32 dwExitCode;
         //   ::u32 tickStart= ::time::now();
         //   while(::task_get_run() && task_get_run())
         //   {
         //
         //      strLog += process->read();
         //
         //      if(process->has_exited(&dwExitCode))
         //         break;
         //
         //      sleep(100_ms);
         //
         //      if(tickStart.elapsed() > 840 * 1000) // 14 minutes
         //      {
         //
         //         //            bTimeout = true;
         //
         //         break;
         //
         //      }
         //
         //   }
         //
         //   strLog += process->read();
         //   string_array stra;
         //
         //   stra.add_lines(strLog);
         //
         //   #ifdef WINDOWS_DESKTOP
         //   {
         //      u32 dwSize = GetEnvironmentVariable("PATH", nullptr, 0);
         //      char * lpsz = memory_new char[dwSize + 1];
         //      dwSize = GetEnvironmentVariable("PATH", lpsz, dwSize + 1);
         //      delete lpsz;
         //   }
         //   #endif
         //
         //   //sleep(10000_ms);
         //
         //#if defined(WINDOWS_DESKTOP)
         //   EnvVarValArray arrEnvVarVal;
         //   // Seperate values and variables
         //   CProcessEnvReader::SeparateVariablesAndValues(stra,arrEnvVarVal);
         //
         //   string_to_string map;
         //
         //   for(auto pair : arrEnvVarVal)
         //   {
         //      map[pair.element1()] = pair.element2();
         //      SetEnvironmentVariable(pair.element1(),pair.element2());
         //   }
         //
         //
         //
         //   //SetEnvironmentVariable("INCLUDE",map["INCLUDE"]);
         //   //SetEnvironmentVariable("LIBPATH",map["LIBPATH"]);
         //   //SetEnvironmentVariable("PATH",map["PATH"]);
         //
         //   // UpdateProcessMiscInfo( hProcess, pNMItemActivate->iItem);
         //   //CProcessEnvReader::ReleaseHandle(hProcess);
         //
         //#endif
         //
         //stra.add_lines(strLog);

         //string strEnv = acmefile()->as_string(         auto psystem = acmesystem();

      //         auto pacmedirectory = psystem->m_pacmedirectory;
      //
      //pacmedirectory->system() / "env.txt");

         //::file::path strFolder;
         //strFolder = dir()->install();
         //if (!string_ends(strFolder, "/") && !string_ends(strFolder, "\\"))
         //   strFolder += "/";
         //string strTemplate;
         //string strSource = "operating_system/operating_system-" OPERATING_SYSTEM_NAME "/_stage/dynamic_source/";
         //strSource += lpcszSource;

         //   string strN = m_pmanager->m_strNetnodePath;
               //strN.replace("\\","/");
               //if(!string_ends(strN,"/") && !string_ends(strN,"\\"))
               // strN += "/";

               //#ifdef _DEBUG
         //strTemplate = strFolder / strSource;
         //#else
         // strTemplate = strFolder, "app/_stage/aura/account/app/main/matter/dynamic_source_cl.bat", false);
         //#endif
         //string str;
         //str = file()->safe_get_string(strTemplate);
         /*string strVars = getenv("VS100COMNTOOLS");
         file()->path().eat_end_level(strVars, 2, "/");
         strVars += "vc/bin/vcvars32.bat";*/
         //str.find_replace("%VS_VARS%", m_strContext);
         //str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);

         //string strV(dir()->install());
         //strV.find_replace("\\", "/");
         //if (!string_ends(strV, "/") && !string_ends(strV, "\\"))
         //   strV += "/";
         //str.find_replace("%CA2_ROOT%", strV);
         //str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
         //str.find_replace("%NETNODE_ROOT%", strN);
         //str.find_replace("%SDK1%", m_strSdk1);
         ////str.replace("%DVP%", strDVP_B);

         //string strDest = m_strDynamicSourceStage / "front" / lpcszDest;
         //::file::path strCmd;
         ////#ifdef _DEBUG
         //strCmd = strFolder / strDest;
         ////#else
         //// strCmd = strFolder, "app\\_stage\\aura\\account\\app\\main\\front\\dynamic_source_cl.bat", false);
         ////#endif
         //dir()->create(strCmd.folder());
         ////file()->put_text_utf8(strCmd, str);
         //file()->put_text(strCmd, str);
         //dir()->create(m_strTime / "dynamic_source");


      }



      ::string context::prepare_path(const ::file::path & path)
      {

         string strSource;

         strSource = path;

         if (strSource.begins_eat("C:\\"))
         {

            strSource = "/c/" + strSource;

         }

         strSource.find_replace("\\", "/");

         return strSource;

      }


      void context::prepare_compilation_script(::string& str)
      {


         ::integration::context::prepare_compilation_script(str);

         
         str.find_replace("%VS_VARS%", m_strContext);
         str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
         str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
         str.find_replace("%SDK1%",payload("sdk1").as_string());


         // programming/compiler
   //      str.find_replace("%VS_VARS%", m_strContext);
   //      str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
   //      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
   //      str.find_replace("%SDK1%", m_strSdk1);


   // script_compiler cl
   //      str.find_replace("%VS_VARS%",m_strContext);
   //      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
   //      str.find_replace("%PLATFORM%",m_strPlatform);
   //      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
   //      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
   //      str.find_replace("%SDK1%",m_strSdk1);


         

      }


      void context::prepare_linking_script(::string& str)
      {

         ::integration::context::prepare_linking_script(str);


         str.find_replace("%VS_VARS%", m_strContext);
         str.find_replace("%VS_VARS_PLAT2%", m_strPlat2);
         str.find_replace("%STAGEPLATFORM%", m_strStagePlatform);
         str.find_replace("%SDK1%", payload("sdk1").as_string());
         str.find_replace("%LIBPLATFORM%", m_strLibPlatform);


         //      str.find_replace("%VS_VARS%",m_strContext);
         //      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
         //      str.find_replace("%PROJECT_DIR%", m_pathProjectDir);
         //      str.find_replace("%PLATFORM%",m_strPlatform);
         //      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
         //      str.find_replace("%SDK1%",m_strSdk1);


         // script_compiler cl
         //      str.find_replace("%VS_VARS%",m_strContext);
         //      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
         //      str.find_replace("%PLATFORM%",m_strPlatform);
         //      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
         //      str.find_replace("%SDK1%",m_strSdk1);


         // script_compiler cl 2
         //      str.find_replace("%VS_VARS%",m_strContext);
         //      str.find_replace("%VS_VARS_PLAT2%",m_strPlat2);
         //      str.find_replace("%PLATFORM%",m_strPlatform);
         //      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      //      str.find_replace("%LIBPLATFORM%", m_strLibPlatform);
         //      str.find_replace("%SDK1%",m_strSdk1);


         // script_compiler cl 3
         //      str.find_replace("%PLATFORM%",m_strPlatform);
         //      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      str.find_replace("%LIBPLATFORM%",m_strLibPlatform);
         //      str.find_replace("%SDK1%",m_strSdk1);


         // script_compiler cl 4
         //      str.find_replace("%PLATFORM%",m_strPlatform);
         //      str.find_replace("%STAGEPLATFORM%",m_strStagePlatform);
         //      str.find_replace("%LIBPLATFORM%",m_strLibPlatform);
         //      str.find_replace("%SDK1%",m_strSdk1);

      }




   } // namespace integration




   void node::integration_factory()
   {

      acmesystem()->m_psubsystem->m_pfactory->add_factory_item < ::acme_windows::integration::context, ::integration::context >();

   }


} // namespace acme_windows




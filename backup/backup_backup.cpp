#include "framework.h"


namespace backup
{


   backup::backup(::particle * pparticle) :
      ::object(pobject),
      thread(pobject),
      production(pobject)
   {
      m_bClean       = false;
      m_bBuild       = true;
      m_bFinished    = true;
      m_eversion     = version_stage;
   }

   backup::~backup()
   {
   }

   string backup::get_new_repos_local_path(const ::scoped_string & scopedstr)
   {
      string strNewRepos;
      strNewRepos.Format("V:\\ca2\\bk\\%s\\repos\\%s", m_strTag, psz);
      return strNewRepos;
   }

   string backup::get_new_db_local_path(const ::scoped_string & scopedstr)
   {
      string strNewRepos;
      strNewRepos.Format("V:\\ca2\\bk\\%s\\db\\%s", m_strTag, psz);
      return strNewRepos;
   }


   void     backup::run()
   {

      if(m_iStep == 1)
      {
         string strStartTime;
         m_timeStart.Format(strStartTime, "%Y-%m-%d %H-%M-%S");
         add_status("Backup starting at " + strStartTime);
         add_status(unitext("Thank you!!"));
         m_tickStart = ::GetTickCount();
         m_timeStart.Format(m_strTag, "%Y-%m-%d_%H-%M-%S");

         __keep(&m_bFinished, false, true, true);
         string str;

         string strFile = dir().install() / "basis/ca2/app/dbbk.bat";
         if(!file().exists(strFile))
         {
            string str;
            str.formatf("***File %s does not exist. (mysqldump -uroot -ppassword --opt --all-databases > %%1)", strFile);
            add_status(str);
            return error_failed;
         }

         if (!hotcopy_repos("ca2os"))
         {

            return error_failed;

         }

         if(!hotcopy_repos("app"))
         {

            return error_failed;

         }

         if(!hotcopy_repos("net"))
         {

            return error_failed;

         }

         if(!hotcopy_repos("hi5"))
         {

            return error_failed;

         }

         if(!hotcopy_repos("hi5-net"))
         {

            return error_failed;

         }

         if(!hotcopy_repos("public_reading"))
         {

            return error_failed;

         }

         if(!hotcopy_repos("main"))
         {

            return error_failed;

         }

         if(!all_db_dump())
         {

            return error_failed;

         }



         if(!compress_repos("ca2os"))
         {

            return error_failed;

         }

         if(!compress_repos("app"))
         {

            return error_failed;

         }

         if(!compress_repos("net"))
         {

            return error_failed;

         }

         if(!compress_repos("hi5"))
         {

            return error_failed;

         }

         if(!compress_repos("hi5-net"))
         {

            return error_failed;

         }

         if (!compress_repos("public_reading"))
         {

            return error_failed;

         }

         if(!compress_repos("main"))
         {

            return error_failed;

         }

         if(!db_copy())
         {

            return error_failed;

         }

         //throw ::not_implemented(get_application());

         //m_bFinished = true;
         //m_timeEnd = ::earth::time::now();
         //m_tickEnd = ::GetTickCount();
         //auto dwMin = (m_tickEnd - m_tickStart) / 1000 / 60;
         //auto dwSeg = ((m_tickEnd - m_tickStart) / 1000) % 60;
         //string strTime;

         //m_timeStart.Format(strStartTime, "%Y-%m-%d %H-%M-%S");
         //string strEndTime;
         //m_timeEnd.Format(strEndTime, "%Y-%m-%d %H-%M-%S");
         //add_status("Backup started at " + strStartTime);
         //add_status("Backup ending at " + strEndTime);
         //strTime.Format("Backup took: %dm %ds", dwMin, dwSeg);
         //add_status(strTime);
         //add_status(unitext("Finished!! Thank you!!"));
         //add_status("");
         //add_status("");
         //add_status("");
         //add_status("");
         //add_status("");
      }


   }


   bool  backup::hotcopy_repos(const ::scoped_string & scopedstr)
   {
      string strStatus;
      strStatus.Format("hotcopy repository: %s ...", psz);
      add_status(strStatus);

      string str;
      string strBase = m_strBase;
      STARTUPINFO si;
      PROCESS_INFORMATION pi;
      memory_set(&si, 0, sizeof(si));
      memory_set(&pi, 0, sizeof(pi));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_HIDE;
      ::file::path strNewRepos = get_new_repos_local_path(psz);
      dir().create(strNewRepos.folder());
      str.formatf("svnadmin hotcopy C:\\repos\\%s %s", psz, strNewRepos);

      if(!::CreateProcess(nullptr, (LPTSTR) (const ::string &) str, nullptr, nullptr, false, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi))
      {
         strStatus.Format("     Error: Check svn installation!!");
         add_status(strStatus);
         return false;
      }

      DWORD dwExitCode;
      int i = 1;
      while(true)
      {
         if(!GetExitCodeProcess(pi.hProcess, &dwExitCode))
            break;
         if(dwExitCode != STILL_ACTIVE)
            break;
         Sleep(2300);
         str.formatf("%d hotcopy repository: %s ...", i, psz);
         add_status(str);
         i++;
      }
      return true;
   }

   bool  backup::all_db_dump()
   {
      string strStatus;
      strStatus.Format("dumping all databases");
      add_status(strStatus);

      string str;
      string strBase = m_strBase;
      STARTUPINFOW si;
      PROCESS_INFORMATION pi;
      memory_set(&si, 0, sizeof(si));
      memory_set(&pi, 0, sizeof(pi));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_HIDE;
      ::file::path strdump = get_new_db_local_path("all.sql");
      dir().create(strdump.folder());

      str.formatf("%s \"%s\"", dir().install() / "basis/ca2/app/dbbk.bat", strdump);

      wstring wstr(str);

      if(!::CreateProcessW(nullptr, (LPWSTR) (const wchar_t *) wstr,
                          nullptr, nullptr, false, 0, nullptr,
                          L"C:\\", &si, &pi))
      {
         strStatus.Format("     Error: Check svn installation!!");
         add_status(strStatus);
         return false;
      }

      DWORD dwExitCode;
      int i = 1;
      while(true)
      {
         if(!GetExitCodeProcess(pi.hProcess, &dwExitCode))
            break;
         if(dwExitCode != STILL_ACTIVE)
            break;
         Sleep(2300);
         str.formatf("%d dumping all databases ...", i);
         add_status(str);
         i++;
      }
      return true;
   }

   bool  backup::compress_repos(const ::scoped_string & scopedstr)
   {
      string strStatus;
      strStatus.Format("compressing repository: %s ...", psz);
      add_status(strStatus);

      string str;
      string strBase = m_strBase;
      STARTUPINFO si;
      PROCESS_INFORMATION pi;
      memory_set(&si, 0, sizeof(si));
      memory_set(&pi, 0, sizeof(pi));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = SW_HIDE;
      string strNewRepos = get_new_repos_local_path(psz);
      ::file::path strTar;
      strTar = ::file::path("C:\\ca2\\bk") / m_strTag  / "repos" / psz + ".tar";
      dir().create(strTar.folder());
      str.formatf("7za.exe a -r -ttar \"%s\" \"%s\"", strTar, strNewRepos);

      if(!::CreateProcess(nullptr, (LPTSTR) (const ::string &) str, nullptr, nullptr, false, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi))
      {
         strStatus.Format("     Error: Check 7-zip installation! Cannot 7za.exe command line utility!");
         add_status(strStatus);
         return false;
      }

      DWORD dwExitCode;
      int i = 1;
      while(true)
      {
         if(!GetExitCodeProcess(pi.hProcess, &dwExitCode))
            break;
         if(dwExitCode != STILL_ACTIVE)
            break;
         Sleep(2300);
         str.formatf("%d compressing repository: %s ...", i, psz);
         add_status(str);
         i++;
      }
      return true;
   }



   bool  backup::db_copy()
   {

      string strStatus;
      strStatus.Format("duplicating db backup ...");
      add_status(strStatus);

      string strSrc = get_new_db_local_path("all.sql");
      string strDst;
      strDst.Format("C:\\ca2\\bk\\%s\\db\\all.sql", m_strTag);
      file().copy(strDst, strSrc);

      return true;

   }


} // namespace backup





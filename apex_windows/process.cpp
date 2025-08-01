#include "framework.h"
#include "process.h"
#include "acme/exception/exception.h"
#include "acme/prototype/string/parse.h"
#include "acme/prototype/string/str.h"
#include "acme_windows/pipe.h"
#include "acme_windows/uac_tools.h"
#include "acme/operating_system/windows_common/_string.h"


#include "acme/_operating_system.h"


namespace apex_windows
{


   process::process()
   {

      memory_set(&m_pi,0,sizeof(PROCESS_INFORMATION));

      memory_set(&m_si,0,sizeof(STARTUPINFO));

   }


   process::~process()
   {

      if(m_pi.hProcess != INVALID_HANDLE_VALUE && m_pi.hProcess != nullptr)
      {

         CloseHandle(m_pi.hProcess);

      }

      if(m_pi.hThread != INVALID_HANDLE_VALUE && m_pi.hThread != nullptr)
      {

         CloseHandle(m_pi.hThread);

      }

   }


   bool process::create_child_process(const ::scoped_string & scopedstrCmdLine, bool bPiped, const ::scoped_string & scopedstrDir, ::enum_priority epriority)
   {

      if (!::operating_system::process::create_child_process(scopedstrCmdLine, bPiped, scopedstrDir, epriority))
      {

         return false;

      }

      string szCmdline = scopedstrCmdLine;

      bool bSuccess = false;

      m_si.cb = sizeof(STARTUPINFO);

      if(bPiped)
      {

         auto ppipeOut        = m_pipe.m_ppipeOut.cast < ::acme_windows::pipe >();

         m_si.hStdError       = ppipeOut->m_hWrite;

         m_si.hStdOutput      = ppipeOut->m_hWrite;

         ::acme_windows::pipe * ppipeIn       = m_pipe.m_ppipeIn.cast < ::acme_windows::pipe >();

         m_si.hStdInput       = ppipeIn->m_hRead;

         m_si.dwFlags         |= STARTF_USESTDHANDLES;

      }

      /* STARTUPINFO si;
      PROCESS_INFORMATION pi;
      memory_set(&si, 0, sizeof(si));
      memory_set(&pi, 0, sizeof(pi));
      si.cb = sizeof(si);
      si.dwFlags = STARTF_USESHOWWINDOW;
      si.wShowWindow = e_display_none; */
      //         if(!::CreateProcess(nullptr, (char *) (const ::string &) m_papplication->dir().appdata("production\\build.bat"), nullptr, nullptr, false, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi))
      m_si.dwFlags |= STARTF_USESHOWWINDOW;
      m_si.wShowWindow = e_display_none;


      unsigned int dwPriorityClass = ::get_os_priority_class(epriority);

      wstring wstrDir(scopedstrDir);

      const unichar * pwszDir;

      if (scopedstrDir.is_empty())
      {

         pwszDir = nullptr;

      }
      else
      {

         pwszDir = wstrDir;

      }

      // create the child process.

      wstring wstrCommandLine;

      if(szCmdline.case_insensitive_ends(".bat"))
      {

         string strCmd;

         strCmd = "";
         strCmd += szCmdline;
         strCmd += "";

         wstrCommandLine = strCmd;

      }
      else
      {

         wstrCommandLine = szCmdline;

      }

      unichar * pwszCommandLine = (unichar * ) (const unichar *) wstrCommandLine;
      unsigned int dwFlags = 0;
      if (is_true("inherit"))
      {
         dwFlags = CREATE_NEW_CONSOLE | CREATE_UNICODE_ENVIRONMENT;
      }

      bSuccess = CreateProcessW(nullptr,
                                pwszCommandLine,
                                nullptr,          // process security attributes
                                nullptr,          // primary thread security attributes
                                true,          // handles are inherited
                                dwFlags | dwPriorityClass,             // creation flags
                                nullptr,          // use parent's environment
                                pwszDir,
                                &m_si,  // STARTUPINFO pointer
                                &m_pi) != false;  // receives PROCESS_INFORMATION

      // If an error occurs, exit the application.
      if (!bSuccess)
      {

         DWORD dwLastError = ::GetLastError();

         string strMessage = ::windows::last_error_message(dwLastError);

         output_debug_string("command line: \"" + string(pwszCommandLine) + "\"");
         output_debug_string("\r\n");
         output_debug_string("CreateProcessW Error!!");
         output_debug_string("\r\n");
         output_debug_string(strMessage + " (" + ::as_string((unsigned int) dwLastError) + ")");
         output_debug_string("\r\n");

         return false;

      }
      else
      {

         m_iPid = m_pi.dwProcessId;

         // close handles to the child process and its primary thread.
         // Some applications might keep these handles to monitor the status
         // of the child process, for example.

         //CloseHandle(m_pi.hProcess);
         //CloseHandle(m_pi.hthread);

      }

      return true;

   }


   bool process::has_exited()
   {

      DWORD dwExitCode;

      bool bExited;

      if(!GetExitCodeProcess(m_pi.hProcess,&dwExitCode))
      {

         m_exitstatus.m_iExitCode = -1;

         bExited = true;

      }
      else
      {

         if(dwExitCode == STILL_ACTIVE)
         {

            bExited = false;

         }
         else
         {

            bExited = true;

         }

      }

      m_exitstatus.m_iExitCode = dwExitCode;

      return bExited;

   }


   bool process::synch_elevated(const ::scoped_string & scopedstrCmdLine,int iShow,const class time & timeTimeOut,bool * pbTimeOut)
   {

      DWORD dwExitCode = 0;

      HANDLE h = nullptr;

      ::parse parse(scopedstrCmdLine,strlen(scopedstrCmdLine), "= "_ansi);

      parse.EnableQuote(true);

      string strPath;

      if(parse.getrestlen())
      {

         parse.getword(strPath);

      }

      string strParam;

      parse.getrest(strParam);

      if(uac_tools::run_elevated(nullptr,strPath,strParam,nullptr,&h))
      {

         dwExitCode = 0;

      }
      else
      {

         return false;

      }

      bool bTimedOut = true;

      auto tickStart = ::time::now();

      auto tickTimeout = timeTimeOut;

      while(tickStart.elapsed() < tickTimeout)
      {

         if (!::GetExitCodeProcess(h, &dwExitCode))
         {

            break;

         }

         if(dwExitCode != STILL_ACTIVE)
         {

            bTimedOut = false;

            break;

         }

         sleep(100_ms);

      }

      ::CloseHandle(h);

      if(pbTimeOut != nullptr)
      {

         *pbTimeOut = bTimedOut;

      }

      return !bTimedOut;

   }


   bool process::kill()
   {

      throw ::exception(::error_failed, "serious?! I don't believe... LOL...");
      
      //::system(string("taskkill /F /T /PID " ) + ::as_string((int) m_pi.dwProcessId));

      return true;
      //return TerminateProcess(m_pi.hthread, -1) != false;

   }


} // namespace apex_windows




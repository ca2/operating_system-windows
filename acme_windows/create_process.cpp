// Created by camilo on 2024-03-07 10:48 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "create_process.h"
#include "acme/parallelization/manual_reset_event.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/primitive/string/str.h"


namespace acme_windows
{


   create_process::create_process()
   {

      m_hOutRd = nullptr;
      m_hOutWr = nullptr;
      m_hErrRd = nullptr;
      m_hErrWr = nullptr;
      m_hInRd = nullptr;
      m_hInWr = nullptr;
      m_pattrList = nullptr;
      m_iExitCode = 0;
      m_dwExitCode2 = 0;
      m_dwCreationFlags = 0;

   }


   create_process::~create_process()
   {
      if (m_hOutRd) ::CloseHandle(m_hOutRd);
      if (m_hOutWr) ::CloseHandle(m_hOutWr);
      if (m_hErrRd) ::CloseHandle(m_hErrRd);
      if (m_hErrWr) ::CloseHandle(m_hErrWr);
      if (m_hInRd) ::CloseHandle(m_hInRd);
      if (m_hInWr) ::CloseHandle(m_hInWr);
      if (m_pi.hProcess)::CloseHandle(m_pi.hProcess);
      if (m_pi.hThread)::CloseHandle(m_pi.hThread);

      //::CloseHandle(hInWr);


      m_hOutRd = nullptr;
      m_hOutWr = nullptr;
      m_hErrRd = nullptr;
      m_hErrWr = nullptr;
      m_hInRd = nullptr;
      m_hInWr = nullptr;

      if (m_pattrList)
      {

         DeleteProcThreadAttributeList(
            m_pattrList
         );
         m_pattrList = nullptr;
      }

   }


   SECURITY_ATTRIBUTES* create_process::__sa()
   {

      if (m_saAttr.nLength == 0)
      {

         ZeroMemory(&m_saAttr, sizeof(m_saAttr));

         m_saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
         m_saAttr.bInheritHandle = TRUE;
         m_saAttr.lpSecurityDescriptor = NULL;

      }

      return &m_saAttr;

   }

   void create_process::initialize_stdout()
   {


      // Create a pipe for the child process's STDOUT. 

      if (!CreatePipe(&m_hOutRd, &m_hOutWr, __sa(), (DWORD)m_iPipeSize))
      {

         // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }

      // Ensure the read handle to the pipe for STDOUT is not inherited.
      if (!SetHandleInformation(m_hOutRd, HANDLE_FLAG_INHERIT, 0))
      {

         //::CloseHandle(m_hOutRd);
         //::CloseHandle(m_hOutWr);

         //m_hOutRd = nullptr;
         //m_hOutWr = nullptr;

         // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }


      // Ensure the read handle to the pipe for STDOUT is not inherited.
      if (!SetHandleInformation(m_hOutWr, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
      {

         //::CloseHandle(m_hOutRd);
         //::CloseHandle(m_hOutWr);

         // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }


   }
   void create_process::initialize_stderr()
   {


      // Create a pipe for the child process's STDOUT. 

      if (!CreatePipe(&m_hErrRd, &m_hErrWr, __sa(), (DWORD)m_iPipeSize))
      {

         //::CloseHandle(hOutRd);
         //::CloseHandle(hOutWr);

         // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }


      // Ensure the read handle to the pipe for STDOUT is not inherited.
      if (!SetHandleInformation(m_hErrRd, HANDLE_FLAG_INHERIT, 0))
      {

         //::CloseHandle(hOutRd);
         //::CloseHandle(hOutWr);
         //::CloseHandle(hErrRd);
         //::CloseHandle(hErrWr);

         // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }


      // Ensure the read handle to the pipe for STDOUT is not inherited.
      if (!SetHandleInformation(m_hErrWr, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
      {

         //::CloseHandle(hOutRd);
         //::CloseHandle(hOutWr);
         //::CloseHandle(hErrRd);
         //::CloseHandle(hErrWr);

         // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }
   }

   void create_process::initialize_stdin()
   {

      // Create a pipe for the child process's STDOUT. 

      if (!CreatePipe(&m_hInRd, &m_hInWr, __sa(), (DWORD)m_iPipeSize))
      {

         //::CloseHandle(hOutRd);
         //::CloseHandle(hOutWr);
         //::CloseHandle(hErrRd);
         //::CloseHandle(hErrWr);

         // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }


      // Ensure the read handle to the pipe for STDOUT is not inherited.
      if (!SetHandleInformation(m_hInWr, HANDLE_FLAG_INHERIT, 0))
      {

         /*           ::CloseHandle(hOutRd);
                    ::CloseHandle(hOutWr);
                    ::CloseHandle(hErrRd);
                    ::CloseHandle(hErrWr);
                    ::CloseHandle(hInRd);
                    ::CloseHandle(hInWr);*/

                    // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }
      if (!SetHandleInformation(m_hInRd, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT))
      {

         //::CloseHandle(hOutRd);
         //::CloseHandle(hOutWr);
         //::CloseHandle(hErrRd);
         //::CloseHandle(hErrWr);
         //::CloseHandle(hInRd);
         //::CloseHandle(hInWr);

         // log error
         DWORD dwLastError = GetLastError();

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }

      //{

      //   DWORD dwState = PIPE_NOWAIT;

      //   SetNamedPipeHandleState(hOutRd, &dwState, nullptr, nullptr);

      //}

      //{

      //   DWORD dwState = PIPE_NOWAIT;

      //   SetNamedPipeHandleState(hErrRd, &dwState, nullptr, nullptr);

      //}

      //{

      //   DWORD dwState = PIPE_NOWAIT;

      //   SetNamedPipeHandleState(hInWr, &dwState, nullptr, nullptr);

      //}


   }

   //straOutput.clear();

   void create_process::prepare()
   {

      SIZE_T sizeAttrList = 0;
      InitializeProcThreadAttributeList(
         NULL,
         1,
         0,
         &sizeAttrList
      );
      m_memoryAttrList.set_size(sizeAttrList);
      m_pattrList = (LPPROC_THREAD_ATTRIBUTE_LIST)m_memoryAttrList.data();
      InitializeProcThreadAttributeList(
         m_pattrList,
         1,
         0,
         &sizeAttrList
      );


      HANDLE hList[3];

      hList[0] = m_hErrWr;
      hList[1] = m_hOutWr;
      hList[2] = m_hInRd;

      UpdateProcThreadAttribute(
         m_pattrList,
         0,
         PROC_THREAD_ATTRIBUTE_HANDLE_LIST,
         hList,
         sizeof(hList),
         nullptr,
         nullptr
      );

      ZeroMemory(&m_si, sizeof(m_si));
      m_si.StartupInfo.cb = sizeof(m_si);
      m_si.StartupInfo.hStdError = m_hErrWr;
      m_si.StartupInfo.hStdOutput = m_hOutWr;
      m_si.StartupInfo.hStdInput = m_hInRd;
      m_si.StartupInfo.wShowWindow = SW_HIDE; // Don't show the console window (DOS box)
      m_si.StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
      m_si.StartupInfo.dwFlags |= STARTF_USESTDHANDLES;
      m_si.lpAttributeList = m_pattrList;
      //m_si.StartupInfo.wShowWindow = SW_HIDE; // Don't show the console window (DOS box)
      //m_si.StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;


      ZeroMemory(&m_pi, sizeof(m_pi));

   }


   void create_process::set_create_new_console()
   {

      m_dwCreationFlags |= CREATE_NEW_CONSOLE;

   }


   void create_process::call_create_process(const ::scoped_string& scopedstr)
   {




      string str(scopedstr);


      ::string str1;
      auto range = str();
      range.m_erange = e_range_none;
      try
      {
         str1 = range.consume_quoted_value();

      }
      catch (...)
      {


      }
      ::string str2;
      if (str1.is_empty() || str1.case_insensitive_ends(".cmd"))
      {
         ::string strCmd = node()->get_environment_variable("ComSpec");
         str1 = strCmd;
         str2 = "\"" + strCmd + "\" /c " + scopedstr;
      }
      else
      {

         str2 = scopedstr;
         str2.trim();
      }

      wstring wstr1;
      wstring wstr2;

      wstr1 = str1;
      wstr2 = str2;

      //STARTUPINFO si = { {sizeof(si)} };
      //PROCESS_INFORMATION pi = {};


      //ZeroMemory(&si, sizeof(si));
      //m_si.cb = sizeof(m_si);
      //m_si.wShowWindow = SW_HIDE; // Don't show the console window (DOS box)
      //m_si.dwFlags |= STARTF_USESHOWWINDOW;




      if (!CreateProcessW(
         (WCHAR*)wstr1.c_str(),
         (WCHAR*)wstr2.c_str(),
         NULL,
         NULL,
         TRUE,
         m_dwCreationFlags,
         NULL,
         NULL,
         &m_si.StartupInfo,
         &m_pi))
      {

         DWORD dwLastError = ::GetLastError();

         printf("Create Process(2) failed with lasterror = %d\n", dwLastError);
         printf("Parameters(2): %s %s\n", str1.c_str(), str2.c_str());

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }

      ::CloseHandle(m_hOutWr);
      ::CloseHandle(m_hErrWr);
      ::CloseHandle(m_hInRd);
      m_hOutWr = nullptr;
      m_hErrWr = nullptr;
      m_hInRd = nullptr;

   }

   void create_process::wait_process(const trace_function& tracefunction)
   {

      auto peventEndOut = __create_new < manual_reset_event >();

      application()->fork([this, tracefunction, peventEndOut]()
         {

            char sz[256];

            while (true)
            {

               DWORD dwRead = 0;

               if (!ReadFile(m_hOutRd, sz, 256, &dwRead, nullptr))
               {

                  break;

               }

               if (dwRead == 0)
               {

                  break;

               }

               string str(sz, dwRead);

               m_strOutput += str;

               if (tracefunction)
               {

                  ::str::get_lines(m_strOutput, false, [&](auto& str)
                     {

                        tracefunction(e_trace_level_information, str);

                     });

               }


               //if (ecommandsystem & e_command_system_inline_log)
               //{

               //   fprintf(stdout, "%s", str.c_str());

               //   fflush(stdout);

               //}

               //strOutput += str;

               //::str().get_lines(straOutput, strOutput, "I: ", false, &sl, pfileLines);

            };

            ::CloseHandle(m_hOutRd);
            m_hOutRd = nullptr;

            ::output_debug_string("read out end");
            peventEndOut->SetEvent();


         });


      auto peventEndErr = __create_new < manual_reset_event >();


      application()->fork([this, tracefunction, peventEndErr]()
         {

            char sz[256];

            while (true)
            {

               DWORD dwRead = 0;

               if (!ReadFile(m_hErrRd, sz, 256, &dwRead, nullptr))
               {

                  break;

               }

               if (dwRead == 0)
               {

                  break;

               }

               string str(sz, dwRead);

               m_strError += str;

               if (tracefunction)
               {

                  ::str::get_lines(m_strError, false, [&](auto& str)
                     {

                        tracefunction(e_trace_level_error, str);

                     });

               }


               //if (ecommandsystem & e_command_system_inline_log)
               //{

               //   fprintf(stdout, "%s", str.c_str());

               //   fflush(stdout);

               //}

               //strOutput += str;

               //::str().get_lines(straOutput, strOutput, "I: ", false, &sl, pfileLines);

            };

            ::CloseHandle(m_hErrRd);
            m_hErrRd = nullptr;

            ::output_debug_string("read err end");
            peventEndErr->SetEvent();


         });

      DWORD dwError = 0;

      m_dwExitCode2 = 0;

      m_iExitCode = -1;

      while (true)
      {

         if (::GetExitCodeProcess(m_pi.hProcess, &m_dwExitCode2))
         {

            if (m_dwExitCode2 != STILL_ACTIVE)
            {

               m_iExitCode = m_dwExitCode2;

               break;

            }

         }
         else
         {

            dwError = ::GetLastError();

            break;

         }

         preempt(100_ms);

      }

      while (::task_get_run())
      {

         auto result = WaitForSingleObject(m_pi.hProcess, 100);

         if (result == WAIT_OBJECT_0)
         {

            break;

         }

         if (tracefunction
            && !tracefunction.m_timeTimeout.is_infinite()
            && m_timeStart.elapsed() > tracefunction.m_timeTimeout)
         {

            break;

         }

      }



      ////single_lock sl(pparticleSynchronization);

      //while (true)
      //{


      //   while (true)
      //   {

      //      DWORD dwRead = 0;

      //      if (!ReadFile(hErrRd, sz, 256, &dwRead, nullptr))
      //      {

      //         break;

      //      }

      //      if (dwRead == 0)
      //      {

      //         break;

      //      }

      //      string str(sz, dwRead);

      //      strError += str;

      //      if (tracefunction)
      //      {

      //         ::str::get_lines(strError, false, [&](auto & str)
      //            {

      //                  tracefunction(e_trace_level_error, str);

      //            });

      //      }


      //      //if (ecommandsystem & e_command_system_inline_log)
      //      //{

      //      //   fprintf(stderr, "%s", str.c_str());

      //      //   fflush(stderr);

      //      //}

      //      //strError += str;

      //      //::str().get_lines(straOutput, strError, "E: ", false, &sl, pfileLines);

      //   };



      //}

      while (true)
      {

         if (peventEndOut->_wait(100_ms) && peventEndErr->_wait(100_ms))
         {

            break;

         }

      }

      if (tracefunction)
      {

         ::str::get_lines(m_strOutput, true, [&](auto& str)
            {

               tracefunction(e_trace_level_information, str);

            });

         ::str::get_lines(m_strError, true, [&](auto& str)
            {

               tracefunction(e_trace_level_error, str);

            });

      }


      //::str().get_lines(straOutput, strOutput, "I: ", true, &sl, pfileLines);
      //::str().get_lines(straOutput, strError, "E: ", true, &sl, pfileLines);



   }


} // namespace acme_windows




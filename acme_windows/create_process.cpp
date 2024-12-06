// Created by camilo on 2024-03-07 10:48 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "create_process.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/application.h"
#include "acme/platform/node.h"
#include "acme/prototype/datetime/datetime.h"
#include "acme/prototype/string/str.h"
#include "registry.h"

///******************************************************************************\
//*       This is a part of the Microsoft Source Code Samples.
//*       Copyright 1995 - 1997 Microsoft Corporation.
//*       All rights reserved.
//*       This source code is only intended as a supplement to
//*       Microsoft Development Tools and/or WinHelp documentation.
//*       See these sources for detailed information regarding the
//*       Microsoft samples programs.
//\******************************************************************************/
//
///*++
//Copyright (c) 1997  Microsoft Corporation
//Module Name:
//    pipeex.c
//Abstract:
//    CreatePipe-like function that lets one or both handles be overlapped
//Author:
//    Dave Hart  Summer 1997
//Revision History:
//--*/
//
//#include <windows.h>
//#include <stdio.h>
//
//static volatile long PipeSerialNumber;
//
//BOOL
//APIENTRY
//MyCreatePipeEx(
//   OUT LPHANDLE lpReadPipe,
//   OUT LPHANDLE lpWritePipe,
//   IN LPSECURITY_ATTRIBUTES lpPipeAttributes,
//   IN DWORD nSize,
//   DWORD dwReadMode,
//   DWORD dwWriteMode
//)
//
///*++
//Routine Description:
//    The CreatePipeEx API is used to create an anonymous pipe I/O device.
//    Unlike CreatePipe FILE_FLAG_OVERLAPPED may be specified for one or
//    both handles.
//    Two handles to the device are created.  One handle is opened for
//    reading and the other is opened for writing.  These handles may be
//    used in subsequent calls to ReadFile and WriteFile to transmit data
//    through the pipe.
//Arguments:
//    lpReadPipe - Returns a handle to the read side of the pipe.  Data
//        may be read from the pipe by specifying this handle value in a
//        subsequent call to ReadFile.
//    lpWritePipe - Returns a handle to the write side of the pipe.  Data
//        may be written to the pipe by specifying this handle value in a
//        subsequent call to WriteFile.
//    lpPipeAttributes - An optional parameter that may be used to specify
//        the attributes of the ___new pipe.  If the parameter is not
//        specified, then the pipe is created without a security
//        descriptor, and the resulting handles are not inherited on
//        process creation.  Otherwise, the optional security attributes
//        are used on the pipe, and the inherit handles flag effects both
//        pipe handles.
//    nSize - Supplies the requested buffer size for the pipe.  This is
//        only a suggestion and is used by the operating system to
//        calculate an appropriate buffering mechanism.  A value of zero
//        indicates that the system is to choose the default buffering
//        scheme.
//Return Value:
//    TRUE - The operation was successful.
//    FALSE/NULL - The operation failed. Extended error status is available
//        using GetLastError.
//--*/
//
//{
//   HANDLE ReadPipeHandle, WritePipeHandle;
//   DWORD dwError;
//   UCHAR PipeNameBuffer[MAX_PATH];
//
//   //
//   // Only one valid OpenMode flag - FILE_FLAG_OVERLAPPED
//   //
//
//   if ((dwReadMode | dwWriteMode) & (~FILE_FLAG_OVERLAPPED)) {
//      SetLastError(ERROR_INVALID_PARAMETER);
//      return FALSE;
//   }
//
//   //
//   //  Set the default timeout to 120 seconds
//   //
//
//   if (nSize == 0) {
//      nSize = 4096;
//   }
//
//   ::string strName;
//
//   strName.formatf("\\\\.\\Pipe\\RemoteExeAnon.%08x.%08x",
//      GetCurrentProcessId(),
//      InterlockedIncrement(&PipeSerialNumber)
//   );
//
//   ::wstring wstrName(strName);
//
//   ReadPipeHandle = CreateNamedPipeW(
//      wstrName,
//      PIPE_ACCESS_INBOUND | dwReadMode,
//      PIPE_TYPE_BYTE | PIPE_WAIT,
//      1,             // Number of pipes
//      nSize,         // Out buffer size
//      nSize,         // In buffer size
//      120 * 1000,    // Timeout in ms
//      lpPipeAttributes
//   );
//
//   if (!ReadPipeHandle) {
//      return FALSE;
//   }
//
//   WritePipeHandle = CreateFileW(
//      wstrName,
//      GENERIC_WRITE,
//      0,                         // No sharing
//      lpPipeAttributes,
//      OPEN_EXISTING,
//      FILE_ATTRIBUTE_NORMAL | dwWriteMode,
//      NULL                       // Template file
//   );
//
//   if (INVALID_HANDLE_VALUE == WritePipeHandle) {
//      dwError = GetLastError();
//      CloseHandle(ReadPipeHandle);
//      SetLastError(dwError);
//      return FALSE;
//   }
//
//   *lpReadPipe = ReadPipeHandle;
//   *lpWritePipe = WritePipeHandle;
//   return(TRUE);
//}
///*
//
//BOOL WaitReadFile(HANDLE hFile, LPVOID lpBuffer, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
//{
//
//   const int BUF_SIZE = 4096;
//
//   char inBuffer[BUF_SIZE];
//   DWORD nBytesToRead = BUF_SIZE;
//   DWORD dwBytesRead = 0;
//   DWORD dwFileSize = GetFileSize(hFile, NULL);
//   OVERLAPPED stOverlapped = { 0 };
//
//   DWORD dwError = 0;
//   LPCTSTR errMsg = NULL;
//
//   BOOL bResult = FALSE;
//   BOOL bContinue = TRUE;
//
//// Set up overlapped structure happening. Other members are already 
//// initialized to zero.
////stOverlapped.hEvent = hEvent;
//
//// This is an intentionally brute-force loop to force the EOF trigger.
//// A properly designed loop for this simple file read would use the
//// GetFileSize API to regulate execution. However, the purpose here
//// is to demonstrate how to trigger the EOF error and handle it.
//
//while (bContinue)
//{
//   // Default to ending the loop.
//   bContinue = FALSE;
//
//   // Attempt an asynchronous read operation.
//   bResult = ReadFile(hFile,
//      inBuffer,
//      nBytesToRead,
//      &dwBytesRead,
//      lpOverlapped);
//
//   dwError = GetLastError();
//
//   // Check for a problem or pending operation. 
//   if (!bResult)
//   {
//      switch (dwError)
//      {
//
//      case ERROR_HANDLE_EOF:
//      {
//         printf("\nReadFile returned FALSE and EOF condition, async EOF not triggered.\n");
//         return false;
//      }
//      case ERROR_IO_PENDING:
//      {
//         BOOL bPending = TRUE;
//
//         // Loop until the I/O is complete, that is: the overlapped 
//         // happening is signaled.
//
//         while (bPending)
//         {
//            bPending = FALSE;
//
//            // Pending asynchronous I/O, do something else
//            // and re-check overlapped structure.
//            printf("\nReadFile operation is pending\n");
//
//            // Do something else then come back to check. 
//            GoDoSomethingElse();
//
//            // Check the result of the asynchronous read
//            // without waiting (forth parameter FALSE). 
//            bResult = GetOverlappedResult(hFile,
//               &stOverlapped,
//               &dwBytesRead,
//               FALSE);
//
//            if (!bResult)
//            {
//               switch (dwError = GetLastError())
//               {
//               case ERROR_HANDLE_EOF:
//               {
//                  // Handle an end of file
//                  printf("GetOverlappedResult found EOF\n");
//                  break;
//               }
//
//               case ERROR_IO_INCOMPLETE:
//               {
//                  // Operation is still pending, allow while loop
//                  // to loop again after printing a little progress.
//                  printf("GetOverlappedResult I/O Incomplete\n");
//                  bPending = TRUE;
//                  bContinue = TRUE;
//                  break;
//               }
//
//               default:
//               {
//                  // Decode any other errors codes.
//                  errMsg = ErrorMessage(dwError);
//                  _tprintf(TEXT("GetOverlappedResult failed (%d): %s\n"),
//                     dwError, errMsg);
//                  LocalFree((LPVOID)errMsg);
//               }
//               }
//            }
//            else
//            {
//               printf("ReadFile operation completed\n");
//
//               // Manual-reset happening should be reset since it is now signaled.
//               ResetEvent(stOverlapped.hEvent);
//            }
//         }
//         break;
//      }
//
//      default:
//      {
//         // Decode any other errors codes.
//         errMsg = ErrorMessage(dwError);
//         printf("ReadFile GLE unhandled (%d): %s\n", dwError, errMsg);
//         LocalFree((LPVOID)errMsg);
//         break;
//      }
//      }
//   }
//   else
//   {
//      // EOF demo did not trigger for the given file.
//      // Note that system caching may cause this condition on most files
//      // after the first read. CreateFile can be called using the
//      // FILE_FLAG_NOBUFFERING parameter but it would require reads are
//      // always aligned to the volume's sector boundary. This is beyond
//      // the scope of this example. See comments in the main() function.
//
//      printf("ReadFile completed synchronously\n");
//   }
//
//   // The following operation assumes the file is not extremely large, otherwise 
//   // logic would need to be included to adequately account for very large
//   // files and manipulate the OffsetHigh member of the OVERLAPPED structure.
//
//   stOverlapped.Offset += dwBytesRead;
//   if (stOverlapped.Offset < dwFileSize)
//      bContinue = TRUE;
//}
//
//return stOverlapped.Offset;
//}
//
//*/
//

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

      {

         DWORD dwState = PIPE_NOWAIT;

         SetNamedPipeHandleState(m_hOutRd, &dwState, nullptr, nullptr);

      }

      //m_overlappedOut.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
      //m_overlappedOut.Offset = 0;
      //m_overlappedOut.OffsetHigh = 0;

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
      //m_overlappedOut.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
      //m_overlappedOut.Offset = 0;
      //m_overlappedOut.OffsetHigh = 0;

      {

         DWORD dwState = PIPE_NOWAIT;

         SetNamedPipeHandleState(m_hErrRd, &dwState, nullptr, nullptr);

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

      {

         DWORD dwState = PIPE_NOWAIT;

         SetNamedPipeHandleState(m_hInWr, &dwState, nullptr, nullptr);

      }

   }

   //straOutput.clear();

   void create_process::prepare()
   {

      ZeroMemory(&m_si, sizeof(m_si));
      m_si.StartupInfo.cb = sizeof(m_si);


      if (m_hErrWr || m_hOutWr || m_hInRd)
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
         int c = 0;
         if (m_hErrWr)
            hList[c++] = m_hErrWr;
         if (m_hOutWr)
            hList[c++] = m_hOutWr;
         if (m_hInRd)
            hList[c++] = m_hInRd;

         auto s = sizeof(hList);

         UpdateProcThreadAttribute(
            m_pattrList,
            0,
            PROC_THREAD_ATTRIBUTE_HANDLE_LIST,
            hList,
            c * sizeof(HANDLE),
            nullptr,
            nullptr
         );
         m_si.StartupInfo.dwFlags |= STARTF_USESTDHANDLES;
         m_si.lpAttributeList = m_pattrList;

         m_si.StartupInfo.hStdError = m_hErrWr;
         m_si.StartupInfo.hStdOutput = m_hOutWr;
         m_si.StartupInfo.hStdInput = m_hInRd;
      }

      m_si.StartupInfo.dwFlags |= STARTF_USESHOWWINDOW;
      if (::is_screen_visible(m_edisplay))
      {

         m_si.StartupInfo.wShowWindow = SW_SHOWNORMAL; // Show show the console window (DOS box)

      }
      else
      {
         m_si.StartupInfo.wShowWindow = SW_HIDE; // Don't show the console window (DOS box)
      }
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
      try
      {
         auto range = str();
         range.m_erange = e_range_none;
         str1 = range.consume_quoted_value();

      }
      catch (...)
      {


      }

      ::string strCandidateFile;
      try
      {
         auto range = str();
         range.m_erange = e_range_none;
         strCandidateFile = range.consume_word();

      }
      catch (...)
      {


      }
      ::string str2;

      if (str.begins_eat("powershell://"))
      {

         auto strPowerShell = node()->_get_power_shell_path().windows_path().path();

         str1 = strPowerShell;

         str2 = "\"" + strPowerShell + "\" /c " + scopedstr;

      }
      else if (file_system()->exists(strCandidateFile))
      {
         str1 = strCandidateFile;
         str1.trim();

         str2 = scopedstr;
         str2.trim();

      }
      else if (str1.is_empty() || str1.case_insensitive_ends(".cmd"))
      {

         ::string strCmd = node()->_get_cmd_path().windows_path().path();

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

      ::wstring wstrWorkingDirectory;

      wstrWorkingDirectory = m_pathWorkingDirectory.windows_path().path();

      LPCWSTR pszWorkingDirectory = nullptr;

      if (wstrWorkingDirectory.has_character())
      {

         pszWorkingDirectory = wstrWorkingDirectory;

      }

      if (!CreateProcessW(
         (WCHAR*)wstr1.c_str(),
         (WCHAR*)wstr2.c_str(),
         NULL,
         NULL,
         TRUE,
         m_dwCreationFlags,
         NULL,
         pszWorkingDirectory,
         &m_si.StartupInfo,
         &m_pi))
      {

         DWORD dwLastError = ::GetLastError();

         printf("Create Process(2) failed with lasterror = %d\n", dwLastError);
         printf("Parameters(2): %s %s\n", str1.c_str(), str2.c_str());

         auto estatus = ::windows::last_error_status(dwLastError);

         throw ::exception(estatus);

      }
      m_timeStart.Now();
      ::CloseHandle(m_hOutWr);
      ::CloseHandle(m_hErrWr);
      ::CloseHandle(m_hInRd);
      m_hOutWr = nullptr;
      m_hErrWr = nullptr;
      m_hInRd = nullptr;

   }

//   void create_process::__read_task(enum_trace_level etracelevel, const trace_function& tracefunction, ::string* pstrOut, const void* p, ::collection::count c)
//   {
//
//      pstrOutput->append(p, c);
//
//      if (tracefunction)
//      {
//
//         ::str::get_lines(m_strOutput, false, [etracelevel, tracefunction](auto& str)
//            {
//
//               tracefunction(etracelevel, str);
//
//            });
//
//      }
//
//   }
//
//   void create_process::_read_task(enum_trace_level etracelevel, const trace_function& tracefunction, ::string* pstrOut, OVERLAPPED* poverlapped)
//   {
//
//
//      const int BUF_SIZE = 4096;
//
//      char inBuffer[BUF_SIZE];
//      DWORD nBytesToRead = BUF_SIZE;
//      DWORD dwBytesRead = 0;
//      DWORD dwFileSize = GetFileSize(hFile, NULL);
//      OVERLAPPED stOverlapped = { 0 };
//
//      DWORD dwError = 0;
//      LPCTSTR errMsg = NULL;
//
//      BOOL bResult = FALSE;
//      BOOL bContinue = TRUE;
//
//      // Set up overlapped structure happening. Other members are already 
//      // initialized to zero.
//      //stOverlapped.hEvent = hEvent;
//
//      // This is an intentionally brute-force loop to force the EOF trigger.
//      // A properly designed loop for this simple file read would use the
//      // GetFileSize API to regulate execution. However, the purpose here
//      // is to demonstrate how to trigger the EOF error and handle it.
//
//      while (bContinue)
//      {
//         // Default to ending the loop.
//         bContinue = FALSE;
//         //if (ReadFileAsync(m_hOutRd, szOut, sizeof(szOut), &dwReadOut, nullptr) && dwReadOut > 0)
//         //{
//
//
//         //}
//
//         // Attempt an asynchronous read operation.
//         bResult = ReadFile(hFile,
//            inBuffer,
//            nBytesToRead,
//            &dwBytesRead,
//            poverlapped);
//
//         // Check for a problem or pending operation. 
//         if (bResult)
//         {
//
//            __read_task(etracelevel, tracefunction, pstrOut, inBuffer, dwBytesRead);
//
//         }
//         else
//         {
//
//            dwError = GetLastError();
//
//
//            switch (dwError)
//            {
//
//            case ERROR_HANDLE_EOF:
//            {
//               printf("\nReadFile returned FALSE and EOF condition, async EOF not triggered.\n");
//               return;
//            }
//            case ERROR_IO_PENDING:
//            {
//               BOOL bPending = TRUE;
//
//               // Loop until the I/O is complete, that is: the overlapped 
//               // happening is signaled.
//
//               while (bPending)
//               {
//                  bPending = FALSE;
//
//                  // Pending asynchronous I/O, do something else
//                  // and re-check overlapped structure.
//                  //printf("\nReadFile operation is pending\n");
//
//                  // Do something else then come back to check. 
//                  //GoDoSomethingElse();
//                  //preempt(10_ms);
//
//                  // Check the result of the asynchronous read
//                  // without waiting (forth parameter FALSE). 
//                  bResult = GetOverlappedResultEx(hFile,
//                     &stOverlapped,
//                     &dwBytesRead,
//                     100,
//                     TRUE);
//
//                  if (!bResult)
//                  {
//                     switch (dwError = GetLastError())
//                     {
//                     case ERROR_HANDLE_EOF:
//                     {
//                        // Handle an end of file
//                        printf("GetOverlappedResult found EOF\n");
//                        return;
//                     }
//
//                     case ERROR_IO_INCOMPLETE:
//                     {
//                        // Operation is still pending, allow while loop
//                        // to loop again after printing a little progress.
//                        printf("GetOverlappedResult I/O Incomplete\n");
//                        bPending = TRUE;
//                        bContinue = TRUE;
//                        break;
//                     }
//
//                     default:
//                     //{
//                        // Decode any other errors codes.
//                        //errMsg = ErrorMessage(dwError);
//                        //_tprintf(TEXT("GetOverlappedResult failed (%d): %s\n"),
//                          // dwError, errMsg);
//                        //LocalFree((LPVOID)errMsg);
//                        return;
//                     }
//                  }
//                  else
//                  {
//                     printf("ReadFile operation completed\n");
//
//                     // Manual-reset happening should be reset since it is now signaled.
//                     ResetEvent(stOverlapped.hEvent);
//                  }
//               }
//               break;
//            }
//
//            default:
//            {
//               return;
//               // Decode any other errors codes.
//               //errMsg = ErrorMessage(dwError);
//               //printf("ReadFile GLE unhandled (%d): %s\n", dwError, errMsg);
//               //LocalFree((LPVOID)errMsg);
//               //break;
//            }
//         }
////         else
////         {
////            // EOF demo did not trigger for the given file.
////            // Note that system caching may cause this condition on most files
////            // after the first read. CreateFile can be called using the
////            // FILE_FLAG_NOBUFFERING parameter but it would require reads are
////            // always aligned to the volume's sector boundary. This is beyond
////            // the scope of this example. See comments in the main() function.
////
//////            printf("ReadFile completed synchronously\n");
////
////            
////
////         }
//
//         // The following operation assumes the file is not extremely large, otherwise 
//         // logic would need to be included to adequately account for very large
//         // files and manipulate the OffsetHigh member of the OVERLAPPED structure.
//
//         poverlapped->Offset += dwBytesRead;
//         //if (postOverlapped.Offset < dwFileSize)
//         //   bContinue = TRUE;
//      }
//
//   }

   void create_process::wait_process(const trace_function& tracefunction)
   {

      //auto phappeningEndOut = __create_new < manual_reset_happening >();

      //application()->fork([this, tracefunction, phappeningEndOut]()

      char szOut[4096];
      char szErr[4096];
      DWORD dwReadOut = 0;
      DWORD dwReadErr = 0;
      DWORD dwError = 0;
      bool bFinished = false;
      m_dwExitCode2 = 0;

      m_iExitCode = -1;


      while (!bFinished)
      {

         if (::GetExitCodeProcess(m_pi.hProcess, &m_dwExitCode2))
         {

            if (m_dwExitCode2 != STILL_ACTIVE)
            {

               bFinished = true;

               m_iExitCode = m_dwExitCode2;

            }

         }
         else
         {

            dwError = ::GetLastError();

            break;

         }

         do
         {



            //if (ecommandsystem & e_command_system_inline_log)
            //{

            //   fprintf(stdout, "%s", str.c_str());

            //   fflush(stdout);

            //}

            //strOutput += str;

            //::str().get_lines(straOutput, strOutput, "I: ", false, &sl, pfileLines);

            if (ReadFile(m_hOutRd, szOut, sizeof(szOut), &dwReadOut, nullptr) && dwReadOut > 0)
            {

               m_strOutput.append(szOut, dwReadOut);

               if (tracefunction)
               {

                  ::str::get_lines(m_strOutput, false, [&](auto& str, bool bCarriage)
                     {

                        tracefunction(e_trace_level_information, str, bCarriage);

                     });

               }

            }

            if (ReadFile(m_hErrRd, szErr, sizeof(szErr), &dwReadErr, nullptr) && dwReadErr > 0)
            {

               m_strError.append(szErr, dwReadErr);

               if (tracefunction)
               {

                  ::str::get_lines(m_strError, false, [&](auto& str, bool bCarriage)
                     {

                        tracefunction(e_trace_level_error, str, bCarriage);

                     });

               }

            }

         }
         while (dwReadOut > 0 || dwReadErr > 0);

         if (tracefunction
            && !tracefunction.timeout().is_infinite()
            && m_timeStart.elapsed() > tracefunction.timeout())
         {

            break;

         }

         preempt(40_ms);

      }


      ::CloseHandle(m_hOutRd);

      m_hOutRd = nullptr;

      ::CloseHandle(m_hErrRd);
      m_hErrRd = nullptr;


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

      //while (true)
      //{

      //   if (phappeningEndOut->_wait(100_ms) && phappeningEndErr->_wait(100_ms))
      //   {

      //      break;

      //   }

      //}

      if (tracefunction)
      {

         ::str::get_lines(m_strOutput, true, [&](auto& str, bool bCarriage)
            {

               tracefunction(e_trace_level_information, str, bCarriage);

            });

         ::str::get_lines(m_strError, true, [&](auto& str, bool bCarriage)
            {

               tracefunction(e_trace_level_error, str, bCarriage);

            });

      }


      //::str().get_lines(straOutput, strOutput, "I: ", true, &sl, pfileLines);
      //::str().get_lines(straOutput, strError, "E: ", true, &sl, pfileLines);

      if(m_dwExitCode2 == STILL_ACTIVE)
      {

         auto elapsed = m_timeStart.elapsed();

         if (tracefunction
            && !tracefunction.timeout().is_infinite()
            && elapsed > tracefunction.timeout())
         {

            ::string strElapsed = datetime()->elapsed_time_text(elapsed);

            ::string strMessage;

            strMessage = "create_process::wait_process failed by timeout ";

            strMessage = strElapsed;

            throw ::exception(error_wait_timeout, strMessage);

         }


      }

   }


} // namespace acme_windows




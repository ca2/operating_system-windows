//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "subsystem/platform/CommandLineArguments.h"
#include "node/File.h"
#include "node/OperatingSystem.h"
#include "node/Shell.h"
#include "node/WTS.h"
#include "node/PipeServer.h"
#include <wincrypt.h>
#include <shellapi.h>
#pragma comment (lib, "Crypt32.lib")




namespace subsystem_windows
{

   ::subsystem_windows::subsystem * subsystem::s_p = nullptr;

subsystem::subsystem()
   {



   }


   subsystem::~subsystem()
   {


   }

    ::subsystem_windows::WTS &subsystem::WTS()
   {

       if (!m_pwts)
       {

           construct_newø(m_pwts);

       }

       return *m_pwts;


   }


    PipeServer * subsystem::pipe_server()
   {

       if (!m_ppipeserver)
       {

           construct_newø(m_ppipeserver);

       }

       return m_ppipeserver;


   }


       void subsystem::_parse_windows_command_line_arguments(
      ::subsystem::CommandLineArguments *pcommandlinearguments, const scoped_string &scopedstrCommandLineInWindowsFormat)
   {
      ::string strstorage(scopedstrCommandLineInWindowsFormat);
      ::wstring uniCmdLine(strstorage);
      size_t cmdLen = uniCmdLine.length();
      if (cmdLen > 0)
      {
         int nArgs;
         LPWSTR *argList = CommandLineToArgvW(uniCmdLine, &nArgs);
         if (argList == 0)
         {
            throw ::subsystem::Exception("Invalid command line");
         }
         for (int i = 0; i < nArgs; i++)
         {
            ::wstring uniArg(argList[i]);
            ::string arg;
            arg = uniArg;
            if (arg.length() > 0)
            {
               pcommandlinearguments->m_args.add(arg);
            }
         }

         LocalFree(argList);
      }
   }


   pointer<::subsystem::CommandLineArguments> subsystem::getCurrentProcessCommandLineArguments()
   {

      ::string strCommandLine;

      strCommandLine = ::GetCommandLineW();

      auto pcommandlinearguments = getCommandLineArguments(strCommandLine);

      return pcommandlinearguments;

   }


   pointer<::subsystem::CommandLineArguments> subsystem::getCommandLineArguments(const scoped_string &scopedstrCommandLineInWindowsFormat)
   {

       auto pcommandlinearguments = create_newø<::subsystem::CommandLineArguments>();

       ::string strCommandLine;

       strCommandLine = scopedstrCommandLineInWindowsFormat;

       _parse_windows_command_line_arguments(pcommandlinearguments, strCommandLine);

       return pcommandlinearguments;

   }


   bool subsystem::EncryptData(const ::string& input, ::memory & output)
   {

   DATA_BLOB inBlob;
   DATA_BLOB outBlob;

   inBlob.pbData = (unsigned char*)input.data();
   inBlob.cbData = (DWORD)input.size();

   if (!CryptProtectData(&inBlob, nullptr, nullptr, nullptr, nullptr, 0, &outBlob))
      return false;

   output.assign(outBlob.pbData, outBlob.cbData);
   LocalFree(outBlob.pbData);
   return true;
}

   bool subsystem::DecryptData(const memory & input, ::string& output)
{
   DATA_BLOB inBlob;
   DATA_BLOB outBlob;

   inBlob.pbData = (unsigned char*)input.data();
   inBlob.cbData = (DWORD)input.size();

   if (!CryptUnprotectData(&inBlob, nullptr, nullptr, nullptr, nullptr, 0, &outBlob))
      return false;

   output.assign((char*)outBlob.pbData, outBlob.cbData);
   LocalFree(outBlob.pbData);
   return true;
}


   //int subsystem::get_last_socket_error()
   //{

   //   return WSAGetLastError();

   //}


   //string subsystem::get_socket_error_message_text(int iError)
   //{

   //   if (iError <= 0)
   //   {

   //      return {};

   //   }

   //   LPWSTR buffer = nullptr;

   //   DWORD size = FormatMessageW(
   //       FORMAT_MESSAGE_FROM_SYSTEM |
   //       FORMAT_MESSAGE_ALLOCATE_BUFFER |
   //       FORMAT_MESSAGE_IGNORE_INSERTS,
   //       nullptr,
   //       iError,
   //       MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
   //       (LPWSTR)&buffer,
   //       0,
   //       nullptr
   //   );

   //   ::wstring wstr;

   //   if (size && buffer)
   //   {

   //      wstr.assign(buffer, size);

   //   }

   //   LocalFree(buffer);  // always safe (even if buffer == nullptr)

   //   return wstr;

   //}

      pointer<::subsystem::FileInterface> subsystem::fileFrom_HANDLE(void *pHANDLE)
{

   auto pfile = create_newø<::subsystem_windows::File>();

   pfile->m_handle = (HANDLE)pHANDLE;

   return pfile;
}


   memsize subsystem::getCurrentMemoryUsage()
   {
   
      if (!OperatingSystem().isVistaOrLater())
      {
      
         return 0;

      }

      PROCESS_MEMORY_COUNTERS pmc;

      GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));

      return pmc.WorkingSetSize;

    }


   void subsystem::toString(::string & str, const ::earth::time & time)
   {

      auto systemTime = as_SYSTEMTIME(time);

      toLocal_SYSTEMTIME(systemTime);

      const size_t dateStringMaxLength = 255;

      TCHAR dateString[dateStringMaxLength + 1];

      if (GetDateFormat(LOCALE_USER_DEFAULT, DATE_SHORTDATE, &systemTime, 0, dateString, dateStringMaxLength) == 0)
      {
         // TODO: Process this error.
      }

      str = dateString;
      str += ' ';

      const size_t timeStringMaxLength = 255;

      TCHAR timeString[timeStringMaxLength + 1];

      if (GetTimeFormat(LOCALE_USER_DEFAULT, 0, &systemTime, 0, timeString, timeStringMaxLength) == 0)
      {
         // TODO: Process this error.
      }

      str += timeString;

   }


}//namespace subsystem_windows



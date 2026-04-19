//
// Created by camilo on 2026-04-05 03:04 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "subsystem/CommandLineArguments.h"
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

    WTS* subsystem::wts()
   {

       if (!m_pwts)
       {

           construct_newø(m_pwts);

       }

       return m_pwts;


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


    void subsystem::initializeCommandLineArguments(::subsystem::CommandLineArguments* pcommandlinearguments)
    {


       ::string strCommandLine;

       strCommandLine = ::GetCommandLineW();

      _parse_windows_command_line_arguments(pcommandlinearguments,     strCommandLine);


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

}//namespace subsystem_windows



//
// Created by camilo on 2026-04-05 20:14 <3ThomasBorregaardSørensen!!
//


// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "subsystem_bsd_sockets/subsystem.h"
#include "subsystem_windows/_common_header.h"


namespace subsystem_windows
{


   class CLASS_DECL_SUBSYSTEM_WINDOWS subsystem :
      virtual public ::subsystem_bsd_sockets::subsystem
   {
   public:


      static ::subsystem_windows::subsystem *            s_p;
      // ::pointer < ::subsystem::string_table >     m_pstringtable;
      // ::pointer < ::subsystem::resource_loader >     m_presourceloader;
      // ::pointer < ::subsystem::Registry >     m_pregistry;
      // ::pointer < ::subsystem::Shell >     m_pshell;
       ::pointer < PipeServer > m_ppipeserver;
      static critical_section s_criticalsectionResolveIp4;

       ::pointer<::subsystem_windows::WTS> m_pwts;

      subsystem();
      ~subsystem() override;

      //
      // virtual ::subsystem::string_table * string_table();
      // virtual ::subsystem::resource_loader* resource_loader();
      // virtual ::subsystem::Registry* registry();
      virtual ::subsystem_windows::WTS & WTS();
      virtual PipeServer * pipe_server();

             virtual void _parse_windows_command_line_arguments(::subsystem::CommandLineArguments *pcommandlinearguments,
                                                         const scoped_string &scopedstrCommandLineInWindowsFormat);

//         void initializeCommandLineArguments(::subsystem::CommandLineArguments *pcommandlinearguments,
//                                                 const scoped_string &scopedstrCommandLineInWindowsFormat) override;

      virtual pointer<::subsystem::CommandLineArguments>
         getCurrentProcessCommandLineArguments() override;

      virtual pointer<::subsystem::CommandLineArguments>
      getCommandLineArguments(const ::scoped_string &scopedstrCommandLine) override;

      ::pointer < ::subsystem::SecurityIdentifier > createSidFromString(const ::scoped_string & scopedstr) override;

      bool EncryptData(const ::string& input, ::memory & output) override;
      bool DecryptData(const memory & input, ::string& output) override;

      pointer<::subsystem::FileInterface> fileFrom_HANDLE(void *pHANDLE) override;


      virtual void toString(::string &str, const ::earth::time &time);

      memsize getCurrentMemoryUsage() override;



   };



} // namespace subsystem_windows



inline ::subsystem_windows::subsystem & WindowsSubsystem()
{

   if (!::subsystem::subsystem::s_p)
   {

      MainSubsystem();

   }

   return *::subsystem_windows::subsystem::s_p;

}


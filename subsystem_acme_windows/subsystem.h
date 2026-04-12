//
// Created by camilo on 2026-04-05 20:14 <3ThomasBorregaardSørensen!!
//


// Offloading apex(TBS)::app_core from deep stack stuff into acme(CSTBS) ::system 2022-02-22 by camilo at 07:19 <3ThomasBorregaardSorensen!!
#pragma once


#include "subsystem_acme/subsystem.h"
#include "subsystem_win32/_common_header.h"


namespace subsystem_win32
{


   class CLASS_DECL_SUBSYSTEM_WIN32 subsystem :
      virtual public ::subsystem_sockets_bsd::subsystem
   {
   public:


      static ::subsystem_win32::subsystem *            s_p;
      // ::pointer < ::subsystem::string_table >     m_pstringtable;
      // ::pointer < ::subsystem::resource_loader >     m_presourceloader;
      // ::pointer < ::subsystem::Registry >     m_pregistry;
      // ::pointer < ::subsystem::Shell >     m_pshell;
       ::pointer < PipeServer > m_ppipeserver;
      static critical_section s_criticalsectionResolveIp4;

       ::pointer < WTS > m_pwts;

      subsystem();
      ~subsystem() override;

      //
      // virtual ::subsystem::string_table * string_table();
      // virtual ::subsystem::resource_loader* resource_loader();
      // virtual ::subsystem::Registry* registry();
      virtual WTS * wts();
      virtual PipeServer * pipe_server();

      ::pointer < ::subsystem::SecurityIdentifier > createSidFromString(const ::scoped_string & scopedstr) override;

      bool EncryptData(const ::string& input, ::memory & output) override;
      bool DecryptData(const memory & input, ::string& output) override;

      int get_last_socket_error() override;

      ::string get_socket_error_message_text(int iError) override;

      ::pointer < ::subsystem::SocketAddressIPv4Interface > resolve_ip4_address(const ::scoped_string & scopedstrHost, unsigned short port) override;


   };



} // namespace subsystem_win32



inline ::subsystem_win32::subsystem * windows_subsystem()
{

   return ::subsystem_win32::subsystem::s_p;

}


#pragma once

/*
Module : IPENUM.H
Purpose: Interface for an apex API class wrapper for IP address enumeration
Created: PJN / 21-04-1998
History: None

Copyright (ca) 1998 by PJ Naughter.


*/


#include "apex/networking/ip_enum.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS ip_enum :
      virtual public ::networking::ip_enum
   {
   public:


      //__creatable_from_base(ip_enum, ::net::ip_enum);


      bool     m_bWinsockInitialized;


      ip_enum();
      virtual ~ip_enum();


      //      virtual ::count enumerate(ip_array & ipa);
      virtual ::count enumerate(pointer_array < ::networking::address > & ipa) override;

   };


} // namespace apex_windows




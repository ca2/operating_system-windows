// created by Camilo 2021-01-31 05:26 BRT <3CamiloSasukeThomasBorregaardSoerensen
// From interprocess_communcation by camilo on 2022-10-11 15:33 <3ThomasBorregaardSorensen!!
#pragma once


#include "apex/interprocess/base.h"
#include "acme/_operating_system.h"


namespace apex_windows
{


   class CLASS_DECL_APEX_WINDOWS interprocess_base :
      virtual public interprocess::base
   {
   public:



      HWND              m_hwnd;
      string            m_strBaseChannel;


      interprocess_base();
      ~interprocess_base() override;


      HWND get_hwnd() const { return (HWND) m_hwnd; }
      void set_hwnd(HWND hwnd) { m_hwnd = hwnd; }


   };


} // namespace apex_windows




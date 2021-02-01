// created by Camilo 2021-01-31 06:24 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_ACME monitor :
      virtual public ::windowing::monitor
   {
   public:


      HMONITOR          m_hmonitor;


      monitor(HMONITOR hmonitor);
      virtual ~monitor();


      virtual ::e_status update_cache() override;


   };


} // namespace windowing_win32



// created by Camilo 2021-02-04 00:58 BRT CamiloSasuke<3ThomasBorregaardSoerensen
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 keyboard :
      virtual public ::windowing::keyboard
   {
   public:


      //__creatable_from_base(keyboard, ::windowing::keyboard);


      keyboard();
      ~keyboard() override;


   };


} // namespace windowing_win32






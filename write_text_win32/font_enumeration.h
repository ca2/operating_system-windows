#pragma once


namespace write_text_win32
{


   // Windows GDI

   class CLASS_DECL_WRITE_TEXT_WIN32 font_enumeration :
      virtual public ::write_text::font_enumeration
   {
   public:


      HDC                                    m_hdc;
      wstring                                m_wstrTopicFaceName;


      font_enumeration();
      ~font_enumeration() override;


      ::e_status on_enumerate_fonts() override;


      virtual void enumerate_character_set(::write_text::font_enumeration_item * pitem);


      static BOOL CALLBACK callback(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 FontType, LPVOID point_i32);


      static BOOL CALLBACK callback_character_set(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 FontType, LPVOID point_i32);


   };


} // namespace write_text_win32




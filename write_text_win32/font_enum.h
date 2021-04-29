#pragma once


namespace write_text_win32
{


   class CLASS_DECL_WRITE_TEXT_WIN32 wingdi_font_enum
   {
   public:


      HDC                                    m_hdc;
      ::write_text::font_enum_item_array &   m_itema;
      bool                                   m_bRaster;
      bool                                   m_bTrueType;
      bool                                   m_bOther;
      wstring                                m_wstrTopicFaceName;
      int_array                              m_iaCharSet;


      wingdi_font_enum(::write_text::font_enum_item_array & itema, bool bRaster, bool bTrueType, bool bOther);



      ~wingdi_font_enum();


      void enumerate();


      void enum_cs(::write_text::font_enum_item * pitem);


      static BOOL CALLBACK callback(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 FontType, LPVOID point_i32);


      static BOOL CALLBACK callback_cs(LPLOGFONTW plf, LPNEWTEXTMETRICW lpntm, ::u32 FontType, LPVOID point_i32);


   };


} // namespace write_text_win32




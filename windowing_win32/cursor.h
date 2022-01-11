// created by Camilo CamiloSasuke<3ThomasBorregaardSoerensen
// recreated by Camilo 2021-02-03 22:01 BRT
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 cursor :
      virtual public ::windowing::cursor
   {
   public:


      cursor(HCURSOR hcursor = nullptr);
      virtual ~cursor();


      void _create_os_cursor() override;

      inline HCURSOR get_hcursor() const { return (HCURSOR)get_os_data(); }

      inline void set_hcursor(HCURSOR hcursor) { set_os_data(hcursor); }

      virtual void _load_default_cursor(enum_cursor ecursor);

      virtual void _create_from_image(const ::image* pimage, ::i32 xHotspot, ::i32 yHotspot);


   };



} // namespace windowing






// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Sørensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:43
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_AURA icon :
      virtual public ::windowing::icon
   {
   public:


      HICON m_hicon;

      icon();
      virtual ~icon();

      virtual iptr get_os_data() const;
      
      virtual bool load_file(string strPath) override;


      virtual image * get_image(const concrete < ::size_i32 > & size);

      
   };



} // namespace windowing




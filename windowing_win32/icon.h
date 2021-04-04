// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Sørensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:43
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 icon :
      virtual public ::windowing::icon
   {
   public:


      map < ::size_i32, HICON >    m_iconmap;


      icon();
      virtual ~icon();

      virtual void * get_os_data(const ::size_i32 & size) const;
      
      virtual ::e_status load_file(string strPath) override;

      virtual bool add_icon(HICON hicon);

      virtual void get_sizes(array < concrete < ::size_i32 > > & a) override;

      virtual image_pointer create_image(const concrete < ::size_i32 > & size);


      void _erase_all();

      
   };



} // namespace windowing




// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen - Honoring Thomas Borregaard Sørensen My ONLY GOD
// recreated by Camilo 2021-02-01 16:43
#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 icon :
      virtual public ::windowing::icon
   {
   public:


      map < ::size_i32, HICON >              m_iconmap;

      ::file::path                           m_pathProcessed;

      map < ::size_i32, image_pointer >      m_imagemap;

      
      icon();
      ~icon() override;


      virtual void * get_os_data(const ::size_i32 & size) const;
      
      ::e_status load_file(const string & strPath) override;

      ::e_status load_app_tray_icon(const string& strApp) override;

      virtual bool add_icon(HICON hicon);

      void get_sizes(array < concrete < ::size_i32 > > & a) override;

      image_pointer get_image(const concrete < ::size_i32 > & size) override;

      virtual image_pointer _create_image(const concrete < ::size_i32 >& size);


      void _erase_all();

      
   };



} // namespace windowing




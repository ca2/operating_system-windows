#pragma once


#include <shlobj.h>
#include <Shellapi.h>
#include <CommonControls.h>


#include "aura/user/shell.h"


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 shell :
      virtual public ::user::shell
      //, virtual public ::user::message_queue_listener
   {
   public:


      comptr < IMalloc >                              m_pmalloc;
      comptr < IShellFolder >                         m_pfolderDesktop;
      comptr < IImageList >                           m_pilSmall;
      comptr < IImageList >                           m_pilLarge;
      comptr < IImageList >                           m_pilExtraLarge;
      comptr < IImageList >                           m_pilJumbo;
      //__composite(::user::message_queue)              m_pmessagequeue;

      comptr<IKnownFolderManager> m_knownfoldermanager;

      shell();
      ~shell() override;


      ::e_status initialize(::object * pobject) override;


      ::e_status run() override;


      i32 _get_file_image(const image_key & key) override;


      i32 get_file_image(image_key & key, const itemidlist & pidlAbsolute, const unichar * pcszExtra, const ::color::color & colorBackground);

      i32 get_image_by_file_extension(image_key & key);


      i32 add_system_icon(int iIcon, const ::color::color & colorBackground, int iImage);
      //i32 add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, ::color::color crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);
      i32 add_system_icon(int iSize, int iIcon, const ::color::color & colorBackground, int iImage);


      i32 get_file_image(image_key key, const unichar * pcszExtra, ::color::color crBk);




      ///         virtual i32 get_extension_image(const ::string & strExtension, e_file_attribute eattribute, e_icon eicon, ::color::color crBk = 0) override;

      i32 add_icon(int iSize, HICON hicon, const ::color::color & colocrBackground, int iImage);

      i32 set_icon(int iImage, const ::file::path & path, const ::color::color & colocrBackground) override;

      i32 add_system_icon(int iSize, IImageList * plist, int iIcon, const ::color::color & colorBackground, int iImage);



      ::user::shell::e_folder get_folder_type(::object * pobject, const ::wstring & wstrPath) override;

      ::user::shell::e_folder get_folder_type(::object * pobject, const ::string & strPath) override;



      virtual void set_image_ico(string strIconLocation, i32 & iImage, ::color::color crBk);
      virtual void set_image_resource(string strIconLocation, i32 & iImage, const image_key & imagekey, ::color::color crBk);

      ::e_status destroy() override;

      //int shell::add_hover_image(int iSize, int iImage, ::color::color crBk)

   };


} // namespace windowing_win32




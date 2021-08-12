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


      //__composite(::user::message_queue)              m_pmessagequeue;

      //comptr<IThumbnailHandlerFactory> m_thumbnailhandlerfactory;

      struct _get_file_image_ :
         public ::user::shell::_get_file_image_
      {

         comptr < IMalloc >               m_pmalloc;
         comptr < IShellFolder >          m_pfolderDesktop;
         comptr < IImageList >            m_pilSmall;
         comptr < IImageList >            m_pilLarge;
         comptr < IImageList >            m_pilExtraLarge;
         comptr < IImageList >            m_pilJumbo;
         comptr<IKnownFolderManager>      m_knownfoldermanager;
         comptr < IShellFolder >          m_pshellfolder;
         itemidlist                       m_itemidlist;
         itemidlist                       m_itemidlistFolder;
         itemidlist                       m_itemidlistChild;
         wstring                          m_wstrExtra;

      };


      shell();
      ~shell() override;


      ::user::shell::_get_file_image_ * new_get_file_image() override;


      ::e_status initialize(::object * pobject) override;


      ::e_status run() override;


      void _get_file_image(::user::shell::_get_file_image_ & getfileimage) override;
      void _get_file_image(_get_file_image_ & getfileimage);


      bool defer_set_thumbnail(::user::shell::_get_file_image_ & getfileimage) override;

      bool _defer_set_thumbnail_IThumbnailProvider(_get_file_image_ & getfileimage);

      void _internal_get_file_image(_get_file_image_ & getfileimage);

      //i32 get_image_by_file_extension(image_key & key);

      void get_image_by_file_extension(_get_file_image_ & getfileimage);


      void add_system_icon(int iIcon, _get_file_image_ & getfileimage);
      //i32 add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, ::color::color crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);
      void add_system_icon(int iSize, int iIcon, _get_file_image_ & getfileimage);


      //i32 get_file_image(image_key key, const unichar * pcszExtra, ::color::color crBk);





      ///         virtual i32 get_extension_image(const ::string & strExtension, e_file_attribute eattribute, e_icon eicon, ::color::color crBk = 0) override;

      void add_icon(int iSize, HICON hicon, _get_file_image_ & getfileimage);

      void set_icon(const ::file::path & path, ::user::shell::_get_file_image_ & getfileimageParam);

      void add_system_icon(int iSize, IImageList * plist, int iIcon, _get_file_image_ & getfileimage);



      ::user::shell::enum_folder get_folder_type(::object * pobject, const ::wstring & wstrPath) override;

      ::user::shell::enum_folder get_folder_type(::object * pobject, const ::string & strPath) override;



      virtual void set_image_ico(string strIconLocation, _get_file_image_ & getfileimage);
      virtual void set_image_resource(string strIconLocation, _get_file_image_ & getfileimage);

      ::e_status destroy() override;

      //int shell::add_hover_image(int iSize, int iImage, ::color::color crBk)

   };


} // namespace windowing_win32




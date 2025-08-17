// Created by camilo on 2023-03-14 01:51 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "file_link.h"
#include "node.h"
#include "path_system.h"
//#include "os_context.h"
#include "acme/platform/system.h"
//#include "apex/platform/context.h//"
#include "acme/operating_system/windows_common/com/hresult_exception.h"
#include "acme_windows/itemidlist.h"


#include "acme/_operating_system.h"


//#include <shobjidl.h>
#include <ShellApi.h>


namespace acme_windows
{


   file_link::file_link()
   {


   }


   file_link::~file_link()
   {


   }


   ::pointer < ::file::link > file_link::create_clean_new() const
   {

      return ((::acme_windows::file_link *)this)->øcreate_new < ::acme_windows::file_link >();

   }


   void file_link::open(const ::file::path & path, ::file::e_link elink)
   {

      clear();

      m_path = path;

      ASSERT(m_path.case_insensitive_ends(".lnk"));

      if (m_path.contains("0318") && m_path.contains("removal"))
      {

         output_debug_string("app.removal.tool link?!");

      }

      auto windowspath = m_path.windows_path();

      SHFILEINFOW info{};

      node()->defer_co_initialize_ex(false);

      DWORD_PTR dw = 0;

      auto pitemidlist = m_path.m_pparticleOsPath.cast < ::itemidlist>();

      if (pitemidlist)
      {

         dw = SHGetFileInfoW((const wchar_t *)pitemidlist->m_pidl, 0, &info, sizeof(info), SHGFI_ATTRIBUTES | SHGFI_PIDL);

      }
      else
      {

         dw = SHGetFileInfoW(windowspath.path(), 0, &info, sizeof(info), SHGFI_ATTRIBUTES);

      }

      if (dw == 0 || !(info.dwAttributes & SFGAO_LINK))
      {

         m_elink.clear();

         return;

      }

      ::pointer < ::acme_windows::path_system > pacmepath;

      pacmepath = path_system();

      m_pshelllink = pacmepath->_get_IShellLinkW(m_path);

      if (!m_pshelllink)
      {

         return;

      }

      if (elink & ::file::e_link_target)
      {

         if (pitemidlist)
         {

            HRESULT hresultGetIDList = m_pshelllink->GetIDList(&pitemidlist->m_pidl);

            if (FAILED(hresultGetIDList))
            {

               informationf("Failed to get ID Link %s", path.c_str());

            }

         }

         wstring wstr;

         auto pwsz = wstr.get_buffer(MAX_PATH * 8);

         if (SUCCEEDED(m_pshelllink->GetPath(pwsz, MAX_PATH * 8, nullptr, 0)))
         {

            wstr.release_buffer();

            m_pathTarget = wstr;

            m_elink |= ::file::e_link_target;

         }

      }

      if (elink & ::file::e_link_folder)
      {

         wstring wstr;

         auto pwsz = wstr.get_buffer(MAX_PATH * 8);

         if (SUCCEEDED(m_pshelllink->GetWorkingDirectory(pwsz, MAX_PATH * 8)))
         {

            wstr.release_buffer();

            m_pathFolder = wstr;

            m_elink |= ::file::e_link_folder;

         }

      }

      if (elink & ::file::e_link_arguments)
      {

         wstring wstr;

         auto pwsz = wstr.get_buffer(MAX_PATH * 8);

         if (SUCCEEDED(m_pshelllink->GetArguments(pwsz, MAX_PATH * 8)))
         {

            wstr.release_buffer();

            m_strArguments = wstr;

            m_elink |= ::file::e_link_arguments;

         }

      }

      if (elink & ::file::e_link_icon)
      {

         wstring wstr;

         auto pwsz = wstr.get_buffer(MAX_PATH * 8);

         int iIcon = 0;

         if (SUCCEEDED(m_pshelllink->GetIconLocation(pwsz, MAX_PATH * 8, &iIcon)))
         {

            wstr.release_buffer();

            m_pathIcon = wstr;

            m_iIcon = iIcon;

            m_elink |= ::file::e_link_icon;

         }

      }

   }


   ::file::e_link file_link::write(const ::file::path & pathWriteAs)
   {

      ::file::e_link elinkWritten = ::file::e_link_none;

      ::pointer < ::acme_windows::path_system > pacmepath;

      pacmepath = path_system();

      //auto pshelllink = poscontext->_get_IShellLinkW(m_path);

      if (!m_pshelllink)
      {

         throw ::exception(error_failed);

      }

      if (m_elink & ::file::e_link_target)
      {

         auto windowspath = m_pathTarget.windows_path();

         HRESULT hresult = m_pshelllink->SetPath(windowspath.path());

         if (SUCCEEDED(hresult))
         {

            elinkWritten |= ::file::e_link_target;

         }

      }

      if (m_elink & ::file::e_link_folder)
      {

         auto windowspath = m_pathFolder.windows_path();

         HRESULT hresult = m_pshelllink->SetWorkingDirectory(windowspath.path());

         if (SUCCEEDED(hresult))
         {

            elinkWritten |= ::file::e_link_folder;

         }

      }

      if (m_elink & ::file::e_link_icon)
      {

         auto windowspath = m_pathIcon.windows_path();

         if (windowspath.is_empty())
         {

            HRESULT hresult = m_pshelllink->SetIconLocation(nullptr, 0);

            if (SUCCEEDED(hresult))
            {
            
               elinkWritten |= ::file::e_link_icon;

            }

         }
         else
         {

            HRESULT hresult = m_pshelllink->SetIconLocation(windowspath.path(), m_iIcon);

            if (SUCCEEDED(hresult))
            {

               elinkWritten |= ::file::e_link_icon;

            }

         }

      }

      comptr < IPersistFile > ppersistfile;

      m_pshelllink.as(ppersistfile);

      if (!ppersistfile)
      {

         throw ::exception(error_no_interface);

      }

      if (pathWriteAs.has_character())
      {

         m_path = pathWriteAs;

      }

      auto windowspath = m_path.windows_path();

      ppersistfile->Save(windowspath.extended_path(), TRUE);

      return elinkWritten;

   }


} // namespace acme_windows




// Created by camilo on 2023-03-14 01:51 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/filesystem/filesystem/link.h"


#include "acme/_operating_system.h"


#include "acme_windows_common/comptr.h"


#include <shobjidl_core.h>


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS file_link :
      virtual public ::file::link
   {
   public:


      comptr < IShellLinkW >        m_pshelllink;


      file_link();
      ~file_link() override;


      ::pointer < ::file::link > create_clean_new() const override;


      void open(const ::file::path & path, ::file::e_link elink) override;

      ::file::e_link write(const ::file::path & pathWriteAs = "") override;


   };


} // namespace acme_windows




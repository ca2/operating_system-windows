#pragma once


#include "acme/filesystem/file/memory_map.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS file_memory_map :
      virtual public ::file::memory_map
   {
   public:


      //__creatable_from_base(file_memory_map, ::file::memory_map);


      ::windows::file_instance   m_fileinstance;
      HANDLE                     m_hfilemap;


      file_memory_map();
      ~file_memory_map() override;


      bool open();
      bool close();

      bool is_mapped();


   };


} // namespace acme_windows




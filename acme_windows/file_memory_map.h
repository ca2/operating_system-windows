#pragma once


namespace windows
{


   class CLASS_DECL_ACME_WINDOWS file_memory_map :
      virtual public ::file::memory_map
   {
   public:


      __creatable_from_library(file_memory_map, ::file::memory_map, "acme_windows");


      HANDLE                     m_hfile;
      HANDLE                     m_hfilemap;


      file_memory_map();
      ~file_memory_map() override;


      bool open();
      bool close();

      bool is_mapped();


   };


} // namespace file




#pragma once


namespace cross_windows
{


   class CLASS_DECL_ACME_WINDOWS file_memory_map :
      virtual public ::file::memory_map
   {
   public:

      int                        m_iFile;


      file_memory_map();
      file_memory_map(const ::scoped_string & scopedstr, bool bRead, bool bWrite, bool bCreate, memsize size);
      virtual ~file_memory_map();


      void construct();

      bool open();
      bool open(const ::scoped_string & scopedstr, bool bRead, bool bWrite, bool bCreate, memsize size);
      bool close();

      void * get_data();

      bool is_mapped();

      inline string get_name();
      string get_path();

   };




   inline string memory_map::get_name()
   {

      return m_strName;

   }


   inline void * memory_map::get_data()
   {

      return m_pdata;

   }


} // namespace file




#pragma once


namespace backup
{



   class CLASS_DECL_CA2_BACKUP backup : 
      public ::production::production 
   {
   public:



      backup(::particle * pparticle);
      virtual ~backup();

      virtual void     run() override;

      bool hotcopy_repos(const ::scoped_string & scopedstr);
      bool compress_repos(const ::scoped_string & scopedstr);

      bool all_db_dump();
      bool db_copy();

      string get_new_repos_local_path(const ::scoped_string & scopedstr);
      string get_new_db_local_path(const ::scoped_string & scopedstr);




   };


} // namespace backup




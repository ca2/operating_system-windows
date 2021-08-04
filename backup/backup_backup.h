#pragma once


namespace backup
{



   class CLASS_DECL_CA2_BACKUP backup : 
      public ::production::production 
   {
   public:



      backup(::object * pobject);
      virtual ~backup();

      virtual ::e_status     run() override;

      bool hotcopy_repos(const ::string & psz);
      bool compress_repos(const ::string & psz);

      bool all_db_dump();
      bool db_copy();

      string get_new_repos_local_path(const ::string & psz);
      string get_new_db_local_path(const ::string & psz);




   };


} // namespace backup




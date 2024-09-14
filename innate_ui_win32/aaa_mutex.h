#pragma once


namespace windows
{


   class CLASS_DECL_ACME_WINDOWS mutex :
      virtual public ::mutex
   {
   public:


      HANDLE               m_hsync;
      bool                 m_bAlreadyExists;


      mutex(enum_create_new ecreatenew, bool bInitiallyOwn, const ::string & lpszName, sync_options * psyncoptions = nullptr);
      mutex(enum_create_new ecreatenew = e_create_new, bool bInitiallyOwn = false);
      virtual ~mutex();




      using synchronization_object::unlock;
      virtual bool unlock();


      bool already_exists();


      static ::mutex open_mutex(const ::string & lpszName) { return ::open_mutex(lpszName); }


   };


} // namespace windows


CLASS_DECL_ACME_WINDOWS void wait_until_mutex_does_not_exist(const ::string & lpszName);



CLASS_DECL_ACME_WINDOWS::mutex * get_ui_destroyed_mutex();







namespace install
{


   class CLASS_DECL_ACME_WINDOWS ::mutex :
      public ::mutex
   {
   public:

      // null_dacl_sync_options
      ::mutex(string strPlatform, string strSuffix = "");

   };


   class CLASS_DECL_ACME_WINDOWS admin_mutex :
      public ::mutex
   {
   public:

      // null_dacl_sync_options
      admin_mutex(string strPlatform, string strSuffix = "");

   };




} // namespace install






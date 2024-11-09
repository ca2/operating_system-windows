#pragma once


namespace acme_windows
{


   /// This class represents happenings for file changes
   class CLASS_DECL_ACME_WINDOWS file_change_event :
      virtual public synchronization_object
   {
   public:

      /// enum describing the possible filters
      enum filter
      {
         change_file_name = FILE_NOTIFY_CHANGE_FILE_NAME,
         change_dir_name = FILE_NOTIFY_CHANGE_DIR_NAME,
         change_attributes = FILE_NOTIFY_CHANGE_ATTRIBUTES,
         change_size = FILE_NOTIFY_CHANGE_SIZE,
         change_last_write = FILE_NOTIFY_CHANGE_LAST_WRITE,
         change_security = FILE_NOTIFY_CHANGE_SECURITY
      };

      ///  \brief		constructor with passed path to file
      ///  \lparam		path the file to watch
      ///  \lparam		watchsubtree if true, the function monitors the directory tree
      ///				rooted at the specified directory, if it is false,
      ///				it monitors only the specified directory
      ///  \lparam		filter filter conditions that satisfy a machine notification wait
      ///				can take values described by enum filter
      file_change_event(::matter * pobject, const ::string & path, bool watchsubtree, unsigned int filter);

      ///  \brief		destructor
      ~file_change_event();


      virtual bool lock(const class time & timeTimeout = time::infinite());

      using synchronization_object::unlock;
      virtual bool unlock();


      ///  \brief		waits for an file notification forever
      virtual synchronization_result wait();

      ///  \brief		waits for an file notification for a specified time
      ///  \lparam		time time period to wait for an file notification
      ///  \return	waiting action result as synchronization_result
      virtual synchronization_result wait(const class time & time);

      ///  \brief		requests that the operating system signal a machine
      ///				notification handle the next time it detects an appropriate
      ///				machine
      bool next();

      ///  \brief		stops machine notification handle monitoring
      void close();

   };


} // namespace acme_windows




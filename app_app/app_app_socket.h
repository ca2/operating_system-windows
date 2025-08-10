#pragma once


namespace app_app
{


   class application;
   class service;


   class CLASS_DECL_APP_CORE_USER_SERVICE socket :
      virtual public ::sockets::httpd_socket
   {
   public:


      bool                             m_bSetCookie;

      socket();
      ~socket();

      virtual void OnExecute();
      virtual void OnResponseComplete();

      virtual void OnSSLAccept();

      void send_response();



      virtual void simple_file_server(const ::scoped_string & scopedstrPath);
      virtual void simple_image_server(const ::scoped_string & scopedstrPath, int iMaxWidth = -1, int iMaxHeight = -1);

      virtual bool http_filter_response_header(atom key, string_array_base & straValue);

      //virtual void on_compress();


   };


} // namespace user_service


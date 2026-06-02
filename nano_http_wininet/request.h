//
// From http.cpp by camilo on 20/08/2023 ~02:10 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "hinternet.h"


namespace windows
{



   namespace nano
   {


      namespace http
      {


         class CLASS_DECL_NANO_HTTP_WININET request :
            public hinternet
         {
         public:

            connect& m_connect;

            request(connect& connect, const ::scoped_string& scopedstrOperation, const ::scoped_string& scopedstrObject);
            ~request() override;

            bool send_request(::nano::http::get* pnanohttpget);

            bool get_response(::nano::http::get * pnanohttpget);


         };



      } // namespace http


   }// namespace nano


} // namespace windows




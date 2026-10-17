//
// From http.cpp by camilo on 20/08/2023 ~02:10 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "hinternet.h"
#include <atomic>


namespace windows
{



   namespace nano
   {


      namespace http
      {


         class CLASS_DECL_NANO_HTTP_WINHTTP request :
            public hinternet
         {
         public:

            connect& m_connect;
            std::atomic<unsigned long> m_secureFailureFlags{0};
            DWORD m_callbackError = 0;
            DWORD m_contextError = 0;
            std::atomic<unsigned long> m_secureFailureCount{0};

            static void CALLBACK status_callback(HINTERNET, DWORD_PTR context, DWORD status,
               LPVOID information, DWORD informationLength) noexcept;
            ::string security_diagnostics();

            request(connect& connect, const ::scoped_string& scopedstrOperation, const ::scoped_string& scopedstrObject);
            ~request() override;

            bool send_request(::nano::http::get* pnanohttpget);

            bool get_response(::nano::http::get * pnanohttpget);


         };



      } // namespace http


   }// namespace nano


} // namespace windows




//
// From http.cpp by camilo on 20/08/2023 02:16 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "_.h"
#include "acme/_operating_system.h"
#include <wininet.h>


namespace windows
{


   namespace nano
   {


      namespace http
      {

         class hinternet
         {
         public:


            HINTERNET  m_hinternet;


            hinternet(HINTERNET hinternet = nullptr);
            virtual ~hinternet();


         };


      } // namespace http


   }// namespace nano


} // namespace windows




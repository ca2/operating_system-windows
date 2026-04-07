// Created by camilo on 2024-12-27 05:49 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/user/user/activation_token.h"


namespace win32
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_WIN32 activation_token :
            virtual public ::user::activation_token

         {
         public:


            ::task *          m_ptaskForeground;


            activation_token(::task * ptask);
            ~activation_token();


            bool matches(const ::user::activation_token * pactivationtoken) const override;


         };

   
      } // namespace windowing


   } // namespace acme


} // namespace win32






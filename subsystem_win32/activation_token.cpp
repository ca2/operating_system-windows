// Created by camilo on 2024-12-27 05:49 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "activation_token.h"


namespace win32
{


   namespace acme
   {


      namespace windowing
      {


         activation_token::activation_token(::task * ptask) :
            m_ptaskForeground(ptask)
         {


         }

         
         activation_token::~activation_token()
         {


         }


         bool activation_token::matches(const ::user::activation_token * pactivationtoken) const
         {

            if (!m_ptaskForeground)
            {

               return false;

            }

            auto puseractivationtoken = dynamic_cast <activation_token *>((::user::activation_token *) pactivationtoken);

            if (!puseractivationtoken)
            {

               return false;

            }

            if (!puseractivationtoken->m_ptaskForeground)
            {

               return false;

            }

            return puseractivationtoken->m_ptaskForeground == m_ptaskForeground;

         }


      } // namespace windowing


   } // namespace acme


} // namespace win32




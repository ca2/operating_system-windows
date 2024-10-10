//
// Created by camilo on 31/01/2022 14:38 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/micro/pen.h"
#include "object.h"


namespace windows
{


   namespace acme
   {


      namespace user
      {


         class CLASS_DECL_ACME pen :
            virtual public ::nano::graphics::pen,
            virtual public object
         {
         public:


            //__CreatableFromBase(::nano::graphics::pen, ::nano::graphics::pen);


            pen();
            ~pen() override;


            void update(::nano::graphics::device* pnanodevice) override;


         };



      } // namespace user


   } // namespace acme

} // namespace windows




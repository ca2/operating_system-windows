//
// Created by camilo on 31/01/2022 14:40 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/user/micro/brush.h"
#include "object.h"


namespace windows
{



   namespace acme
   {


      namespace user
      {


         class CLASS_DECL_ACME brush :
            virtual public ::nano::graphics::brush,
            virtual public object
         {
         public:


            //CreatableFromBase(brush, brush);


            brush();
            ~brush() override;


            void update(::nano::graphics::device* pnanodevice) override;


         };



      } // namespace user


   } // namespace acme


} // namespace windows




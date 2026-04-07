//
// Created by camilo on 2026-04-06 14:24 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "../../../source/app/apex/operating_system/windows/innate_subsystem/ImageList.h"


namespace windows
{
   namespace innate_subsystem
   {

      ImageList::ImageList()
      {


         m_himagelist = nullptr;

      }


      ImageList::~ImageList()
      {

         destroy_image_list();

      }


      void ImageList::initializeImageList()
      {



      }


      void ImageList::createImageList(const ::int_size & size, int flags, int iInitialSize, int iGrow)
      {
        m_himagelist = ImageList_Create(size.cx,
                              size.cy,
                                                     flags, iInitialSize,iGrow);


      }


      void ImageList::destroyImageList()
      {

         if (!m_himagelist)
         {

            return;

         }
         ImageList_Destroy(m_himagelist);
         m_himagelist = nullptr;

      }


      void ImageList::addIcon(innate_ui::icon* pinnateuiicon)
      {

         ::cast < ::window

      }


   }// namespace innate_subsystem
}// namnamespace  windows
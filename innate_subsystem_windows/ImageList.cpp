//
// Created by camilo on 2026-04-06 14:24 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "ImageList.h"
#include "innate_ui_win32/icon.h"
#include "drawing/Icon.h"


namespace innate_subsystem_windows
{

   ImageList::ImageList()
   {


      m_himagelist = nullptr;

   }


   ImageList::~ImageList()
   {

      destroyImageList();

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


   void ImageList::addIcon(innate_subsystem::IconInterface * picon)
   {

      auto piconWin32 = picon->impl<::innate_subsystem_windows::Icon>();

      auto hicon = piconWin32->m_hicon;

      ImageList_AddIcon(m_himagelist, hicon);

   }


}// namespace innate_subsystem_windows

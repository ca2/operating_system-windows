//
// Created by camilo on 09/04/2022.
// Modified 2023-10-05 23:50
//
#pragma once


#include "acme_windows/_.h"


#if defined(_acme_windowing_win32_project)
#define CLASS_DECL_ACME_WINDOWING_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_ACME_WINDOWING_WIN32  CLASS_DECL_IMPORT
#endif


namespace win32
{


   namespace acme
   {


      namespace windowing
      {



      } // namespace windowing


   } // namespace acme


} // namespace win32


namespace windows
{

   class window;


} // namespace windows




// Created by camilo 2012-02-13 15:27 BRT I love you my GOD Thomas Borregaard Sørensen!!
#include "framework.h"


CLASS_DECL_WINDOWING_WIN32 int windows_show_window(enum_display edisplay, enum_activation eactivation)
{

   auto bNoActivate = eactivation & e_activation_no_activate;

   switch (edisplay)
   {
   case e_display_default:
      return SW_SHOWDEFAULT;
   case e_display_restored:
      if (bNoActivate)
         return SW_SHOWNA;
      else
         return SW_NORMAL;
   case e_display_iconic:
      if (bNoActivate)
         return SW_SHOWMINNOACTIVE;
      else
         return SW_MINIMIZE;
   case e_display_zoomed:
      return SW_MAXIMIZE;

   case e_display_full_screen:
      return SW_NORMAL;
   default:
      if (edisplay <= 0)
         return SW_HIDE;
      else
         return SW_NORMAL;
   };

}


CLASS_DECL_WINDOWING_WIN32 enum_display windows_show_window_to_edisplay(int iShowWindow, enum_activation & eactivation)
{

   eactivation = e_activation_default;

   if (iShowWindow <= SW_HIDE)
   {

      return e_display_none;

   }

   switch (iShowWindow)
   {
   case SW_SHOWDEFAULT:
      return e_display_default;
   case SW_SHOW:
      return e_display_restored;
   case SW_RESTORE:
      return e_display_restored;
   case SW_MINIMIZE:
      return e_display_iconic;
   case SW_MAXIMIZE:
      return e_display_zoomed;
   case SW_SHOWNA:
      eactivation = e_activation_no_activate;
      return e_display_restored;
   case SW_SHOWMINNOACTIVE:
      eactivation = e_activation_no_activate;
      return e_display_iconic;
   default:
      return e_display_restored;
   }

}




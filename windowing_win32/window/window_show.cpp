// Created by camilo 2012-02-13 15:27 BRT I love you my GOD Thomas Borregaard Soerensen!!
#include "framework.h"


#include "acme/_operating_system.h"


namespace windows
{


   CLASS_DECL_WINDOWING_WIN32 int show_window(enum_display edisplay, const ::user::activation & useractivation)
   {

      auto bNoActivate = useractivation & ::user::e_activation_no_activate;

      switch (edisplay)
      {
      case e_display_default:
         return SW_SHOWDEFAULT;
      case e_display_normal:
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


   CLASS_DECL_WINDOWING_WIN32 enum_display show_window_to_edisplay(int iShowWindow, ::user::activation & useractivation)
   {

      useractivation = { ::user::e_activation_default } ;

      if (iShowWindow <= SW_HIDE)
      {

         return e_display_none;

      }

      switch (iShowWindow)
      {
      case SW_SHOWDEFAULT:
         return e_display_default;
      case SW_SHOW:
         return e_display_normal;
      case SW_RESTORE:
         return e_display_normal;
      case SW_MINIMIZE:
         return e_display_iconic;
      case SW_MAXIMIZE:
         return e_display_zoomed;
      case SW_SHOWNA:
         useractivation = { ::user::e_activation_no_activate };
         return e_display_normal;
      case SW_SHOWMINNOACTIVE:
         useractivation = { ::user::e_activation_no_activate };
         return e_display_iconic;
      default:
         return e_display_normal;
      }

   }



} // namespace windows




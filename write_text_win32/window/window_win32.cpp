#include "framework.h"




#ifdef WINDOWS_DESKTOP


// https://stackoverflow.com/questions/15966642/how-do-you-tell-lshift-apart-from-rshift-in-wm-keydown-events

wparam MapLeftRightKeys(wparam vk, lparam lParam)
{

   wparam new_vk = vk;

   unsigned int scancode = (lParam & 0x00ff0000) >> 16;

   int extended = (lParam & 0x01000000) != 0;

   switch (vk)
   {
   case VK_SHIFT:
      new_vk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
      break;
   case VK_CONTROL:
      new_vk = extended ? VK_RCONTROL : VK_LCONTROL;
      break;
   case VK_MENU:
      new_vk = extended ? VK_RMENU : VK_LMENU;
      break;
   default:
      // not a key we map from matter to left/right specialized
      //  just return it.
      new_vk = vk;
      break;
   }
   return new_vk;
}


#endif

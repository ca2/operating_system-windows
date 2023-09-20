// created by Camilo 2021-02-04 00:58 BRT CamiloSasuke<3ThomasBorregaardSoerensen
#include "framework.h"
#include "keyboard.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/message/user.h"


#include "acme/_operating_system.h"


namespace windowing_win32
{

   
   keyboard::keyboard()
   {


   }


   keyboard::~keyboard()
   {


   }

   ::user::enum_key virtual_key_code_to_user_key(int iVirtualKey)
   {

      char ch;

      ch = (char)iVirtualKey;

      if (ch >= '0' && ch <= '9')
      {

         return (::user::enum_key)(::user::e_key_0 + (ch - '0'));

      }

      if (ch >= 'A' && ch <= 'Z')
      {

         return (::user::enum_key) (::user::e_key_a + (ch - 'A'));

      }

      if (ch == ' ')
      {

         return ::user::e_key_space;

      }

      switch (iVirtualKey)
      {
      case VK_LEFT:
         return ::user::e_key_left;
      case VK_RIGHT:
         return ::user::e_key_right;
      case VK_UP:
         return ::user::e_key_up;
      case VK_DOWN:
         return ::user::e_key_down;
      case VK_TAB:
         return ::user::e_key_tab;
      case VK_RETURN:
         return ::user::e_key_return;
      case VK_LSHIFT:
         return ::user::e_key_left_shift;
      case VK_RSHIFT:
         return ::user::e_key_right_shift;
      case VK_LCONTROL:
         return ::user::e_key_left_control;
      case VK_RCONTROL:
         return  ::user::e_key_right_control;
      case VK_LMENU:
         return ::user::e_key_left_alt;
      case VK_RMENU:
         return ::user::e_key_right_alt;
      case VK_LWIN:
         return ::user::e_key_left_command;
      case VK_RWIN:
         return ::user::e_key_right_command;
      case VK_BACK:
         return ::user::e_key_back;
      case VK_DELETE:
         return ::user::e_key_delete;
      case VK_HOME:
         return ::user::e_key_home;
      case VK_END:
         return ::user::e_key_end;
      case VK_PRIOR:
         return ::user::e_key_prior;
      case VK_NEXT:
         return ::user::e_key_next;
      }

      return ::user::e_key_none;

   }


   void keyboard::translate_os_key_message(::user::key* pkey)
   {

      synchronous_lock synchronouslock(synchronization());

      if (pkey->m_ekey == ::user::e_key_refer_to_text_member
         && pkey->m_strText.has_char())
      {

         return;

      }

      pkey->m_ekey = virtual_key_code_to_user_key(pkey->m_iVirtualKey);

   }


} // namespace windowing_win32





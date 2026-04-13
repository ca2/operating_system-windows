// created by Camilo 2021-02-04 00:58 BRT CamiloSasuke<3ThomasBorregaardSoerensen
#include "framework.h"
#include "keyboard.h"
#include "acme/constant/user_key.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/message/user.h"
#include "acme/operating_system/windows/user.h"

#include "acme/_operating_system.h"


namespace windowing_win32
{

   
   keyboard::keyboard()
   {


   }


   keyboard::~keyboard()
   {


   }

   void keyboard::translate_os_key_message(::user::key* pkey)
   {

      _synchronous_lock synchronouslock(synchronization());

      if (pkey->m_ekey == ::user::e_key_refer_to_text_member
         && pkey->m_strText.has_character())
      {

         return;

      }

      pkey->m_ekey = ::windows::virtual_key_code_to_user_key(pkey->m_iVirtualKey);

   }


} // namespace windowing_win32



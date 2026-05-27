// Created by camilo on 2026-04-17 17:45 <3ThomasBorregaardSørensen!!
// Using HKL (Windows Keyboard Layout) code from Remoting.
#pragma once

#include "innate_subsystem/gui/KeyboardLayout.h"
#include "innate_subsystem/_common_header.h"


namespace innate_subsystem_windows
{


   class KeyboardLayout : virtual public ::Implementation < ::innate_subsystem::KeyboardLayoutInterface >
   {
   public:


       KeyboardLayout();

       ~KeyboardLayout() override;

      bool vkCodeToString(::u16 virtKey, bool down, ::wstring *res, ::innate_subsystem::keyboard_state_t * pkeyboarstate) override;

      virtual bool _tryTranslateNotPrintableToUnicode(::u16 virtKey, HKL currentLayout, WCHAR *unicodeChar,
                                                      ::innate_subsystem::keyboard_state_t *pkeyboarstate);

   };


} // namespace innate_subsystem

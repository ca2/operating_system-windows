// Created by camilo on 2026-04-17 17:45 <3ThomasBorregaardSørensen!!
// Using HKL (Windows Keyboard Layout) code from Remoting.
#include "framework.h"
#include "KeyboardLayout.h"



namespace innate_subsystem_windows
{

    KeyboardLayout::KeyboardLayout()
    {


    }

    KeyboardLayout::~KeyboardLayout() {}



   bool KeyboardLayout::vkCodeToString(::u16 virtKey, bool down, ::wstring *res, 
                                       ::innate_subsystem::keyboard_state_t *pkeyboardstate)
   {

             bool needReleaseModifiers = false;
      wchar_t outBuff[20];

       HKL currentLayout = GetKeyboardLayout(0);
      
       ::i32 count = ToUnicodeEx(virtKey, 0, pkeyboardstate->m_viewerKeyState, outBuff,
           sizeof(outBuff) / sizeof(WCHAR),
           0, currentLayout);
      
       // For keyboards with dead keys
       if (pkeyboardstate->m_doubleDeadCatched && !down && !pkeyboardstate->m_allowProcessDoubleChar)
       {
          debug("Disable process ::i8 event");
          pkeyboardstate->m_allowProcessCharEvent = false;
          pkeyboardstate->m_doubleDeadCatched = false;
       }
      
       // For keyboards with dead keys
       if (count == 2 && (::innate_subsystem::isDoubleDeadCharacters(outBuff))) {
          debug("Extra ::f64 dead key catched.");
          if (down) {
             debug("Enable process ::i8 event. Enable process ::f64 ::i8.");
             pkeyboardstate->m_allowProcessDoubleChar = true;
             pkeyboardstate->m_allowProcessCharEvent = true;
             pkeyboardstate->m_doubleDeadCatched = true;
             count = ToUnicodeEx(virtKey, 0, pkeyboardstate->m_viewerKeyState, outBuff,
                 sizeof(outBuff) / sizeof(WCHAR),
                 0, currentLayout);
             if (count > 0) {
                outBuff[count] = 0;
             } else {
                outBuff[0] = 0;
             }
             //ToUnicodeEx can return without null termination
             debug("ToUnicodeEx() function called second. Returned: {}. Output buff: {}", count,
             ::wstring(outBuff)); res->clear(); return false;
          }
          else if (!pkeyboardstate->m_allowProcessCharEvent)
          {
             debug("Disable second calling ToUnicodeEx()");
             res->clear();
             return false;
          }
       }
      
       if (count > 0) {
          count = ToUnicodeEx(virtKey, 0, pkeyboardstate->m_viewerKeyState, outBuff,
                sizeof(outBuff) / sizeof(WCHAR), 0, currentLayout);
       }
       if (count > 0) {
          outBuff[count] = 0;
       } else {
          outBuff[0] = 0;
       }
       debug("ToUnicodeEx() returned {}, output buff : {}", count, ::wstring(outBuff));
      
       if (count == 1 && !pkeyboardstate->m_allowProcessCharEvent)
       {
          res->add(pkeyboardstate->GettingCharFromCtrlSymbol(outBuff[0]));
          needReleaseModifiers = true;
       }
       // Two or more (only two of them is relevant?)
       else if (count > 1) {
          for (::i32 i = 0; i < count; i++) {
             res->add(pkeyboardstate->GettingCharFromCtrlSymbol(outBuff[i]));
          }
          needReleaseModifiers = true;
       } else if (count == 0) {
          WCHAR unicodeChar;
          if (_tryTranslateNotPrintableToUnicode(virtKey, currentLayout, &unicodeChar, pkeyboardstate))
          {
             res->add(unicodeChar);
          }
       } else if (count == -1 && down) {
          debug("Dead key pressed, wait for a ::i8 event");
          pkeyboardstate->m_allowProcessCharEvent = true;
       }

       return true;
   }


       bool KeyboardLayout::_tryTranslateNotPrintableToUnicode(::u16 virtKey, HKL currentLayout,
                                                           WCHAR *unicodeChar,
                                                           ::innate_subsystem::keyboard_state_t *pkeyboardstate)
    {
       WCHAR outBuff[20];
       debug("Was get a not printable symbol then try get a printable"
         " with turned off the ctrl and alt modifiers");
       // E.g if pressed Ctrl + Alt + A
       // Try found ::i8 without modificators
       ::u8 withoutCtrlAltKbdState[256];
       memcpy(withoutCtrlAltKbdState, pkeyboardstate->m_viewerKeyState, sizeof(withoutCtrlAltKbdState));
       withoutCtrlAltKbdState[VK_LCONTROL] = 0;
       withoutCtrlAltKbdState[VK_RCONTROL] = 0;
       withoutCtrlAltKbdState[VK_CONTROL] = 0;
       withoutCtrlAltKbdState[VK_LMENU] = 0;
       withoutCtrlAltKbdState[VK_RMENU] = 0;
       withoutCtrlAltKbdState[VK_MENU] = 0;
       ::i32 count = ToUnicodeEx(virtKey, 0, withoutCtrlAltKbdState, outBuff,
         sizeof(outBuff) / sizeof(WCHAR),
         0, currentLayout);
       if (count > 0) {
          outBuff[count] = 0;
       }
       else {
          outBuff[0] = 0;
       }
       debug("ToUnicodeEx() without ctrl and alt return {} wchars : {}", count, ::wstring(outBuff));
   
       if (count == 1) { // other case will be ignored
          *unicodeChar = outBuff[0];
          return true;
       }
       return false;
    }

   }  // namespace innate_subsystem_windows

// Created by camilo on 2026-04-17 17:45 <3ThomasBorregaardSørensen!!
// Using HKL (Windows Keyboard Layout) code from TightVNC.
#include "framework.h"
#include "KeyboardLayout.h"



namespace innate_subsystem_windows
{

    KeyboardLayout::KeyboardLayout()
    {


    }

    KeyboardLayout::~KeyboardLayout() {}



   bool KeyboardLayout::vkCodeToString(unsigned short virtKey, bool down, ::wstring *res, 
                                       ::innate_subsystem::keyboard_state_t *pkeyboardstate)
   {

             bool needReleaseModifiers = false;
      wchar_t outBuff[20];

       HKL currentLayout = GetKeyboardLayout(0);
      
       int count = ToUnicodeEx(virtKey, 0, pkeyboardstate->m_viewerKeyState, outBuff,
           sizeof(outBuff) / sizeof(WCHAR),
           0, currentLayout);
      
       // For keyboards with dead keys
       if (pkeyboardstate->m_doubleDeadCatched && !down && !pkeyboardstate->m_allowProcessDoubleChar)
       {
          debug("Disable process char event");
          pkeyboardstate->m_allowProcessCharEvent = false;
          pkeyboardstate->m_doubleDeadCatched = false;
       }
      
       // For keyboards with dead keys
       if (count == 2 && (::innate_subsystem::isDoubleDeadCharacters(outBuff))) {
          debug("Extra double dead key catched.");
          if (down) {
             debug("Enable process char event. Enable process double char.");
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
          for (int i = 0; i < count; i++) {
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
          debug("Dead key pressed, wait for a char event");
          pkeyboardstate->m_allowProcessCharEvent = true;
       }

       return true;
   }


       bool KeyboardLayout::_tryTranslateNotPrintableToUnicode(unsigned short virtKey, HKL currentLayout,
                                                           WCHAR *unicodeChar,
                                                           ::innate_subsystem::keyboard_state_t *pkeyboardstate)
    {
       WCHAR outBuff[20];
       debug("Was get a not printable symbol then try get a printable"
         " with turned off the ctrl and alt modifiers");
       // E.g if pressed Ctrl + Alt + A
       // Try found char without modificators
       unsigned char withoutCtrlAltKbdState[256];
       memcpy(withoutCtrlAltKbdState, pkeyboardstate->m_viewerKeyState, sizeof(withoutCtrlAltKbdState));
       withoutCtrlAltKbdState[VK_LCONTROL] = 0;
       withoutCtrlAltKbdState[VK_RCONTROL] = 0;
       withoutCtrlAltKbdState[VK_CONTROL] = 0;
       withoutCtrlAltKbdState[VK_LMENU] = 0;
       withoutCtrlAltKbdState[VK_RMENU] = 0;
       withoutCtrlAltKbdState[VK_MENU] = 0;
       int count = ToUnicodeEx(virtKey, 0, withoutCtrlAltKbdState, outBuff,
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

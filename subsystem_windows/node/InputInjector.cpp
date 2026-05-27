// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
#include "framework.h"
#include "InputInjector.h"
#include "Keyboard.h"
#include "acme/constant/user_key.h"
#include "acme/operating_system/windows/user.h"
#include "subsystem/node/SystemException.h"
//#include "remoting/remoting/win_system/Environment.h"
//#include <vector>

//#include <crtdbg.h>

namespace subsystem_windows
{
      InputInjector::InputInjector():
            m_controlIsPressed(false),
      m_menuIsPressed(false),
      m_deleteIsPressed(false),
      m_shiftIsPressed(false),
      m_winIsPressed(false),
      m_ctrlAltDelEnabled(false),
      m_plogwriter(nullptr)
      {
      }


      InputInjector::~InputInjector()
      {
         try {
            resetModifiers();
         } catch (...) {
         }
      }

      void InputInjector::initialize_input_injector(bool ctrlAltDelEnabled, ::subsystem::LogWriter *plogwriter)
     //:
     {
         m_ctrlAltDelEnabled =ctrlAltDelEnabled;
         m_plogwriter = plogwriter;
         // FIXME: Better to call this function from an owner (Now, its
         // possible only from trunk code because in the stable hive the owner is
         // the deprecated KeyEvent class)
         try {
            resetModifiers();
         }
         catch (::exception &e) {
            m_plogwriter->error("InputInjector: error occurred while reseting modifiers: {}",
              e.get_message());
         }
     }

      void InputInjector::injectKeyPress(::user::enum_key euserkey)
      {
         injectKeyEvent(euserkey, false);
      }

      void InputInjector::injectKeyRelease(::user::enum_key euserkey)
      {
         injectKeyEvent(euserkey, true);
      }

      void InputInjector::injectKeyEvent(::user::enum_key euserkey, bool release, bool extended)
      {
         m_plogwriter->debug("Prepare to inject the key event:"
                    " user::enum_key = {}, release = {}, extended = {}",
                    (::i32)euserkey,
                    (::i32)release,
                    (::i32)extended);
         m_plogwriter->debug("The modifier states before:"
                    " m_controlIsPressed = {};"
                    " m_menuIsPressed = {};"
                    " m_deleteIsPressed = {};"
                    " m_shiftIsPressed = {};"
                    " m_winIsPressed = {};",
                    (::i32)m_controlIsPressed,
                    (::i32)m_menuIsPressed,
                    (::i32)m_deleteIsPressed,
                    (::i32)m_shiftIsPressed,
                    (::i32)m_winIsPressed);

         if (euserkey == ::user::e_key_control || euserkey == ::user::e_key_right_control || euserkey == ::user::e_key_left_control) {
            m_controlIsPressed = !release;
         }
         if (euserkey == ::user::e_key_alt || euserkey == ::user::e_key_right_alt || euserkey == ::user::e_key_left_alt) {
            m_menuIsPressed = !release;
         }
         if (euserkey == ::user::e_key_delete) {
            m_deleteIsPressed = !release;
         }
         if (euserkey == ::user::e_key_shift || euserkey == ::user::e_key_right_shift || euserkey == ::user::e_key_left_shift) {
            m_shiftIsPressed = !release;
         }
         if (euserkey == ::user::e_key_left_command || euserkey == ::user::e_key_right_command) {
            m_winIsPressed = !release;
         }
         m_plogwriter->debug("The modifier states after:"
                    " m_controlIsPressed = {};"
                    " m_menuIsPressed = {};"
                    " m_deleteIsPressed = {};"
                    " m_shiftIsPressed = {};"
                    " m_winIsPressed = {};",
                    (::i32)m_controlIsPressed,
                    (::i32)m_menuIsPressed,
                    (::i32)m_deleteIsPressed,
                    (::i32)m_shiftIsPressed,
                    (::i32)m_winIsPressed);

         if (m_controlIsPressed && m_menuIsPressed && m_deleteIsPressed &&
             !m_winIsPressed && !m_shiftIsPressed) {
            if (m_ctrlAltDelEnabled) {
               m_plogwriter->debug("Try simulate the Ctrl+Alt+Del combination");
               throw todo;
               // if (node()->_windows_isVistaOrLater()) {
               //   Environment::simulateCtrlAltDelUnderVista(m_log);
               // }
               // else {
               //   Environment::simulateCtrlAltDel(m_log);
               // }
            } else {
               m_plogwriter->debug("The Ctrl+Alt+Del combination is disabled. Ignore the Del key pressing");
            }
             } else {
                INPUT keyEvent = {0};

                auto vkCode = e_user_key_to_vkcode(euserkey);
                keyEvent.type = INPUT_KEYBOARD;
                keyEvent.ki.wVk = vkCode;
                keyEvent.ki.wScan = MapVirtualKey(vkCode, 0);

                if (release) {
                   keyEvent.ki.dwFlags = KEYEVENTF_KEYUP;
                }

                if (extended) {
                   keyEvent.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
                }

                if (SendInput(1, &keyEvent, sizeof(keyEvent)) == 0) {
                   auto lasterror = ::windows::last_error();
                   if (lasterror != ERROR_SUCCESS) {
                      throw ::subsystem::SystemException("SendInput() function failed:", lasterror);
                   } else {
                      // Under Vista or later the SendInput() function doesn't return error
                      // code if inputs blocked by UIPI.
                      throw ::subsystem::Exception("SendInput() function failed");
                   }
                }
             }
      }

      void InputInjector::injectCharEvent(::i32 ch, bool release)
      {
         m_plogwriter->debug("Try insert a ::i8 event: ::i8 = {}, release = {}",
                    (::i32)ch, (::i32)release);

         bool ctrlOrAltPressed = m_controlIsPressed || m_menuIsPressed;
         SHORT vkKeyScanResult = 0;
         HKL hklCurrent = (HKL)0x04090409;
         try {
            hklCurrent = _getCurrentKbdLayout();
            m_plogwriter->debug("Current keyboard layout = {:#08x}", (::i32)hklCurrent);
            vkKeyScanResult = _searchVirtKey(ch, hklCurrent);
            m_plogwriter->debug("The virtual code scan result = {}", (::i32)vkKeyScanResult);
         } catch (...) {
            m_plogwriter->debug("Can't insert the ::i8 by simulating a key press event,"
                      " therefore try insert it as an unicode symbol");
            if (ctrlOrAltPressed) {
               m_plogwriter->warning("Can't insert the ::i8 by an unicode symbol because"
                            " a modifier is pressed");
               throw;
            }
            INPUT keyEvent = {0};

            keyEvent.type = INPUT_KEYBOARD;
            keyEvent.ki.wVk = 0;
            keyEvent.ki.wScan = ch;
            keyEvent.ki.dwFlags = KEYEVENTF_UNICODE;

            if (release) {
               keyEvent.ki.dwFlags |= KEYEVENTF_KEYUP;
            }

            if (SendInput(1, &keyEvent, sizeof(keyEvent)) == 0) {
               throw ::subsystem::SystemException();
            }
            return;
         }
         bool controlSym;
         if (ch >= L'A' && ch <= L'Z' || ch >= L'a' && ch <= L'z') {
            controlSym = m_controlIsPressed && !m_menuIsPressed && !m_shiftIsPressed;
         } else {
            controlSym = false;
         }
         // Not all keys must be typed with the SHIFT to get the lower case when the
         // CAPS pressed, e.g. the numerical keys.
         bool resistantToCaps = _isResistantToCaps((BYTE)vkKeyScanResult, hklCurrent);
         bool invariantToShift = _isInvariantToShift((BYTE)vkKeyScanResult, hklCurrent);

         // If code belonged with high registr we must generate shift up and shift
         // down also.
         bool shiftedKey = (vkKeyScanResult >> 8 & 1) != 0;
         shiftedKey = shiftedKey && !capsToggled() ||
                      shiftedKey && capsToggled() && resistantToCaps ||
                      !shiftedKey && capsToggled() && !resistantToCaps;
         bool shiftPressNeeded = shiftedKey && !m_shiftIsPressed && !release &&
                                 !controlSym;
         bool shiftUpNeeded = !shiftedKey && m_shiftIsPressed && !release &&
                              !controlSym && !invariantToShift;
         bool ctrlPressNeeded = (vkKeyScanResult >> 9 & 1) && !m_controlIsPressed &&
                                !release;
         bool altPressNeeded = (vkKeyScanResult >> 10 & 1) && !m_menuIsPressed &&
                               !release;
         if ((ctrlPressNeeded || altPressNeeded) &&
             (m_controlIsPressed || m_menuIsPressed)) {
            m_plogwriter->error("Received a control combination that we doesn't know how it can be made");
            return;
             }

         m_plogwriter->debug("Variable states before generate key events to get the ::i8:"
                    " controlSym = {};"
                    " resistantToCaps = {};"
                    " invariantToShift = {};"
                    " shiftedKey = {};"
                    " shiftPressNeeded = {};"
                    " shiftUpNeeded = {};"
                    " ctrlPressNeeded = {};"
                    " altPressNeeded = {};",
                    (::i32)controlSym,
                    (::i32)resistantToCaps,
                    (::i32)invariantToShift,
                    (::i32)shiftedKey,
                    (::i32)shiftPressNeeded,
                    (::i32)shiftUpNeeded,
                    (::i32)ctrlPressNeeded,
                    (::i32)altPressNeeded);

         if (ctrlPressNeeded) {
            injectKeyEvent(::user::e_key_control, false);
         }
         if (altPressNeeded) {
            injectKeyEvent(::user::e_key_alt, false);
         }
         if (shiftPressNeeded) {
            injectKeyEvent(::user::e_key_shift, false);
         } else if (shiftUpNeeded) {
            injectKeyEvent(::user::e_key_shift, true);
         }

         auto euserkey = windows::virtual_key_code_to_user_key(vkKeyScanResult & 255);
         injectKeyEvent(euserkey, release);
         if (shiftPressNeeded) {
            injectKeyEvent(::user::e_key_shift, true);
         } else if (shiftUpNeeded) {
            injectKeyEvent(::user::e_key_shift, false);
         }
         if (altPressNeeded) {
            injectKeyEvent(::user::e_key_alt, true);
         }
         if (ctrlPressNeeded) {
            injectKeyEvent(::user::e_key_control, true);
         }
      }

      bool InputInjector::isAscii(::i32 ch)
      {
         if (ch >= 0 && ch < 128) {
            return true;
         }
         return false;
      }

      SHORT InputInjector::_searchVirtKey(WCHAR ch, HKL hklCurrent)
      {
         // Test for special case
         bool modifiersPressed = m_controlIsPressed || m_menuIsPressed ||
                                 m_shiftIsPressed;
         bool onlyCtrlPressed = m_controlIsPressed && !m_menuIsPressed &&
                                !m_shiftIsPressed;
         // Try get virtual code in the current keyboard layout
         SHORT vkKeyScanResult = VkKeyScanExW(ch, hklCurrent);
         if (vkKeyScanResult == -1) {
            if (onlyCtrlPressed) {
               if (ch >= L'A' && ch <= L'Z') {
                  return (SHORT)ch;
               } else if (ch >= L'a' && ch <= L'z') {
                  return (SHORT)(ch - L'a' + L'A');
               }
            }
            ::string errMess;
            errMess.formatf("Can't translate the {} character to the scan code",
                           (::u32)ch);
            throw ::subsystem::Exception(errMess);
         }
         if (_isDeadKey(vkKeyScanResult, hklCurrent)) {
            throw ::subsystem::Exception("Special dead symbol must be inserted"
                            " only as unicode character");
         }
         if (!_isOneKeyEventChar(ch, vkKeyScanResult, hklCurrent)) {
            ::string errMess;
            errMess.formatf("Can't get the {} character by one keyboard event",
                           (::u32)ch);
            throw ::subsystem::Exception(errMess);
         }
         // Special trick to get round a problem when printing the ^6 characters
         // instead of estimated 6.
         if (!modifiersPressed) {
            ::u16 layout = ((::u32)hklCurrent & 0xffff0000) >> 16;
            const ::u16 TURKISH = MAKELANGID(LANG_TURKISH, SUBLANG_DEFAULT);
            const ::u16 NORWEGIAN = MAKELANGID(LANG_NORWEGIAN, SUBLANG_DEFAULT);
            const ::u16 BRAZILIAN = MAKELANGID(LANG_PORTUGUESE, SUBLANG_PORTUGUESE_BRAZILIAN);
            const ::u16 GREEK = MAKELANGID(LANG_GREEK, SUBLANG_DEFAULT);
            const ::u16 POLISH1 = MAKELANGID(LANG_POLISH, SUBLANG_DEFAULT);
            const ::u16 POLISH2 = MAKELANGID(LANG_POLISH, SUBLANG_POLISH_POLAND);

            if ((layout == POLISH1 || layout == POLISH2) && ch == _T('`')) {
               throw ::subsystem::Exception("Special case for the '`' character on the POLISH"
                 " keyboard, it will be inserted as"
                 " an unicode");
            }

            if (layout == 0xf001 && ch == _T('6')) {
               throw ::subsystem::Exception("Special case for the '6' character on the USA"
                               " international keyboard, it will be inserted as"
                               " an unicode");
            }
            if (layout == BRAZILIAN && ch == _T('6')) {
               throw ::subsystem::Exception("Special case for the '6' character on the brazilian"
                 " keyboard, it will be inserted as"
                 " an unicode");
            }
            if (layout == NORWEGIAN && ch == _T('\\')) {
               throw ::subsystem::Exception("Special case for the '\\' character on the norwegian"
                               " keyboard, it will be inserted as"
                               " an unicode");
            }
            if (layout == TURKISH && ch == _T('3')) {
               throw ::subsystem::Exception("Special case for the '3' character on the turkish-Q"
                 " keyboard, it will be inserted as"
                 " an unicode");
            }
            if (layout == GREEK && ch == 0x03c2) {
               throw ::subsystem::Exception("Special case for the 'w' character on the greek"
                 " keyboard, it will be inserted as"
                 " an unicode");
            }
         }
         return vkKeyScanResult;
      }

      bool InputInjector::capsToggled()
      {
         return (GetKeyState(VK_CAPITAL) & 1) != 0;
      }

      bool InputInjector::_isDeadKey(SHORT scanResult, HKL keyboardLayout)
      {
         ::u8 kbdState[256];
         memset(kbdState, 0, sizeof(kbdState));
         WCHAR outBuff[20];
         bool withShift = (scanResult >> 8 & 1) != 0;
         bool withCtrl  = (scanResult >> 9 & 1) != 0;
         bool withAlt   = (scanResult >> 10 & 1) != 0;

         kbdState[VK_SHIFT]   = withShift ? 128 : 0;
         kbdState[VK_CONTROL] = withCtrl  ? 128 : 0;
         kbdState[VK_MENU]    = withAlt   ? 128 : 0;

         ::u8 virtKey = scanResult & 255;

         ::i32 count = ToUnicodeEx(virtKey, 0, kbdState, outBuff,
                                 sizeof(outBuff) / sizeof(WCHAR),
                                 0, keyboardLayout);
         bool result = count == -1;
         count = ToUnicodeEx(virtKey, 0, kbdState, outBuff,
                             sizeof(outBuff) / sizeof(WCHAR),
                             0, keyboardLayout);
         result = result || count == -1;
         return result;
      }

      bool InputInjector::_isOneKeyEventChar(WCHAR ch, SHORT scanResult,
                                            HKL keyboardLayout)
      {
         ::u8 kbdState[256];
         memset(kbdState, 0, sizeof(kbdState));
         WCHAR outBuff[20];
         bool withShift = (scanResult >> 8 & 1) != 0;
         bool withCtrl  = (scanResult >> 9 & 1) != 0;
         bool withAlt   = (scanResult >> 10 & 1) != 0;

         kbdState[VK_SHIFT]   = withShift ? 128 : 0;
         kbdState[VK_CONTROL] = withCtrl  ? 128 : 0;
         kbdState[VK_MENU]    = withAlt   ? 128 : 0;

         ::u8 virtKey = scanResult & 255;

         ::i32 count = ToUnicodeEx(virtKey, 0, kbdState, outBuff,
                                 sizeof(outBuff) / sizeof(WCHAR),
                                 0, keyboardLayout);
         if (count == 1) {
            return outBuff[0] == ch;
         } else {
            return false;
         }
      }

      HKL InputInjector::_getCurrentKbdLayout()
      {
         // Determine current owning thread.
         HWND hwnd = GetForegroundWindow();
         if (hwnd == 0) {
            throw ::subsystem::Exception("Can't insert key event because"
                            " a window is losing activation");
         }
         DWORD threadId = GetWindowThreadProcessId(hwnd, 0);
         return GetKeyboardLayout(threadId);
      }

      bool InputInjector::_isDifferentWith(BYTE modifier, BYTE modStateValueOfOn,
                                          BYTE virtKey, HKL keyboardLayout)
      {
         ::u8 kbdState[256];
         memset(kbdState, 0, sizeof(kbdState));
         WCHAR outBuff1[20], outBuff2[20];

         // Get symbol(s) without the modifier.
         ::i32 count1 = ToUnicodeEx(virtKey, 0, kbdState, outBuff1,
                                  sizeof(outBuff1) / sizeof(WCHAR),
                                  0, keyboardLayout);

         // Get symbol(s) with modifier.
         kbdState[modifier & 255] = modStateValueOfOn;
         ::i32 count2 = ToUnicodeEx(virtKey, 0, kbdState, outBuff2,
                                 sizeof(outBuff2) / sizeof(WCHAR),
                                 0, keyboardLayout);
         if (count1 != count2) return false; // It isn't invariant
         if (memcmp(outBuff1, outBuff2, count1 * sizeof(WCHAR)) != 0) {
            return false;
         } else {
            return true;
         }
      }

      bool InputInjector::_isInvariantToShift(BYTE virtKey, HKL keyboardLayout)
      {
         return _isDifferentWith(VK_SHIFT, 128, virtKey, keyboardLayout);
      }

      bool InputInjector::_isResistantToCaps(BYTE virtKey, HKL keyboardLayout)
      {
         return _isDifferentWith(VK_CAPITAL, 1, virtKey, keyboardLayout);
      }

      void InputInjector::resetModifiers()
      {
         // The Alt key.
         injectKeyEvent(::user::e_key_alt, true);
         injectKeyEvent(::user::e_key_left_alt, true);
         injectKeyEvent(::user::e_key_right_alt, true);
         // The Shift key.
         injectKeyEvent(::user::e_key_shift, true);
         injectKeyEvent(::user::e_key_left_shift, true);
         injectKeyEvent(::user::e_key_right_shift, true);
         // The Ctrl key.
         injectKeyEvent(::user::e_key_control, true);
         injectKeyEvent(::user::e_key_left_control, true);
         injectKeyEvent(::user::e_key_right_control, true);
         // The Win key.
         injectKeyEvent(::user::e_key_left_command, true);
         injectKeyEvent(::user::e_key_right_command, true);
         // The Delete key.
         injectKeyEvent(::user::e_key_delete, true);
      }

}// namespace subsystem_windows




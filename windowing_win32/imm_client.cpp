#include "framework.h"
#include "imm_client.h"
#include "imm_context.h"
#include "acme/constant/user_message.h"
#include "acme/constant/user_key.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/message/user.h"
#include "aura/user/user/interaction.h"
#include "aura/platform/session.h"


#ifdef WINDOWS_DESKTOP


imm_client::imm_client()
{

   m_bImeCancelling = false;
   m_bTextCompositionActive2 = false;

}


imm_client::~imm_client()
{


}


void imm_client::initialize_text_composition_client(::channel * pchannel, ::user::interaction * puserinteraction)
{

   m_puserinteraction = puserinteraction;

   USER_MESSAGE_LINK(::user::e_message_set_focus, pchannel, this, &::imm_client::on_message_set_focus);
   USER_MESSAGE_LINK(::user::e_message_kill_focus, pchannel, this, &::imm_client::on_message_kill_focus);
   USER_MESSAGE_LINK(WM_IME_SETCONTEXT, pchannel, this, &::imm_client::_001OnIme);
   USER_MESSAGE_LINK(WM_IME_STARTCOMPOSITION, pchannel, this, &::imm_client::_001OnIme);
   USER_MESSAGE_LINK(WM_IME_COMPOSITION, pchannel, this, &::imm_client::_001OnIme);
   USER_MESSAGE_LINK(WM_IME_ENDCOMPOSITION, pchannel, this, &::imm_client::_001OnIme);
   USER_MESSAGE_LINK(WM_IME_NOTIFY, pchannel, this, &::imm_client::_001OnIme);
   USER_MESSAGE_LINK(WM_IME_KEYDOWN, pchannel, this, &::imm_client::_001OnIme);
   USER_MESSAGE_LINK(WM_IME_KEYUP, pchannel, this, &::imm_client::_001OnIme);
   USER_MESSAGE_LINK(WM_IME_SELECT, pchannel, this, &::imm_client::_001OnIme);
   USER_MESSAGE_LINK(WM_INPUTLANGCHANGE, pchannel, this, &::imm_client::_001OnIme);

   USER_MESSAGE_LINK(::user::e_message_char, pchannel, this, &::imm_client::_011OnChar);
   USER_MESSAGE_LINK(WM_IME_CHAR, pchannel, this, &::imm_client::_011OnChar);

   USER_MESSAGE_LINK(::user::e_message_key_down, pchannel, this, &::imm_client::on_message_key_down);


}





void imm_client::on_message_set_focus(::message::message * pmessage)
{

}


void imm_client::on_message_kill_focus(::message::message * pmessage)
{

   set_text_composition_active(false);

}


void imm_client::_011OnChar(::message::message * pmessage)
{

   ::pointer<::user::message>pusermessage(pmessage);

   if (pmessage->m_eusermessage == ::user::e_message_char)
   {

      auto psession = session();

      if (psession->is_key_pressed(::user::e_key_control)
         || psession->is_key_pressed(::user::e_key_alt))
      {

         information() << "CTRL and/or ALT pressed : ignoring key press";

         return;

      }

      if (pmessage->m_wparam >= 0 && pmessage->m_wparam <= 31)
      {

         // if it is control character

         return;

      }

      //if (pmessage->m_wparam == '\t')
      //{

      //   return;

      //}

      wchar_t wsz[2];
      wsz[0] = (wchar_t)pusermessage->m_wparam;
      wsz[1] = '\0';

      string strChar;

      strChar = wsz;

      //if (!m_strImeComposition.case_insensitive_begins_eat(strChar))
      //{

      pmessage->m_bRet = true;

      m_puserinteraction->insert_text(strChar, false, e_source_user);

      //}

   }

}


void imm_client::insert_text(const ::scoped_string & scopedstr, bool bForceNewStep, const ::action_context & context)
{

   text_composition_client::insert_text(scopedstr, bForceNewStep, context);

}


void imm_client::_001OnIme(::message::message * pmessage)
{

   synchronous_lock synchronouslock(synchronization());

#ifdef WINDOWS_DESKTOP

   ::pointer<::user::message>pusermessage(pmessage);

   if (pmessage->m_eusermessage == WM_INPUTLANGCHANGE)
   {

      ::output_debug_string("WM_INPUTLANGCHANGE");

      //get_wnd()->pred([this]()
      //   {

      //      imm_context imm(m_ptextcompositionclient);

      //      if (!ImmGetOpenStatus(imm))
      //      {

      //         ImmSetOpenStatus(imm, true);

      //      }
      //
      //      //SendMessage(ImmGetDefaultIMEWnd(get_handle()), WM_IME_CONTROL, IMC_OPENSTATUSWINDOW, 0);

      //      //   output_debug_string("window already open");

      //      //}

      //      //


      //   });

   }
   else if (pmessage->m_eusermessage == WM_IME_SELECT)
   {

      //SetInputLanguage();
      ::output_debug_string("\nWM_IME_SELECT");

   }
   else if (pmessage->m_eusermessage == WM_IME_SETCONTEXT)
   {

      //EnableIME();

      ::output_debug_string("\nWM_IME_SETCONTEXT");

   }
   else if (pmessage->m_eusermessage == WM_IME_COMPOSITION)
   {

      if (pmessage->m_lparam == 0)
      {

         ::output_debug_string("\nWM_IME_COMPOSITION Cancellation...");

         if (m_strImeComposition.has_character())
         {

            m_puserinteraction->edit_undo();

            m_strImeComposition.empty();

         }

      }
      else
      {

         ::output_debug_string("\nWM_IME_COMPOSITION " + ::as_string((long long)pusermessage->m_lparam.m_lparam));

         if ((pmessage->m_lparam & GCS_RESULTSTR) != 0)
         {

            ::output_debug_string("\nWM_IME_COMPOSITION GCS_RESULTSTR");

            imm_context imm(m_puserinteraction);

            string strComposition;

            strComposition = imm.get_string(GCS_RESULTSTR);

            if (strComposition.is_empty())
            {

               strComposition = imm.get_string(GCS_RESULTREADSTR);

               ::output_debug_string("\nGCS_RESULTREADSTR \"" + strComposition + "\"");

            }
            else
            {

               ::output_debug_string("\nGCS_RESULTSTR \"" + strComposition + "\"");

            }

            on_text_composition(strComposition);

            //on_text_composition_done();

         }
         else if ((pmessage->m_lparam & GCS_COMPSTR) != 0)
         {

            ::output_debug_string("\nWM_IME_COMPOSITION GCS_COMPSTR");

            imm_context imm(m_puserinteraction);

            string strComposition;

            strComposition = imm.get_string(GCS_COMPSTR);

            wstring wstrComposition;

            wstrComposition = strComposition;

            if (strComposition.is_empty())
            {

               strComposition = imm.get_string(GCS_COMPREADSTR);

               ::output_debug_string("\nGCS_COMPREADSTR \"" + strComposition + "\"");

            }
            else
            {

               ::output_debug_string("\nGCS_COMPSTR \"" + strComposition + "\"");

            }

            on_text_composition(strComposition);

         }

      }

      pusermessage->m_bRet = true;

   }
   else if (pmessage->m_eusermessage == WM_IME_KEYDOWN)
   {

      ::output_debug_string("\nWM_IME_KEYDOWN");

   }
   else if (pmessage->m_eusermessage == WM_IME_ENDCOMPOSITION)
   {

      //::output_debug_string("WM_IME_ENDCOMPOSITION");

      //if (is_text_composition_active())
      {

         if ((pmessage->m_lparam & GCS_RESULTSTR) != 0)
         {

            ::output_debug_string("\nENDCOMPOSITION RESULTSTR");

            imm_context imm(m_puserinteraction);

            string strComposition;

            strComposition = imm.get_string(GCS_RESULTSTR);

            if (strComposition.is_empty())
            {

               strComposition = imm.get_string(GCS_RESULTREADSTR);

               ::output_debug_string("\nGCS_RESULTREADSTR \"" + strComposition + "\"");

            }
            else
            {

               ::output_debug_string("\nGCS_RESULTSTR \"" + strComposition + "\"");

            }

            on_text_composition(strComposition);

            on_text_composition_done();

         }

      }

   }
   else if (pmessage->m_eusermessage == WM_IME_STARTCOMPOSITION)
   {

      ::output_debug_string("\nWM_IME_STARTCOMPOSITION");

      m_bImeCancelling = false;

      set_text_composition_active();

      if (m_strImeComposition.has_character())
      {

         imm_context imm(m_puserinteraction);

         imm.set_string(m_strImeComposition);

      }

      on_text_composition_message(TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION);

      pusermessage->m_bRet = true;

   }
   else if (pmessage->m_eusermessage == WM_IME_NOTIFY)
   {

      if (pusermessage->m_wparam == IMN_CHANGECANDIDATE)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_CHANGECANDIDATE");

         set_text_composition_active();

      }
      else if (pusermessage->m_wparam == IMN_CLOSECANDIDATE)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_CLOSECANDIDATE");

         //set_text_composition_active(false);

         //if (is_text_composition_active())
         //{

         //   if ((pmessage->m_lparam & GCS_RESULTSTR) != 0)
         //   {

         //      ::output_debug_string("\nWM_IME_COMPOSITION Result String... ");

         //      imm_context imm(m_puserinteraction);

         //      string strComposition;

         //      strComposition = imm.get_string(GCS_RESULTSTR);

         //      if (strComposition.is_empty())
         //      {

         //         strComposition = imm.get_string(GCS_RESULTREADSTR);

         //      }

         //      ::output_debug_string("\nWM_IME_COMPOSITION Composite String Length = " + ::as_string(strComposition.length()));

         //      on_text_composition(strComposition);

         //      on_text_composition_done();

         //   }

         //}

      }
      else if (pusermessage->m_wparam == IMN_CLOSESTATUSWINDOW)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_CLOSESTATUSWINDOW");

      }
      else if (pusermessage->m_wparam == IMN_GUIDELINE)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_GUIDELINE");

      }
      else if (pusermessage->m_wparam == IMN_OPENCANDIDATE)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_OPENCANDIDATE");

         //set_text_composition_active();

      }
      else if (pusermessage->m_wparam == IMN_OPENSTATUSWINDOW)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_OPENSTATUSWINDOW");

      }
      else if (pusermessage->m_wparam == IMN_SETCANDIDATEPOS)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETCANDIDATEPOS");

      }
      else if (pusermessage->m_wparam == IMN_SETCOMPOSITIONFONT)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETCOMPOSITIONFONT");

      }
      else if (pusermessage->m_wparam == IMN_SETCOMPOSITIONWINDOW)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETCOMPOSITIONWINDOW");

      }
      else if (pusermessage->m_wparam == IMN_SETCONVERSIONMODE)
      {

         imm_context imm(m_puserinteraction);

         DWORD dwConversion = 0;

         DWORD dwSentence = 0;

         ImmGetConversionStatus(imm, &dwConversion, &dwSentence);

         string str;

         str.formatf("\n" "WM_IME_NOTIFY" " > " "IMN_SETCONVERSIONMODE conversion=%d sentence=%d", dwConversion, dwSentence);

         str += "\n";

         if (dwConversion == IME_CMODE_ALPHANUMERIC)
         {

            str += "alphanumeric mode; ";

         }
         else
         {

            if (dwConversion & IME_CMODE_NATIVE)
            {

               str += "native mode; ";

            }

            if (dwConversion & IME_CMODE_KATAKANA)
            {

               str += "katakana mode; ";

            }
            if (dwConversion & IME_CMODE_LANGUAGE)
            {

               str += "language mode; ";

            }

            if (dwConversion & IME_CMODE_FULLSHAPE)
            {

               str += "full shape mode; ";

            }
            if (dwConversion & IME_CMODE_ROMAN)
            {

               str += "roman mode; ";

            }
            if (dwConversion & IME_CMODE_CHARCODE)
            {

               str += "char code mode; ";

            }
            if (dwConversion & IME_CMODE_HANJACONVERT)
            {

               str += "hanja mode; ";

            }
            if (dwConversion & IME_CMODE_NATIVESYMBOL)
            {

               str += "native symbol mode; ";

            }

         }

         output_debug_string(str);

      }
      else if (pusermessage->m_wparam == IMN_SETOPENSTATUS)
      {

      output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETOPENSTATUS");

      }
      else if (pusermessage->m_wparam == IMN_SETSENTENCEMODE)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETSENTENCEMODE");

      }
      else if (pusermessage->m_wparam == IMN_SETSTATUSWINDOWPOS)
      {

         output_debug_string("\n" "WM_IME_NOTIFY" " > " "IMN_SETSTATUSWINDOWPOS");

      }
      else
      {

         int wparam = (int) pusermessage->m_wparam;

         output_debug_string("\n" "WM_IME_NOTIFY" " > " + ::as_string(wparam) + "    ");

      }

   }

#endif

}


void imm_client::on_message_key_down(::message::message * pmessage)
{

#ifdef WINDOWS_DESKTOP

   auto pkey = pmessage->m_union.m_pkey;

   if (pkey->m_ekey == ::user::e_key_escape)
   {

      if (is_text_composition_active())
      {

         imm_context imm(m_puserinteraction);

         imm.close_candidate();

      }

      if (m_strImeComposition.has_character())
      {

         clear_ime_composition();

         pkey->m_bRet = true;

         return;

      }

   }

#endif

}


void imm_client::on_text_composition(const ::scoped_string & scopedstr)
{

   //text_composition_client::on_text_composition(str);

   m_puserinteraction->on_text_composition(scopedstr);

}



void imm_client::on_text_composition_done()
{

   ::output_debug_string("\non_text_composition_done");
   
   //set_text_composition_active(false);

   //text_composition_client::on_text_composition_done();

   m_puserinteraction->on_text_composition_done();

}


bool imm_client::is_text_composition_active() const
{

   return m_bTextCompositionActive2;

}


void imm_client::set_text_composition_active(bool bActive)
{

   if (bActive)
   {

      if (!m_bTextCompositionActive2)
      {

         m_bTextCompositionActive2 = true;

      }

   }
   else
   {

      if (m_bTextCompositionActive2)
      {

         m_bTextCompositionActive2 = false;

      }

   }

}


string imm_client::get_ime_composition() const
{

   return m_strImeComposition;

}


void imm_client::clear_ime_composition()
{

   m_strImeComposition.empty();

   m_bTextCompositionActive2 = false;

   m_bImeCancelling = true;

   imm_context imm(m_puserinteraction);

   ::ImmNotifyIME(imm, NI_COMPOSITIONSTR, CPS_CANCEL, 0);

   m_puserinteraction->edit_undo();

   m_strImeComposition.empty();


}


int imm_client::on_text_composition_message(int iMessage)
{

#ifdef WINDOWS_DESKTOP

   if (iMessage == TEXT_COMPOSITION_MESSAGE_UPDATE_CARET)
   {

      //character_count iBeg;
      //character_count iEnd;

      //_001GetSel(iBeg, iEnd);

      //int x;
      //int iLine = SelToLineX(iEnd, x);




      //int y = (iLine)* m_iLineHeight - get_context_offset().y();
      //int y2 = y + m_iLineHeight;
      // ::int_point point(x, y);
      //::int_rectangle r;
      //this->rectangle(rectangle);
      //rectangle.left() = x;
      //rectangle.top() = y;
      //rectangle.bottom() = y2;
      //_001ClientToScreen(rectangle);
      //get_wnd()->_001ScreenToClient(rectangle);


      //SetCaretPos(rectangle.left(), rectangle.top());
      //ShowCaret(get_handle());
   }
   else if (iMessage == TEXT_COMPOSITION_MESSAGE_UPDATE_CANDIDATE_WINDOW_POSITION)
   {

      imm_context imm(m_puserinteraction);

      if (!imm)
      {

         return 0;

      }

      ::int_rectangle rectangle;

      m_puserinteraction->get_text_composition_area(rectangle);

      COMPOSITIONFORM compositionform = {};

      compositionform.dwStyle = CFS_FORCE_POSITION;

      compositionform.ptCurrentPos.x = rectangle.top();

      compositionform.ptCurrentPos.y -= 100;

      ::int_rectangle rect2(rectangle);

      rect2.offset_y(-100);

      compositionform.dwStyle = CFS_RECT;

      compositionform.rcArea.left = rect2.left();
      compositionform.rcArea.top = rect2.top();
      compositionform.rcArea.right = rect2.right();
      compositionform.rcArea.bottom = rect2.bottom();

      //copy(com.rcArea, rect2);

      //ShowCaret(get_handle());

      //auto pstyle = get_style(pgraphics);

      //auto pfont = get_font(pstyle);

      //if (pfont)
      //{

      //   LOGFONTW lf = {};

      //   if (pfont->GetLogFont(&lf))
      //   {

      //      if (ImmSetCompositionFontW(imm, &lf))
      //      {

      //         output_debug_string("set ime composition font (Unicode) pos");

      //      }



      //   }

      //}

      if (::ImmSetCompositionWindow(imm, &compositionform))
      {

         output_debug_string("set ime composition window pos");

      }

      CANDIDATEFORM candidateform = {};

      candidateform.dwStyle = CFS_CANDIDATEPOS;

      candidateform.ptCurrentPos.x = rectangle.left();

      candidateform.ptCurrentPos.y = rectangle.bottom();

      if (::ImmSetCandidateWindow(imm, &candidateform))
      {

         output_debug_string("set ime candidate window pos");

      }

      return 1;

   }

#endif

   return 0;

}


#endif




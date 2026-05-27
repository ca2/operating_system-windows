#include "framework.h"
#include "imm_context.h"
#include "acme/prototype/prototype/memory.h"
#include "acme/windowing/window.h"
#include "aura/user/user/interaction.h"


imm_context::imm_context(::user::interaction * pinteraction) :
   m_pinteraction(pinteraction)
{

   auto hwnd = ::as_HWND(m_pinteraction->m_pacmewindowingwindow->operating_system_window());

   m_himc = ImmGetContext(hwnd);

}


imm_context::~imm_context()
{

   auto hwnd = ::as_HWND(m_pinteraction->m_pacmewindowingwindow->operating_system_window());

   ImmReleaseContext(hwnd, m_himc);

}



bool imm_context::close()
{

   return ImmSetOpenStatus(m_himc, false) != false;

}


bool imm_context::is_opened() const
{

   return ImmGetOpenStatus(m_himc) != false;

}


bool imm_context::close_candidate(::collection::index iIndex)
{

   return ImmNotifyIME(m_himc, NI_CLOSECANDIDATE, 0, (::u32)iIndex) != false;

}


string imm_context::get_string(::i32 iStr)
{

   ::i32 iLen = ImmGetCompositionStringW(m_himc, iStr, nullptr, 0);

   wstring wstr;

   unichar * point = wstr.get_buffer(iLen);

   ImmGetCompositionStringW(m_himc, iStr, point, iLen);

   wstr.release_buffer();

   return wstr;

}


void imm_context::set_string(const scoped_string & str, ::i32 iStr)
{

   wstring wstr(str);

   //::i32 iLen = 
   
   ImmSetCompositionStringW(m_himc, iStr, (LPVOID) wstr.c_str(), (DWORD) wstr.length(),nullptr, 0);

   //return ::success;

}

string imm_context::_get_candidate(::i32 iList)
{

   memory mem;

   ::u32 dwCount = 0;

   ::u32 dwSize = ImmGetCandidateListW(m_himc, iList, 0, 0);

   if (dwSize == 0)
   {

      ::u32 dw = GetLastError();

      output_debug_string("error " + ::as_string(dw));

   }

   mem.set_size(dwSize);

   LPCANDIDATELIST pc = (LPCANDIDATELIST)mem.data();

   if (::is_null(pc))
   {

      return "";

   }

   ImmGetCandidateListW(m_himc, iList, pc, (::u32)mem.size());

   ::i32 iTest = pc->dwOffset[0];

   auto iTest2 = (::u8 *)&pc->dwOffset[pc->dwCount] - (::u8 *)pc;

   unichar * pwsz = (unichar *)(mem.data() + pc->dwOffset[pc->dwSelection]);

   return pwsz;

}


string imm_context::get_candidate()
{

   for (::collection::index i = 3; i >= 0; i--)
   {

      string str = _get_candidate((::i32)i);

      if (str.has_character())
      {

         return str;

      }

   }

   return "";

}





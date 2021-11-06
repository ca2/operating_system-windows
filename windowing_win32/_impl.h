#pragma once


namespace windowing_win32
{


   template < typename PRED >
   bool windowing::_top_level_contains_predicate(PRED pred)
   {

      top_level_boolean_predicate<PRED> boolean_predicate(pred);

      EnumWindows(&top_level_boolean_predicate<PRED>::EnumWindowsProc, (LPARAM)&boolean_predicate);

      return boolean_predicate.m_hwnd != nullptr;

   }


   template < typename PREDICATE >
   bool windowing::_top_level_contains_bool_member(PREDICATE predicate)
   {

      top_level_boolean_predicate<PREDICATE> boolean_predicate(predicate);

      EnumWindows(&top_level_boolean_predicate<PREDICATE>::EnumWindowsProc, (LPARAM)&boolean_predicate);

      return boolean_predicate.m_hwnd != nullptr;

   }


} // namespace windowing_win32






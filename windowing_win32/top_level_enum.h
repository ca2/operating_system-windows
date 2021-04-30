#pragma once


namespace windowing_win32
{


   template < typename PRED >
   class top_level_boolean_predicate
   {
   public:


      PRED     m_predicate;
      HWND     m_hwnd;


      top_level_boolean_predicate(PRED pred, HWND hwndDefault = nullptr) : m_predicate(pred), m_hwnd(hwndDefault) {}


      bool found(oswindow oswindow)
      {

         return m_predicate(oswindow);

      }


#ifdef WINDOWS_DESKTOP

      static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
      {

         top_level_boolean_predicate * ppred = (top_level_boolean_predicate *)lParam;

         if (ppred->found((oswindow) hwnd))
         {

            ppred->m_hwnd = hwnd;

            return false;

         }

         return true;

      }

#endif

   };





   /// from top to bottom
   class CLASS_DECL_WINDOWING_WIN32 top_level_enum
   {
   public:


      __pointer(hwnd_array)         m_phwnda;
      bool                          m_bVisible;


      top_level_enum(bool bDestkop = true, bool bVisible = true);
      ~top_level_enum();


      /// from top to bottom
      static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);


   };


} // namespace windowing_win32




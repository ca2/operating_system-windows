#pragma once


namespace windowing_win32
{


   class CLASS_DECL_WINDOWING_WIN32 print_window :
      virtual public ::object
   {
   public:


      manual_reset_happening m_happening;
      oswindow m_pacmewindowingwindow;
      HDC m_hdc;


      print_window(::particle * pparticle, HWND hwnd, HDC hdc, class ::time tickTimeout) :
         ::object(pobject)
      {

         m_pacmewindowingwindow = oswindow;

         m_hdc = hdc;

         start();

         if (m_happening.wait(tickTimeout).timeout())
         {

            information() << "print_window::time_out";

         }

      }


      virtual void     run() override
      {

         try
         {

            ::PrintWindow(m_pacmewindowingwindow, m_hdc, 0);

         }
         catch (...)
         {

         }

         m_happening.set_happening();

         return ::success;

      }

   };


}  // namespace windowing_win32




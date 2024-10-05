//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
// Merged from windowing_system_win32 to
//     nano_user_win32 by camilo on 2024-10-05 10:17 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/windowing/windowing_base.h"


namespace win32
{
   namespace nano
   {

      namespace user
      {

         class CLASS_DECL_NANO_USER_WIN32 windowing :
            virtual public ::windowing::windowing_base
         {
         public:



            windowing_system();
            ~windowing_system() override;

            ::e_status defer_initialize_windowing_system() override;
            ::e_status initialize_windowing_system() override;
            void * get_display() override;
            void sync(const ::procedure & procedure) override;
            void async(const ::procedure & procedure) override;
            void display_error_trap_push(int i) override;
            void display_error_trap_pop_ignored(int i) override;

            //   ::e_status x11_initialize() override;
            //   void * x11_get_display() override;
            //   void x11_sync(const ::procedure & procedure) override;
            //   void x11_async(const ::procedure & procedure) override;
            //   void x11_display_error_trap_push(int i) override;
            //   void x11_display_error_trap_pop_ignored(int i) override;

            void set_dark_mode(bool bDarkMode) override;


            bool dark_mode() override;
            void fetch_system_background_color() override;


            virtual bool _win32_registry_windows_dark_mode_for_app();
            virtual bool _win32_registry_windows_dark_mode_for_system();
            virtual bool _win32_registry_windows_darkness();


            virtual void _set_system_dark_mode1(bool bSet = true);
            virtual void _set_app_dark_mode1(bool bSet = true);

            void on_start_system() override;


            void windowing_system_post_quit() override;


         };

      }//namespace user

   }//namespace nano

} // namespace win32




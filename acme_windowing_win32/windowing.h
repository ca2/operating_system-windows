//
// Created by camilo on 2024-05-26 21:59 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "acme/operating_system/windows/windowing.h"


namespace win32
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_WIN32 windowing :
            virtual public ::windows::windowing
         {
         public:

            
            windowing();
            ~windowing() override;


            //::e_status defer_initialize_windowing() override;
            void initialize_windowing() override;
            //void * get_display() override;
            ::acme::windowing::display * acme_display() override;
            void _main_send(const ::procedure & procedure) override;
            void _main_post(const ::procedure & procedure) override;
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

            ::color::color get_operating_system_background_color() override;

            void on_start_system() override;

            void set_finish() override;
            void kick_idle() override;

            void windowing_post_quit() override;


            void windowing_application_main_loop() override;


            void show(::particle_pointer pparticle) override;


            //void _do_tasks() override;

            bool handle_messages() override;


         };


      } // namespace windowing


   } // namespace acme


} // namespace win32




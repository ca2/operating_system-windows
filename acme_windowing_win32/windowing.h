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

            ::windows::window_class m_windowclassDefault;
            ::windows::window_class m_windowclassAcmeNano;
            ::windows::window_class m_windowclassComHost;


            string_map < ::windows::window_class > m_mapWindowClass;

            
            windowing();
            ~windowing() override;


            //::e_status defer_initialize_windowing() override;
            void initialize_windowing() override;
            //void * get_display() override;
            ::acme::windowing::display * acme_display() override;
            void main_send(const ::procedure & procedure) override;
            void main_post(const ::procedure & procedure) override;
            void user_send(const ::procedure & procedure) override;
            void user_post(const ::procedure & procedure) override;
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

            ::windows::window_class _custom_window_class(const scoped_string &scopedstrClassName, void *pHICON_Big, void *pHICON_Small) override;
            virtual ::windows::window_class _register_custom_window_class(const scoped_string & scopedstrClassName, void * pHICON_Big, void * pHICON_Small);

            ::windows::window_class _default_window_class() override;
            virtual void _register_default_window_class();
            virtual void _register_default_window_class(hinstance hinstance);

            ::windows::window_class _acme_nano_window_class() override;
            virtual void _register_acme_nano_window_class();
            virtual void _register_acme_nano_window_class(hinstance hinstance);

            ::windows::window_class _com_host_window_class() override;
            virtual void _register_com_host_window_class();
            virtual void _register_com_host_window_class(hinstance hinstance);


            virtual bool _win32_registry_windows_dark_mode_for_app();
            virtual bool _win32_registry_windows_dark_mode_for_system();
            virtual bool _win32_registry_windows_darkness();


            virtual void _set_system_dark_mode1(bool bSet = true);
            virtual void _set_app_dark_mode1(bool bSet = true);

            ::color::color get_operating_system_background_color() override;

            void windowing_application_on_system_start() override;

            void set_finish() override;
            void kick_idle() override;

            void windowing_post_quit() override;


            void run() override;


            void show(::particle_pointer pparticle) override;


            //void _do_tasks() override;

            bool handle_messages() override;

            
            ::pointer < ::user::activation_token > get_user_activation_token() override;


         };


      } // namespace windowing


   } // namespace acme


} // namespace win32




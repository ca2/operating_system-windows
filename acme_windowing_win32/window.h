// Created by camilo on 2021-01-21 05:05 PM <3ThomasBorregaardSorensen
#pragma once


#include "acme/windowing/window.h"
//#include "acme/windowing/window_base.h"
#include "acme/operating_system/windows/window.h"
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"


namespace win32
{


   namespace acme
   {


      namespace windowing
      {


         class CLASS_DECL_ACME_WINDOWING_WIN32 window :
            virtual public ::acme::windowing::window,
            virtual public ::windows::window
         {
         public:


            bool m_bNcActive;
            //CreatableFromBase(window, ::micro::window_implementation);
            //bool m_bSizeMoveMode;
            //HWND m_hwnd;
            //HMENU m_hmenuSystem;
            //bool m_bDestroy;
      //      HFONT m_hfont;
      //      color32_t m_crText;
      //      color32_t m_crFocus;
      //      color32_t m_crWindow;
      //      string m_strTitle;
      //      bool m_bNcActive;

      //      rectangle_i32 m_rectangle;
      //      rectangle_i32 m_rectangleX;
      //
      //      pointer_array < ::micro::child > m_childa;
      //      ::atom m_atomLeftButtonDown;
      //      ::atom m_atomLeftButtonUp;
      //      //::atom                             m_atomResult;
      //      ::pointer<::micro::child>m_pchildFocus;
            ::task_pointer       m_ptask;

            ::pointer < ::nano::graphics::device > m_pnanodevice;

            window();

            ~window() override;

            void create_window() override;

            void _create_window() override;

            void destroy_window() override;

            void show_window() override;

            void hide_window() override;

            virtual void _draw(HDC hdc);

            //void on_draw(::nano::graphics::device * pnanodevice) override;

            //void on_char(int iChar) override;

            //bool is_active() override;

            //virtual void draw_children(::nano::graphics::device * pnanodevice);

            //void delete_drawing_objects() override;

            //bool get_dark_mode() override;

            //void create_drawing_objects() override;

            //void update_drawing_objects() override;

            //::micro::child * on_hit_test(const ::point_i32 & point, ::user::e_zorder ezorder) override;

            //void add_child(::micro::child* pchild) override;

            //::payload get_result() override;

            //void on_mouse_move(::user::mouse* pmouse) override;

            //void on_left_button_down(::user::mouse* pmouse) override;

            //void on_left_button_up(::user::mouse* pmouse) override;

            //void on_click(const ::payload& payload, ::user::mouse* pmouse) override;

            //void on_right_button_down(::user::mouse* pmouse) override;

            //void on_right_button_up(::user::mouse* pmouse) override;

            //void on_right_click(const ::payload& payload, ::user::mouse* pmouse) override;

            virtual LRESULT window_procedure(UINT message, WPARAM wparam, LPARAM lparam);

            void set_position(const ::point_i32& point) override;

            //void _destroy_window();

            void destroy() override;

            void redraw() override;


            bool _is_window() override;

            //::point_i32 try_absolute_mouse_position(const ::point_i32& point) override;



            //void get_client_rectangle(::rectangle_i32& rectangle) override;

            ::rectangle_i32 get_window_rectangle() override;

            void set_capture() override;

            bool has_capture() override;

            void release_capture() override;

            void set_cursor(enum_cursor ecursor) override;

            static bool _is_light_theme();


            //::size_i32 get_main_screen_size() override;


            void _user_post(const ::procedure& procedure) override;


            virtual void implementation_message_loop_step();

            void defer_show_system_menu(::user::mouse * pmouse) override;


            /// ::user::primitive_impl



         };


         //CLASS_DECL_ACME void process_messages(bool bWait = false);


      } // namespace windowing

      
   } // namespace acme


} // namespace win32



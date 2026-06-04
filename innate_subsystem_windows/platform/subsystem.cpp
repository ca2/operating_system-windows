//
// Created by camilo on 2026-04-06 10:54 <3ThomasBorregaardSørensen!!
//
#include "framework.h"
#include "subsystem.h"
#include "acme/platform/user_interaction_sink.h"
#include "acme/operating_system/windows/user.h"
#include "acme/operating_system/windows/windows.h"
#include "innate_subsystem_windows/gui/CommonControlsEx.h"
#include "operating_system-windows/gdiplus_library/_.h"


namespace innate_subsystem_windows
{


    subsystem::subsystem()
    {

       initialize_gdiplus();

    }


    subsystem::~subsystem()
    {


    }

    //
    // ::subsystem::string_table * subsystem::string_table()
    // {
    //
    //    if (!m_pstringtable)
    //    {
    //
    //       constructø(m_pstringtable);
    //
    //    }
    //
    //    return m_pstringtable;
    //
    // }
    //
    //
    //
    // ::subsystem::resource_loader * subsystem::resource_loader()
    // {
    //
    //    if (!m_presourceloader)
    //    {
    //
    //       constructø(m_presourceloader);
    //
    //    }
    //
    //    return m_presourceloader;
    //
    // }
    //
    //
    //
    // ::subsystem::Registry * subsystem::registry()
    // {
    //
    //    if (!m_pregistry)
    //    {
    //
    //       construct_newø(m_pregistry);
    //
    //    }
    //
    //    return m_pregistry;
    //
    // }
    //
    //
    // ::subsystem::Shell * subsystem::shell()
    // {
    //
    //    if (!m_pshell)
    //    {
    //
    //       constructø(m_pshell);
    //
    //    }
    //
    //    return m_pshell;
    //
    // }
    //
    // ::pointer < ::subsystem::SecurityIdentifier > subsystem::createSidFromString(const ::scoped_string & scopedstr)
    // {
    //
    //    return nullptr;
    //
    // }


    ::enum_dialog_result subsystem::message_box(
                    const ::user_interaction_sink & userinteractionsink,
                    const ::scoped_string & scopedstrMessage,
                    const ::scoped_string & scopedstrCaption,
                    const ::user::e_message_box & emessagebox)
    {

        auto operatingsystemwindow = userinteractionsink.best_effort_operating_system_window();

        auto hwnd = ::as_HWND(operatingsystemwindow);

        auto iResult = ::MessageBox(hwnd, ::wstring(scopedstrMessage), ::wstring(scopedstrCaption), windows::message_box_to_windows_message_box(emessagebox));

       auto edialogresult = windows::windows_message_box_result_to_dialog_result(iResult);

        return edialogresult;

    }


    ::user::e_key subsystem::virtual_key_code_to_user_key(::i32 iVirtualKeyCode)
    {
        return ::windows::virtual_key_code_to_user_key(iVirtualKeyCode);
        //switch (iVirtualKeyCode)
        //{
          //  case VK_RETURN:


        //}
    }


   void subsystem::initializeInnateSubsystemControls()
    {

       CommonControlsEx::init();
    }



}//namespace subsystem




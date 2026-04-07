// Created by camilo on 2026-04-07 08:42 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "SystemMetrics.h"


namespace windows
{
    namespace innate_subsystem_win32
    {

        SystemMetrics::SystemMetrics()
        {



        }


        SystemMetrics::~SystemMetrics()
        {


        }

        ::int_size SystemMetrics::get_small_icon_size_in_pixels()
        {
            int iSmallIconWidthInPixels = ::GetSystemMetrics(SM_CXSMICON);
            int iSmallIconHeightInPixels = ::GetSystemMetrics(SM_CYSMICON);
            return {iSmallIconWidthInPixels, iSmallIconHeightInPixels};
        }



    } // namespace innate_subsystem_win32
} // namespace windows
// Created by camilo on 2026-04-07 08:44 <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/innate_subsystem_win32/SystemMetrics.h"


namespace windows
{
    namespace innate_subsystem_win32
    {

        class CLASS_DECL_APEX SystemMetrics :
            virtual public ::subsystem::implementation < ::innate_subsystem_win32::SystemMetricsInterface>
        {
            SystemMetrics();

            ~SystemMetrics() override;

            ::int_size  get_small_icon_size_in_pixels() override;
        };



    } // namespace innate_subsystem_win32
} // namespace windows
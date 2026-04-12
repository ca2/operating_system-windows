// Created by camilo on 2026-04-07 08:44 <3ThomasBorregaardSørensen!!
#pragma once


#include "subsystem_apex/SystemMetrics.h"


 namespace innate_subsystem_win32
 {


    class CLASS_DECL_INNATE_SUBSYSTEM_WIN32 SystemMetrics :
         virtual public ::subsystem::implementation < ::subsystem_apex::SystemMetricsInterface>
    {
    public:

      SystemMetrics();

      ~SystemMetrics() override;

      ::int_size  get_small_icon_size_in_pixels() override;

    };


} // namespace innate_subsystem_win32

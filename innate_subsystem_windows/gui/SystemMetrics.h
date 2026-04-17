// Created by camilo on 2026-04-07 08:44 <3ThomasBorregaardSørensen!!
#pragma once


#include "innate_subsystem/gui/SystemMetrics.h"


 namespace innate_subsystem_windows
 {


    class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS SystemMetrics :
         virtual public Implementation < ::innate_subsystem::SystemMetricsInterface>
    {
    public:

      SystemMetrics();

      ~SystemMetrics() override;

      ::int_size  get_small_icon_size_in_pixels() override;

    };


} // namespace innate_subsystem_windows

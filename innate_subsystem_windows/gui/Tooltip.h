// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//
// Adapted by camilo on beginning of 2026-April <3ThomasBorregaardSorensen!!
//
#pragma once
//#define _TOOLTIP_H_

//#include "util/CommonHeader.h"
#include "innate_subsystem/gui/Tooltip.h"
#include "innate_subsystem_windows/gui/Control.h"

//
// Abstract tooltip class
//

namespace innate_subsystem_windows
{


    class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS Tooltip :
    virtual public Implementation<::innate_subsystem::TooltipInterface, Control>
    {
    public:
        Tooltip();
        ~Tooltip() override;

        virtual void showTooltip(::innate_subsystem::ControlInterface * pcontrol) override;

        virtual void setText(const char *text) override;
        virtual void setTitle(const char *caption) override;

        virtual ::string getText() override;
        virtual ::string getTitle() const override;

        virtual void setIconType(::innate_subsystem::enum_tooltip_icon etooltipicon) override;
        virtual ::innate_subsystem::enum_tooltip_icon getIconType() const override;
    };

    //#endif

}// namespace innate_subsystem_windows




// Copyright (C) 2008,2009,2010,2011,2012 GlavSoft LLC.
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

#pragma once
//#define __TEXTBOX_H_

#include "innate_subsystem/gui/TextBox.h"
#include "innate_subsystem_windows/_common_header.h"
#include "innate_subsystem_windows/gui/Control.h"


namespace innate_subsystem_windows
{

   class CLASS_DECL_INNATE_SUBSYSTEM_WINDOWS TextBox : //public Control
      virtual public window_implementation<::innate_subsystem::TextBoxInterface, Control>
      //, virtual public Control
   {
   public:


      TextBox();
      ~TextBox();
    //public:

        //
        // Text limit
        //

      virtual character_count getTextLengthLimit() override;
      virtual void setTextLengthLimit(character_count limit) override;

        //
        // Methods for multiline textboxes
        //

        virtual int getCurrentLineIndex() override;
        virtual int getLineCount() override;

        //
        // Get / set caret position
        //

        virtual int getCaretPos() override;
        virtual void setCaretPos(int h, int v) override;

        //
        // Text selection
        //

        virtual void selectText(character_count startPos, character_count endPos) override;

        //
        // Tooltip methods
        //

        virtual void showBalloonTip(innate_subsystem::TooltipInterface *tip) override;
    };


} // namespace innate_subsystem_windows




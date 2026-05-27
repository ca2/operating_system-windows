// Copyright (C) 2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the T i g h t V N C software.  Please visit our Web site:
//
//                       http://www.t i g h t v n c.com/
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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "subsystem/node/EmulatedAnonymousPipeFactory.h"
//#include "subsystem_windows/node/NamedPipe.h"
#include "subsystem_windows/_common_header.h"
//#include "log_writer/LogWriter.h"


namespace subsystem_windows
{

   // The EmulatedAnonymousPipeFactory class generates a chanel based on named pipe.
   // This is similar to anonymous pipe generation.
   class CLASS_DECL_SUBSYSTEM_WINDOWS EmulatedAnonymousPipeFactory :
   virtual public Implementation<subsystem::EmulatedAnonymousPipeFactoryInterface>
   {
   public:


      //EmulatedAnonymousPipeFactory(::u32 bufferSize, LogWriter *log);
      EmulatedAnonymousPipeFactory();
      ~EmulatedAnonymousPipeFactory() override;


      void initialize_emulated_anonymous_pipe_factory(::u32 bufferSize, ::subsystem::LogWriter *log) override;

      void generatePipes(::pointer < ::subsystem::NamedPipeInterface > & serverPipe, bool serverInheritable,
                         ::pointer < ::subsystem::NamedPipeInterface > & clientPipe, bool clientInheritable) override;

      //private:
      ::string getUniqPipeName() override;

      ::pointer < ::subsystem::LogWriter  > m_log;
      ::u32 m_bufferSize = 0;
   };

   //// __EMULATEDANONYMOUSPIPEFACTORY_H__
} // namespace subsystem_windows
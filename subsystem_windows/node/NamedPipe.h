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
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

#pragma once


#include "acme/input_output/Channel.h"
#include "subsystem/node/NamedPipe.h"
#include "subsystem_windows/node/Pipe.h"
#include "subsystem_windows/node/WindowsEvent.h"


namespace subsystem_windows
{
   /**
    * NamedPipe transport.
    *
    * @author yuri, enikey.
    */
   class CLASS_DECL_SUBSYSTEM_WINDOWS NamedPipe :
      virtual public implementation < ::subsystem::NamedPipeInterface, ::subsystem::Pipe >
   {
   public:
      /**
       * Creates pipe transport.
       */
      NamedPipe();
      /**
       * Destroys instance.
       */
      ~NamedPipe();

      void initialize_pipe(unsigned int maxPortionSize);

      void initialize_named_pipe(::subsystem::FileInterface* pfilePipe, unsigned int maxPortionSize, bool asServer);

      // bool is_subsystem_implementation(void) const override
      // {
      //
      //    return ::subsystem::NamedPipe::is_subsystem_implementation();
      //
      // }
      // bool is_subsystem_composite(void) const override
      // {
      //
      //    return ::subsystem::NamedPipe::is_subsystem_composite();
      //
      // }

      unsigned int getMaxPortionSize() override
      {

         return Pipe::getMaxPortionSize();

      }

      /**
       * Closes transport.
       *
       * @throws ::subsystem::Exception on fail.
       */
      void close();

      /**
       * Reads data from pipe.
       * Implemented from Channel interface.
       * @param buffer buffer to receive data.
       * @param len count of bytes to read.
       * @throws ::io_exception on io error.
       */
      memsize read(void *buffer, memsize len);

      /**
       * Writes data to pipe.
       * Implemented from Channel interface.
       * @param buffer buffer with data to write.
       * @param len count of bytes to write.
       * @throws ::io_exception on io error.
       */
      memsize defer_write(const void *buffer, memsize len);

      memsize available();

      virtual ::subsystem::FileInterface * getFile() const;

   //private:
      void checkPipeFile();

      ::pointer < ::subsystem::File > m_pfilePipe;
      critical_section m_criticalsectionPipe;
      ::string m_pipeName;

      WindowsEvent m_readEvent;
      WindowsEvent m_writeEvent;
      bool m_asServer;
   };


} // namespace subsystem_windows





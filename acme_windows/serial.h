/*!
 * \file serial/impl/windows.h
 * \author  William Woodall <wjwwood@gmail.com>
 * \author  John Harrison <ash@greaterthaninfinity.com>
 * \version 0.1
 *
 * \section LICENSE
 *
 * The MIT License
 *
 * Copyright (c) 2012 William Woodall, John Harrison
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, topic to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * \section DESCRIPTION
 *
 * This provides a windows implementation of the serial class interface.
 *
 */
#pragma once


#include "acme/platform/serial.h"
#include "acme/prototype/prototype/pointer.h"


#include "acme/_operating_system.h"


namespace acme_windows
{

   //using std::string;
   //using std::wstring;
   //using std::invalid_argument;

   //using serial::serial_exception;
   //using serial::io_exception;

   class CLASS_DECL_ACME_WINDOWS serial :
      virtual public ::serial::serial
   {
   public:


      //__creatable_from_base(serial, ::serial::serial);


      bool        m_bReadTimeout;

      //serial_impl (
      //            const string &port,
      //            unsigned long baudrate,
      //            enum_byte_size ebytesize,
      //            enum_parity eparity,
      //            enum_stop_bit estopbit,
      //            enum_flow_control eflowcontrol);

      serial();
      virtual ~serial ();


      virtual void initialize_serial(
         const string& port = "",
         unsigned int baudrate = 9600,
         ::serial::timeout timeout = nullptr,
         ::serial::enum_byte_size ebytesize = ::serial::e_byte_size_eight,
         ::serial::enum_parity eparity = ::serial::e_parity_none,
         ::serial::enum_stop_bit estopbit = ::serial::e_stop_bit_one,
         ::serial::enum_flow_control eflowcontrol = ::serial::e_flow_control_none) override;


      virtual void open () override;

      virtual void close () override;

      virtual bool isOpen () const override;

      virtual size_t available () override;

      virtual bool waitReadable (class ::time timeout);

      virtual void waitByteTimes (size_t count) override;

      virtual size_t _read (unsigned char *buf, size_t size = 1) override;

      virtual size_t _write (const unsigned char *data, size_t length) override;

      virtual void _flush () override;

      virtual void _flushInput () override;

      virtual void _flushOutput () override;

      virtual void sendBreak (int time) override;

      virtual void setBreak (bool level) override;

      virtual void setRTS (bool level) override;

      virtual void setDTR (bool level) override;

      virtual bool waitForChange () override;

      virtual bool getCTS () override;

      virtual bool getDSR () override;

      virtual bool getRI () override;

      virtual bool getCD () override;

      virtual void setPort (const string &port) override;

      virtual string getPort () const override;

      virtual void set_timeout (const ::serial::timeout &timeout) override ;

      virtual ::serial::timeout getTimeout () const override;

      virtual void setBaudrate (unsigned int baudrate) override;

      virtual unsigned int getBaudrate () const override;

      virtual void setBytesize (::serial::enum_byte_size ebytesize) override;

      virtual ::serial::enum_byte_size getBytesize () const override;

      virtual void setParity (::serial::enum_parity eparity) override;

      virtual ::serial::enum_parity getParity () const override;

      virtual void setStopbits (::serial::enum_stop_bit estopbit) override;

      virtual ::serial::enum_stop_bit getStopbits () const override;

      virtual void setFlowcontrol (::serial::enum_flow_control eflowcontrol) override;

      virtual ::serial::enum_flow_control getFlowcontrol () const override;

      //virtual void readLock () override;

      //virtual void readUnlock () override;

      //virtual void writeLock () override;

      //virtual void writeUnlock () override;


      ::particle * read_synchronization() override;
      ::particle * write_synchronization() override;


      virtual size_t readline(string &buffer, size_t size = 65536, string eol = "\n") override;

   protected:

      virtual void reconfigurePort ();

   private:

      wstring           m_wstrPort;               // Path to the file descriptor
      HANDLE            m_hFile;

      bool              m_bOpened;

      ::serial::timeout           m_timeout;           // timeout for read operations
      unsigned long     m_ulBaudrate;    // Baudrate
      unsigned int          m_uiByteTimeNs;     // Nanoseconds to transmit/receive a single unsigned char

      ::serial::enum_parity          m_eparity;           // Parity
      ::serial::enum_byte_size        m_ebytesize;       // Size of the bytes
      ::serial::enum_stop_bit        m_estopbit;       // Stop Bits
      ::serial::enum_flow_control     m_eflowcontrol; // Flow Control

      // Mutex used to lock the read functions
      ::pointer <::mutex >              m_pmutexRead;
      // Mutex used to lock the write functions
      ::pointer < ::mutex>              m_pmutexWrite;
      //HANDLE            m_hMutexWrite;
   };


} // namespace acme_windows




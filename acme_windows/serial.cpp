#include "framework.h"
#include "serial.h"
#include "acme/parallelization/mutex.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/uint64_muldiv.h"
//#include "acme/prototype/time/integral/operator.h"


// namespace windows
// {

   
//    CLASS_DECL_ACME bool alternate_path(::windows_path & windowspath);


// } // namespace windows


/* Copyright 2012 William Woodall and John Harrison */


//using serial::serial;
//using serial::time_out;
//using enum_byte_size;
//using enum_parity;
//using enum_stop_bit;
//using enum_flow_control;
//using serial::serial_exception;
//using serial::port_not_opened_exception;
//using serial::io_exception;
//

namespace acme_windows
{


   // inline windows_path _prefix_port_if_needed(const windows_path& windowspathInput)
   // {

   //    auto windowspath = windowspathInput;

   //    ::windows::get_alternate_path(windowspath);

   //    return windowspath;

   // }
   


      serial::serial()
      {


      }

   void serial::initialize_serial(
      const string& port,
      unsigned int baudrate,
      ::serial::timeout timeout,
      ::serial::enum_byte_size ebytesize,
      ::serial::enum_parity eparity, ::serial::enum_stop_bit estopbit,
      ::serial::enum_flow_control eflowcontrol)
   {

      m_wstrPort = port;
      m_hFile = INVALID_HANDLE_VALUE;
      m_bOpened = false;
      m_ulBaudrate = baudrate;
      m_eparity = eparity;
      m_ebytesize = ebytesize;
      m_estopbit = estopbit;
      m_eflowcontrol = eflowcontrol;

      if (m_wstrPort.has_character())
      {

         open();

      }

      //m_hMutexRead = CreateMutex(nullptr, false, nullptr);
      //m_hMutexWrite = CreateMutex(nullptr, false, nullptr);

      //return ::success;

   }

   serial::~serial()
   {
      this->close();
      //CloseHandle(m_hMutexRead);
      //CloseHandle(m_hMutexWrite);
   }

   void serial::open()
   {
      if (m_wstrPort.is_empty())
      {
         throw ::exception(error_bad_argument, "Empty port is invalid.");
      }
      if (m_bOpened == true)
      {
         throw ::exception(error_serial, "serial port already open.");
      }

      // See: https://github.com/wjwwood/serial/issues/84
      wstring port_with_prefix = m_wstrPort.defer_prefixed(L"\\\\.\\");

      m_hFile = CreateFileW(port_with_prefix,
         GENERIC_READ | GENERIC_WRITE,
         0,
         0,
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         0);

      if (m_hFile == INVALID_HANDLE_VALUE)
      {

         DWORD dwLastError = ::GetLastError();

         string str;

         switch (dwLastError)
         {
         case ERROR_FILE_NOT_FOUND:
            // Use this->getPort to convert to a std::string
            str.formatf("Specified port, %d, does not exist.", this->getPort());
            throw ::exception(error_serial, str);
         default:
            str.formatf("Unknown error opening the serial port: %d", dwLastError);
            throw ::exception(error_serial, str);
         }
      }

      reconfigurePort();

      m_bOpened = true;

   }


   void serial::reconfigurePort()
   {
      if (m_hFile == INVALID_HANDLE_VALUE)
      {
         // Can only operate on a valid file descriptor
         throw ::exception(error_serial, "Invalid file descriptor, is the serial port open?");
      }

      DCB dcbSerialParams = { };

      dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

      if (!GetCommState(m_hFile, &dcbSerialParams))
      {
         //error getting state
         throw ::exception(error_serial, "Error getting the serial port state.");
      }

      // setup baud rate
      switch (m_ulBaudrate)
      {
#ifdef CBR_0
      case 0:
         dcbSerialParams.BaudRate = CBR_0;
         break;
#endif
#ifdef CBR_50
      case 50:
         dcbSerialParams.BaudRate = CBR_50;
         break;
#endif
#ifdef CBR_75
      case 75:
         dcbSerialParams.BaudRate = CBR_75;
         break;
#endif
#ifdef CBR_110
      case 110:
         dcbSerialParams.BaudRate = CBR_110;
         break;
#endif
#ifdef CBR_134
      case 134:
         dcbSerialParams.BaudRate = CBR_134;
         break;
#endif
#ifdef CBR_150
      case 150:
         dcbSerialParams.BaudRate = CBR_150;
         break;
#endif
#ifdef CBR_200
      case 200:
         dcbSerialParams.BaudRate = CBR_200;
         break;
#endif
#ifdef CBR_300
      case 300:
         dcbSerialParams.BaudRate = CBR_300;
         break;
#endif
#ifdef CBR_600
      case 600:
         dcbSerialParams.BaudRate = CBR_600;
         break;
#endif
#ifdef CBR_1200
      case 1200:
         dcbSerialParams.BaudRate = CBR_1200;
         break;
#endif
#ifdef CBR_1800
      case 1800:
         dcbSerialParams.BaudRate = CBR_1800;
         break;
#endif
#ifdef CBR_2400
      case 2400:
         dcbSerialParams.BaudRate = CBR_2400;
         break;
#endif
#ifdef CBR_4800
      case 4800:
         dcbSerialParams.BaudRate = CBR_4800;
         break;
#endif
#ifdef CBR_7200
      case 7200:
         dcbSerialParams.BaudRate = CBR_7200;
         break;
#endif
#ifdef CBR_9600
      case 9600:
         dcbSerialParams.BaudRate = CBR_9600;
         break;
#endif
#ifdef CBR_14400
      case 14400:
         dcbSerialParams.BaudRate = CBR_14400;
         break;
#endif
#ifdef CBR_19200
      case 19200:
         dcbSerialParams.BaudRate = CBR_19200;
         break;
#endif
#ifdef CBR_28800
      case 28800:
         dcbSerialParams.BaudRate = CBR_28800;
         break;
#endif
#ifdef CBR_57600
      case 57600:
         dcbSerialParams.BaudRate = CBR_57600;
         break;
#endif
#ifdef CBR_76800
      case 76800:
         dcbSerialParams.BaudRate = CBR_76800;
         break;
#endif
#ifdef CBR_38400
      case 38400:
         dcbSerialParams.BaudRate = CBR_38400;
         break;
#endif
#ifdef CBR_115200
      case 115200:
         dcbSerialParams.BaudRate = CBR_115200;
         break;
#endif
#ifdef CBR_128000
      case 128000:
         dcbSerialParams.BaudRate = CBR_128000;
         break;
#endif
#ifdef CBR_153600
      case 153600:
         dcbSerialParams.BaudRate = CBR_153600;
         break;
#endif
#ifdef CBR_230400
      case 230400:
         dcbSerialParams.BaudRate = CBR_230400;
         break;
#endif
#ifdef CBR_256000
      case 256000:
         dcbSerialParams.BaudRate = CBR_256000;
         break;
#endif
#ifdef CBR_460800
      case 460800:
         dcbSerialParams.BaudRate = CBR_460800;
         break;
#endif
#ifdef CBR_921600
      case 921600:
         dcbSerialParams.BaudRate = CBR_921600;
         break;
#endif
      default:
         // Try to blindly assign it
         dcbSerialParams.BaudRate = m_ulBaudrate;
      }

      // setup char len
      if (m_ebytesize == ::serial::e_byte_size_eight)
         dcbSerialParams.ByteSize = 8;
      else if (m_ebytesize == ::serial::e_byte_size_seven)
         dcbSerialParams.ByteSize = 7;
      else if (m_ebytesize == ::serial::e_byte_size_six)
         dcbSerialParams.ByteSize = 6;
      else if (m_ebytesize == ::serial::e_byte_size_five)
         dcbSerialParams.ByteSize = 5;
      else
         throw ::exception(error_bad_argument, "invalid char len");

         // setup estopbit
         if (m_estopbit == ::serial::e_stop_bit_one)
            dcbSerialParams.StopBits = ONESTOPBIT;
         else if (m_estopbit == ::serial::e_stop_bit_one_point_five)
            dcbSerialParams.StopBits = ONE5STOPBITS;
         else if (m_estopbit == ::serial::e_stop_bit_two)
            dcbSerialParams.StopBits = TWOSTOPBITS;
         else
            throw ::exception(error_bad_argument, "invalid stop bit");

            // setup eparity
            if (m_eparity == ::serial::e_parity_none)
            {
               dcbSerialParams.Parity = NOPARITY;
            }
            else if (m_eparity == ::serial::e_parity_even)
            {
               dcbSerialParams.Parity = EVENPARITY;
            }
            else if (m_eparity == ::serial::e_parity_odd)
            {
               dcbSerialParams.Parity = ODDPARITY;
            }
            else if (m_eparity == ::serial::e_parity_mark)
            {
               dcbSerialParams.Parity = MARKPARITY;
            }
            else if (m_eparity == ::serial::e_parity_space)
            {
               dcbSerialParams.Parity = SPACEPARITY;
            }
            else
            {
               throw ::exception(error_bad_argument, "invalid eparity");
            }

            // setup eflowcontrol
            if (m_eflowcontrol == ::serial::e_flow_control_none)
            {
               dcbSerialParams.fOutxCtsFlow = false;
               dcbSerialParams.fRtsControl = 0x00;
               dcbSerialParams.fOutX = false;
               dcbSerialParams.fInX = false;
            }
            if (m_eflowcontrol == ::serial::e_flow_control_software)
            {
               dcbSerialParams.fOutxCtsFlow = false;
               dcbSerialParams.fRtsControl = 0x00;
               dcbSerialParams.fOutX = true;
               dcbSerialParams.fInX = true;
            }
            if (m_eflowcontrol == ::serial::e_flow_control_hardware)
            {
               dcbSerialParams.fOutxCtsFlow = true;
               dcbSerialParams.fRtsControl = 0x03;
               dcbSerialParams.fOutX = false;
               dcbSerialParams.fInX = false;
            }

            // activate settings
            if (!SetCommState(m_hFile, &dcbSerialParams))
            {
               CloseHandle(m_hFile);
               throw ::exception(error_serial, "Error setting serial port settings.");
            }

            // Setup timeouts
            COMMTIMEOUTS timeouts = { 0 };
            timeouts.ReadIntervalTimeout = ::windows::wait(m_timeout.m_timeInterByteTimeout);
            timeouts.ReadTotalTimeoutConstant = ::windows::wait(m_timeout.m_timeReadTimeoutConstant);
            timeouts.ReadTotalTimeoutMultiplier = m_timeout.m_uReadTimeoutMultiplier;
            timeouts.WriteTotalTimeoutConstant = ::windows::wait(m_timeout.m_timeWriteTimeoutConstant);
            timeouts.WriteTotalTimeoutMultiplier = m_timeout.m_uWriteTimeoutMultiplier;
            if (!SetCommTimeouts(m_hFile, &timeouts))
            {
               throw ::exception(error_serial, "Error setting timeouts.");
            }


            // Compensate for the e_stop_bit_one_point_five enum being equal to int 3,
            // and not 1.5.
            // Update byte_time_ based on the ___new settings.

            if (m_estopbit == ::serial::e_stop_bit_one_point_five)
            {

               m_uiByteTimeNs = (unsigned int)(((((unsigned long long)1000LL * 1000LL * 1000LL) * (1 + m_ebytesize + m_eparity)) + (1500LL * 1000LL * 1000LL)) / ((unsigned long long)(m_ulBaudrate)));

            }
            else
            {

               m_uiByteTimeNs = (unsigned int)((((unsigned long long)1000LL * 1000LL * 1000LL) * (1 + m_ebytesize + m_eparity + m_estopbit)) / ((unsigned long long)(m_ulBaudrate)));

            }

   }


   void
      serial::close()
   {
      output_debug_string("\nSerial::serialimpl::close");
      if (m_bOpened == true)
      {
         output_debug_string("\nSerial::serialimpl::close open");
         if (m_hFile != INVALID_HANDLE_VALUE)
         {
            output_debug_string("\nSerial::serialimpl::close valid");
            int ret;
            ret = CloseHandle(m_hFile);
            if (ret == 0)
            {
               output_debug_string("\nSerial::serialimpl::close failed");
               string str;

               DWORD dwLastError = ::GetLastError();

               str.formatf("Error while closing serial port: %d", dwLastError);
               throw ::exception(error_io, str);
            }
            else
            {
               output_debug_string("\nSerial::serialimpl::close succesfully closed");
               m_hFile = INVALID_HANDLE_VALUE;
            }
         }
         m_bOpened = false;
      }

   }


   bool serial::isOpen() const
   {

      return m_bOpened;

   }


   size_t serial::available()
   {

      if (!m_bOpened)
      {

         return 0;

      }

      COMSTAT cs;

      if (!ClearCommError(m_hFile, nullptr, &cs))
      {

         string str;

         DWORD dwLastError = ::GetLastError();

         str.formatf("Error while checking status of the serial port: %d", dwLastError);

         throw ::exception(error_io, str);

      }

      return static_cast<size_t>(cs.cbInQue);

   }


   bool serial::waitReadable(class ::time /*timeout*/)
   {

      throw ::exception(error_io, "waitReadable is not implemented on Windows.");

      return false;

   }


   void serial::waitByteTimes(size_t count)
   {

      //throw ::exception (io_exception, "waitByteTimes is not implemented on Windows.");

      class time time;

      time.m_iSecond = uint64_muldiv(count, m_uiByteTimeNs, 1'000'000'000);

      time.m_iNanosecond = (count * m_uiByteTimeNs) % 1'000'000'000;

      preempt(time);

   }


   size_t serial::_read(unsigned char* buf, size_t size)
   {

      if (!m_bOpened)
      {

         throw ::exception(error_port_not_opened, "serial::read");

      }

      DWORD bytes_read;

      if (!ReadFile(m_hFile, buf, static_cast<unsigned int>(size), &bytes_read, nullptr))
      {

         string ss;

         DWORD dwLastError = ::GetLastError();

         ss.formatf("Error while reading from the serial port: %d", dwLastError);

         throw ::exception(error_io, ss);

      }

      return (size_t)(bytes_read);

   }


   size_t serial::_write(const unsigned char* data, size_t length)
   {

      if (m_bOpened == false)
      {

         throw ::exception(error_port_not_opened, "serial::write");

      }

      DWORD bytes_written;

      if (!WriteFile(m_hFile, data, static_cast<unsigned int>(length), &bytes_written, nullptr))
      {

         string str;

         DWORD dwLastError = ::GetLastError();

         str.formatf("Error while writing to the serial port: %d", dwLastError);

         throw ::exception(error_io, str);

      }

      return (size_t)(bytes_written);

   }


   size_t serial::readline(string& buffer, size_t size, string eol)
   {

      ::synchronous_lock readlock(read_synchronization());

      size_t eol_len = (size_t)eol.length();

      unsigned char* buffer_ = static_cast <unsigned char*> (alloca(size * sizeof(unsigned char)));

      auto timeStart = ::time::now();

      size_t read_so_far = 0;

      while (true)
      {

         size_t bytes_read = read(buffer_ + read_so_far, 1);

         read_so_far += bytes_read;

         if (bytes_read == 0)
         {

            if (timeStart.elapsed() > m_timeout.m_timeReadTimeoutConstant)
            {

               break;

            }

            // time_out occured on reading 1 unsigned char
            preempt(maximum(100_ηs, m_timeout.m_timeReadTimeoutConstant / 10));

            if (!::task_get_run())
            {

               break;

            }

            continue;

         }

         auto tickStart = ::time::now();

         if (string(reinterpret_cast<const_char_pointer > (buffer_ + read_so_far - eol_len), eol_len) == eol)
         {

            break; // EOL found

         }

         if (read_so_far == size)
         {

            break; // Reached the maximum read length

         }

      }

      buffer.append(reinterpret_cast<const_char_pointer > (buffer_), read_so_far);

      return read_so_far;

   }


   void serial::setPort(const string& port)
   {

      m_wstrPort = wstring(port);

   }


   string serial::getPort() const
   {

      return string(m_wstrPort);

   }


   void serial::set_timeout(const ::serial::timeout& timeout)
   {
      
      m_timeout = timeout;

      if (m_bOpened)
      {

         reconfigurePort();

      }

   }


   ::serial::timeout serial::getTimeout() const
   {

      return m_timeout;

   }


   void serial::setBaudrate(unsigned int baudrate)
   {
      
      m_ulBaudrate = baudrate;

      if (m_bOpened)
      {

         reconfigurePort();

      }

   }


   unsigned int serial::getBaudrate() const
   {

      return m_ulBaudrate;

   }


   void serial::setBytesize(::serial::enum_byte_size ebytesize)
   {
   
      m_ebytesize = ebytesize;

      if (m_bOpened)
      {

         reconfigurePort();

      }

   }


   ::serial::enum_byte_size serial::getBytesize() const
   {
      
      return m_ebytesize;

   }


   void serial::setParity(::serial::enum_parity eparity)
   {

      m_eparity = eparity;

      if (m_bOpened)
      {

         reconfigurePort();

      }

   }


   ::serial::enum_parity serial::getParity() const
   {
      
      return m_eparity;

   }


   void serial::setStopbits(::serial::enum_stop_bit estopbit)
   {
      
      m_estopbit = estopbit;

      if (m_bOpened)
      {

         reconfigurePort();

      }

   }


   ::serial::enum_stop_bit serial::getStopbits() const
   {
      
      return m_estopbit;

   }


   void serial::setFlowcontrol(::serial::enum_flow_control eflowcontrol)
   {
      
      m_eflowcontrol = eflowcontrol;
      
      if (m_bOpened)
      {

         reconfigurePort();

      }

   }


   ::serial::enum_flow_control serial::getFlowcontrol() const
   {

      return m_eflowcontrol;

   }


   void serial::_flush()
   {

      if (m_bOpened == false)
      {

         throw ::exception(error_port_not_opened, "serial::flush");

      }

      FlushFileBuffers(m_hFile);

   }


   void serial::_flushInput()
   {

      throw ::exception(error_io, "flushInput is not supported on Windows.");

   }


   void serial::_flushOutput()
   {

      throw ::exception(error_io, "flushOutput is not supported on Windows.");

   }


   void serial::sendBreak(int /*time*/)
   {

      throw ::exception(error_io, "sendBreak is not supported on Windows.");

   }


   void serial::setBreak(bool level)
   {

      if (m_bOpened == false)
      {
         throw ::exception(error_port_not_opened, "serial::setBreak");
      }
      if (level)
      {
         EscapeCommFunction(m_hFile, SETBREAK);
      }
      else
      {
         EscapeCommFunction(m_hFile, CLRBREAK);
      }
   }


   void serial::setRTS(bool level)
   {

      if (m_bOpened == false)
      {
         throw ::exception(error_port_not_opened, "serial::setRTS");
      }
      if (level)
      {
         EscapeCommFunction(m_hFile, SETRTS);
      }
      else
      {
         EscapeCommFunction(m_hFile, CLRRTS);
      }

   }


   void serial::setDTR(bool level)
   {

      if (m_bOpened == false)
      {
         throw ::exception(error_port_not_opened, "serial::setDTR");
      }
      if (level)
      {
         EscapeCommFunction(m_hFile, SETDTR);
      }
      else
      {
         EscapeCommFunction(m_hFile, CLRDTR);
      }

   }


   bool serial::waitForChange()
   {
      if (m_bOpened == false)
      {
         throw ::exception(error_port_not_opened, "serial::waitForChange");
      }

      DWORD dwCommEvent;

      if (!SetCommMask(m_hFile, EV_CTS | EV_DSR | EV_RING | EV_RLSD))
      {
         // Error setting communications mask
         return false;
      }

      if (!WaitCommEvent(m_hFile, &dwCommEvent, nullptr))
      {
         // An error occurred waiting for the happening.
         return false;
      }
      else
      {
         // Event has occurred.
         return true;
      }
   }


   bool serial::getCTS()
   {

      if (m_bOpened == false)
      {
         
         throw ::exception(error_port_not_opened, "serial::getCTS");

      }

      DWORD dwModemStatus;
      if (!GetCommModemStatus(m_hFile, &dwModemStatus))
      {
         throw ::exception(error_io, "Error getting the status of the CTS line.");
      }

      return (MS_CTS_ON & dwModemStatus) != 0;
   }


   bool serial::getDSR()
   {

      if (m_bOpened == false)
      {

         throw ::exception(error_port_not_opened, "serial::getDSR");

      }

      DWORD dwModemStatus;

      if (!GetCommModemStatus(m_hFile, &dwModemStatus))
      {
         throw ::exception(error_io, "Error getting the status of the DSR line.");
      }

      return (MS_DSR_ON & dwModemStatus) != 0;

   }


   bool serial::getRI()
   {
      
      if (m_bOpened == false)
      {
         
         throw ::exception(error_port_not_opened, "serial::getRI");

      }

      DWORD dwModemStatus;

      if (!GetCommModemStatus(m_hFile, &dwModemStatus))
      {
         throw ::exception(error_io, "Error getting the status of the RI line.");
      }

      return (MS_RING_ON & dwModemStatus) != 0;
   }

   bool
      serial::getCD()
   {
      if (m_bOpened == false)
      {
         throw ::exception(error_port_not_opened, "serial::getCD");
      }

      DWORD dwModemStatus;

      if (!GetCommModemStatus(m_hFile, &dwModemStatus))
      {
         // Error in GetCommModemStatus;
         throw ::exception(error_io, "Error getting the status of the CD line.");
      }

      return (MS_RLSD_ON & dwModemStatus) != 0;
   }


   ::particle * serial::read_synchronization()
   {
      // m_pmutexRead->lock();
      // 
      // 
      
      return m_pmutexRead;

      //if (WaitForSingleObject(m_hMutexRead, U32_INFINITE_TIMEOUT) != WAIT_OBJECT_0)
      //{
      //   throw ::exception(error_io, "Error claiming read ::mutex.");
      //}

   }


   ::particle * serial::write_synchronization()
   {

      //m_pmutexRead->unlock();

      return m_pmutexWrite;

    /*  if (!ReleaseMutex(m_hMutexRead))
      {
         throw ::exception(error_io, "Error releasing read ::mutex.");
      }*/
   }

   //void serial::writeLock()
   //{
   //   //if (WaitForSingleObject(m_hMutexWrite, U32_INFINITE_TIMEOUT) != WAIT_OBJECT_0)
   //   //{
   //     // throw ::exception(error_io, "Error claiming write ::mutex.");
   //   //}

   //   m_mutexWrite->lock();
   //}

   //void serial::writeUnlock()
   //{
   //   //if (!ReleaseMutex(m_hMutexWrite))
   //   //{
   //     // throw ::exception(error_io, "Error releasing write ::mutex.");
   //   //}

   //   m_pmutexWrite->unlock();

   //}


} // namespace acme_windows




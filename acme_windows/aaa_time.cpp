#include "framework.h"
#include "acme/operating_system.h"













//
///**********************************=> unix ************************************/
//#ifndef _WIN32
//void SleepInMs(unsigned int ms) {
//   struct timespec ts;
//   ts.tv_sec = ms / 1000;
//   ts.tv_nsec = ms % 1000 * 1000000;
//
//   while (nanosleep(&ts, &ts) == -1 && errno == EINTR);
//}
//
//void SleepInUs(unsigned int us) {
//   struct timespec ts;
//   ts.tv_sec = us / 1000000;
//   ts.tv_nsec = us % 1000000 * 1000;
//
//   while (nanosleep(&ts, &ts) == -1 && errno == EINTR);
//}
//
//#ifndef __APPLE__
//::u3264 NowInUs() {
//   struct timespec now;
//   clock_gettime(CLOCK_MONOTONIC, &now);
//   return static_cast<::u3264>(now.tv_sec) * 1000000 + now.tv_nsec / 1000;
//}
//
//#else // mac
//::u3264 NowInUs() {
//   clock_serv_t cs;
//   mach_timespec_t ts;
//
//   host_get_clock_service(mach_host_self(), SYSTEM_CLOCK, &cs);
//   clock_get_time(cs, &ts);
//   mach_port_deallocate(mach_task_self(), cs);
//
//   return static_cast<::u3264>(ts.tv_sec) * 1000000 + ts.tv_nsec / 1000;
//}
//#endif // __APPLE__
//#endif // _WIN32
///************************************ unix <=**********************************/
//
///**********************************=> win *************************************/
//#ifdef _WIN32
//void SleepInMs(unsigned int ms) {
//   ::sleep(ms);
//}
//
//void SleepInUs(unsigned int us) {
//   ::LARGE_INTEGER ft;
//   ft.QuadPart = -static_cast<long long>(us * 10);  // '-' using relative time
//
//   ::HANDLE timer = ::CreateWaitableTimer(nullptr, true, nullptr);
//   ::SetWaitableTimer(timer, &ft, 0, nullptr, nullptr, 0);
//   ::WaitForSingleObject(timer, U32_INFINITE_TIMEOUT);
//   ::CloseHandle(timer);
//}
//
//static inline ::u3264 GetPerfFrequency() {
//   ::LARGE_INTEGER freq;
//   ::QueryPerformanceFrequency(&freq);
//   return freq.QuadPart;
//}
//
//static inline ::u3264 PerfFrequency() {
//   static ::u3264 xFreq = GetPerfFrequency();
//   return xFreq;
//}
//
//static inline ::u3264 PerfCounter() {
//   ::LARGE_INTEGER counter;
//   ::QueryPerformanceCounter(&counter);
//   return counter.QuadPart;
//}
//
//::u3264 NowInUs() {
//   return static_cast<::u3264>(
//      static_cast<double>(PerfCounter()) * 1000000 / PerfFrequency());
//}
//#endif // _WIN32

///* Windows sleep in 100ns units */
//void sleep(const ::nanosecond & nanosecond)
//{
//
//   /* Declarations */
//   HANDLE timer;   /* Timer handle */
//
//   LARGE_INTEGER li;   /* Time definition */
//
//   /* Create timer */
//   if (!(timer = CreateWaitableTimer(nullptr, true, nullptr)))
//   {
//
//      sleep((const ::duration &) nanosecond);
//
//      return;
//
//   }
//
//   /* Set timer properties */
//   li.QuadPart = -(nanosecond.m_i / 100LL );
//
//   if (!SetWaitableTimer(timer, &li, 0, nullptr, nullptr, false))
//   {
//
//      CloseHandle(timer);
//
//      throw ::exception(::resource_exception());
//
//   }
//
//   /* Start & wait for timer */
//   WaitForSingleObject(timer, U32_INFINITE_TIMEOUT);
//
//   /* Clean resources */
//   CloseHandle(timer);
//
//   /* Slept without problems */
//   //return true;
//
//}


//void sleep(const ::duration & dur)
//{
//
//   nanosleep(dur.total_nanoseconds());
//
//}


//namespace windows
//{
//
//
//   CLASS_DECL_ACME void time_to_filetime(::object* pobject, const ::earth::time& time, LPFILETIME pFileTime)
//   {
//
//      SYSTEMTIME sysTime;
//
//      sysTime.wYear = (unsigned short)time.GetYear();
//      sysTime.wMonth = (unsigned short)time.GetMonth();
//      sysTime.wDay = (unsigned short)time.GetDay();
//      sysTime.wHour = (unsigned short)time.GetHour();
//      sysTime.wMinute = (unsigned short)time.GetMinute();
//      sysTime.wSecond = (unsigned short)time.GetSecond();
//      sysTime.wMilliseconds = 0;
//
//      // convert system time to local file time
//      FILETIME localTime;
//      if (!SystemTimeToFileTime((LPSYSTEMTIME)&sysTime, &localTime))
//      {
//
//         DWORD dwLastError = ::GetLastError();
//
//         ::file::throw_os_error(dwLastError);
//
//      }
//
//      // convert local file time to UTC file time
//      if (!LocalFileTimeToFileTime(&localTime, pFileTime))
//      {
//
//         DWORD dwLastError = ::GetLastError();
//
//         ::file::throw_os_error(dwLastError);
//
//      }
//
//   }
//
//
//} // namespace windows




// Created by camilo on 2024-03-07 ~10:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/trace.h"
#include "acme/_operating_system.h"


namespace acme_windows
{

   class create_process :

      virtual public ::particle
   {
   public:


      STARTUPINFOEX m_si = {};
      PROCESS_INFORMATION m_pi = {};
      ::memory m_memoryAttrList;

      const memsize m_iPipeSize = 16_KiB;

      HANDLE m_hOutRd;
      HANDLE m_hOutWr;
      HANDLE m_hErrRd;
      HANDLE m_hErrWr;
      HANDLE m_hInRd;
      HANDLE m_hInWr;

      //OVERLAPPED m_overlappedOut;
      //OVERLAPPED m_overlappedErr;

      class ::time m_timeStart;;

      SECURITY_ATTRIBUTES m_saAttr = {};
      LPPROC_THREAD_ATTRIBUTE_LIST m_pattrList;

      string m_strError;

      string m_strOutput;

      int m_iExitCode;

      DWORD m_dwExitCode2;

      DWORD m_dwCreationFlags;

      ::file::path m_pathWorkingDirectory;
      ::e_display m_edisplay = e_display_none;


      create_process();
      ~create_process();


      SECURITY_ATTRIBUTES* __sa();

      void initialize_stdout();
      void initialize_stderr();

      void initialize_stdin();
      void prepare();

      void set_create_new_console();

      void call_create_process(const ::scoped_string& scopedstr);

      void wait_process(const trace_function& tracefunction);

      //void _read_task(enum_trace_level etracelevel, const trace_function& tracefunction, ::string * pstrOut, OVERLAPPED * poverlapped);
      //void __read_task(enum_trace_level etracelevel, const trace_function& tracefunction, ::string* pstrOut, const void * p, ::collection::count c);

   };


} // namespace acme_windows


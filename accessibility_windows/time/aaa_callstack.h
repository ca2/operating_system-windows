#pragma once


#undef Context


#ifdef WINDOWS

#define FAST_STACK_TRACE 1


#pragma warning(disable: 4091)
#include <ImageHlp.h>
#if OSBIT == 32
#define OS_DWORD DWORD
#define OS_IMAGEHLP_LINE IMAGEHLP_LINE
#define OS_SymGetLineFromAddr SymGetLineFromAddr
#define OS_SymGetSymFromAddr SymGetSymFromAddr
#define OS_STACKFRAME   STACKFRAME
#define OS_PIMAGEHLP_SYMBOL PIMAGEHLP_SYMBOL
#define OS_IMAGEHLP_SYMBOL IMAGEHLP_SYMBOL
#else
typedef struct _tagSTACKFRAME64 STACKFRAME64, * LPSTACKFRAME64;
typedef struct _IMAGEHLP_LINE64 IMAGEHLP_LINE64, * PIMAGEHLP_LINE64;
#define OS_DWORD DWORD64
#define OS_IMAGEHLP_LINE IMAGEHLP_LINE64
#define OS_SymGetLineFromAddr SymGetLineFromAddr64
#define OS_SymGetSymFromAddr SymGetSymFromAddr64
#define OS_STACKFRAME   STACKFRAME64
#define OS_PIMAGEHLP_SYMBOL PIMAGEHLP_SYMBOL64
#define OS_IMAGEHLP_SYMBOL IMAGEHLP_SYMBOL64
#endif

#else

#define FAST_STACK_TRACE 0

#endif



namespace windows
{


   class CLASS_DECL_ACME callstack :
      public ::callstack
   {
   public:


      OS_DWORD             m_uia[4096];
      OS_STACKFRAME        m_stackframe;

      bool                 m_bSkip;
      ::i32                  m_iAddressRead;
      ::i32                  m_iAddressWrite;
      bool                 m_bOk;
      bool                 m_bRefreshSymbols;
      //PVOID                m_pvoidDllNotificationCookie;
      CONTEXT              m_context;

      bool                 m_bInit;
      HMODULE              m_ha[4096];
      ::i32                  m_iHa;

      HMODULE              m_ma[4096];
      ::i32                  m_iMa;
      ::i8 * m_szaModule[4096];
      ::i32 m_iSkip;
      ::i32 m_iCount;

      static critical_section * s_pcriticalsection;

      callstack(const scoped_string & strFormat = default_format(), ::i32 iSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, void * caller_address = nullptr, ::i32 iCount = -1);
      virtual ~callstack();


      //static void global_enable_stack_trace(bool bEnable = true);
      static const ::i8 * default_format() { return "%f(%l) %s\n"; }

      const ::i8 * get_dup(const scoped_string & strFormat = default_format(), ::i32 uiSkip = CALLSTACK_DEFAULT_SKIP_TRIGGER, ::i32 iCount = -1);

      const ::i8 * stack_trace() const;


      bool stack_trace(CONTEXT *, iptr iSkip = 0, const scoped_string & strFormat = default_format(), ::i32 iCount = -1);
      bool stack_trace(iptr iSkip = 1, const scoped_string & strFormat = default_format(), ::i32 iCount = -1);
      bool stack_trace(CONTEXT *, iptr iSkip = 1, bool bSkip = false, const scoped_string & strFormat = default_format(), ::i32 iCount = -1);
      ::i8 * stack_trace(OS_DWORD * pinteraction, ::i32 c, const scoped_string & strFormat = default_format(), ::i32 iCount = -1);

      void reset();

#ifdef WINDOWS_DESKTOP

      ::u32 WINAPI stack_trace_ThreadProc(void * pvoidParam);


      bool get_line_from_address(HANDLE hProc, OS_DWORD uiAddress, ::u32 * puiDisplacement, OS_IMAGEHLP_LINE * pline);
      //size_t get_module_basename(HMODULE hmodule, string & strName);
      size_t get_module_name(HMODULE hmodule, ::i8 * psz, ::i32 nCount);

      ::i8 * get_frame(const scoped_string & strFormat, ::i32 & iLine);

      bool check();


      void address(OS_DWORD a) { m_uia[m_iAddressWrite++] = a; }
      OS_DWORD address() { return m_uia[m_iAddressRead]; }
      void backtrace(::i32 iCount = -1);
      //DWORD64 * backtrace(::i32 &c);
      void backtrace(OS_DWORD * pinteraction, ::i32 & c);

      // symbol handler queries
      size_t      module(::i8 * str, ::i32 nCount);
      size_t      symbol(::i8 * str, ::i32 nCount, OS_DWORD * pdisplacement = 0);
      ::collection::index       fileline(::i8 * str, ::i32 nCount, ::u32 * pline, ::u32 * pdisplacement = 0);


      // stack walk
      bool stack_first(CONTEXT * pctx, ::i32 iCount);
      bool stack_next();

      bool init();
      bool fail() const;
      bool load_modules();
      void clear();
      bool load_module(HANDLE, HMODULE);
#endif

   };


} // namespace windows




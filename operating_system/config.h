#pragma once


#define NTDDI_VERSION   0x0A000000 // NTDDI_WIN10
#define _WIN32_WINNT    0x0A00 // _WIN32_WINNT_WIN10
#define WINVER          0x0A00 // _WIN32_WINNT_WIN10
#define _WIN32_IE       0x0A00 // _WIN32_IE_IE110


#define WCHAR_T_SIZE 16

#define BROAD_PRECOMPILED_HEADER 1



//#define _OPENGL 1

#include "inc.h"


#include "config_memdleak.h"




#pragma warning(default:4263)
#pragma warning(default:4266)

#define PLATFORM_NAMESPACE windows

#define PLATFORM_COMMON_NAMESPACE windows_common

#define PLATFORM_STRING "windows"

#define PLATFORM_COMMON_STRING "windows_common"

#define DEFAULT_DIR_SEPARATOR "\\"



#if !defined(WIN32)
#define WIN32
#endif

#if !defined(_WIN32)
#define _WIN32
#endif

#ifndef _WINDOWS
#define _WINDOWS
#endif


#ifndef WINDOWS
#define WINDOWS
#endif


#ifndef WINDOWS_DESKTOP
#define WINDOWS_DESKTOP
#endif


#define VARIADIC_TEMPLATE_FORMAT2


#define BSD_STYLE_SOCKETS
#define HAVE_MYSQL
#define HAVE_OPENSSL


#define PLATFORM_NAME   "windows"



#define SECURITY_WIN32


#ifdef UNICODE
#ifndef _UNICODE
#define _UNICODE
#endif
#endif

#ifdef _UNICODE
#ifndef UNICODE
#define UNICODE
#endif
#endif


#define DECL_C __cdecl


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#ifndef _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_DEPRECATE
#endif
#ifndef _CRT_NONSTDC_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#endif
#ifndef _CRT_NONSTDC_NO_WARNINGS
#define _CRT_NONSTDC_NO_WARNINGS
#endif
#ifndef _WINSOCK_DEPRECATED_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#endif
#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif


#ifdef WINDOWS
#ifdef CUBE
#define __FACTORY_EXPORT extern "C"
#else
#define __FACTORY_EXPORT extern "C" __declspec(dllexport)
#endif
#else
#define __FACTORY_EXPORT extern "C"
#endif


#ifdef WINDOWS
#ifdef CUBE
#define __FACTORY_IMPORT extern "C"
#else
#define __FACTORY_IMPORT extern "C" __declspec(dllimport)
#endif
#else
#define __FACTORY_IMPORT extern "C"
#endif


#ifdef CUBE
#define CLASS_DECL_EXPORT
#define CLASS_DECL_IMPORT
#else
#define CLASS_DECL_EXPORT __declspec(dllexport)
#define CLASS_DECL_IMPORT __declspec(dllimport)
#endif
#define CLASS_DECL_THREAD __declspec(thread)

#define SECURITY_WIN32




#pragma warning(disable:4250) // disable warning if inherited via dominance



#define HAVE_UINT64_T 1
#define HAVE_WINSOCK2_H 1




#define MESSAGE_WINDOW_PARENT HWND_MESSAGE


#ifndef _DEBUG
#pragma warning(disable: 4101)  // unreferenced local function has been erased
#endif


/////////////////////////////////////////////////////////////////////////////
// Turn off warnings for /W4
// To resume any of these warning: #pragma warning(default: 4xxx)
// which should be placed after the _ include files

#pragma warning(disable: 4505)  // unreferenced local function has been erased
#pragma warning(disable: 4511)  // private copy constructors are good to have
#pragma warning(disable: 4512)  // private operator= are good to have
#pragma warning(disable: 4514)  // unreferenced inlines are common
#pragma warning(disable: 4710)  // function not inlined
#pragma warning(disable: 4660)  // template is already instantiated
#pragma warning(disable: 4127)  // constant expression used in macros do while(0);

#pragma warning(disable: 4275)  // deriving exported class from non-exported
#pragma warning(disable: 4251)  // using non-exported as public in exported


#ifdef ___ALL_WARNINGS
#pragma warning( push )
#endif

// warnings caerated with common acme API/Windows code
#pragma warning(disable: 4134)  // message map member fxn casts
#pragma warning(disable: 4201)  // nameless unions are part of C++
#pragma warning(disable: 4320)  // structs with uuid handled as interfaces
#pragma warning(disable: 4705)  // statement has no effect in optimized code
#pragma warning(disable: 4191)  // pointer-to-function casting
// warnings caused by normal optimizations
#ifndef DEBUG
#pragma warning(disable: 4701)  // local var *may* be used without init
#pragma warning(disable: 4702)  // unreachable code caused by optimizations
#pragma warning(disable: 4791)  // loss of debugging info in release version
#pragma warning(disable: 4189)  // initialized but unused var
#pragma warning(disable: 4390)  // is_empty controlled statement
#endif
#pragma warning(disable: 4204)  // non-constant aggregate initializer
#pragma warning(disable: 4263 4264)  // base class method is hidden
#if OSBIT == 32 || OSBIT == 64
#pragma warning(disable: 4244) // C4244: '+=': conversion from 'index' to 'LONG', possible loss of data
#endif


// #define FONT_SANS "Segoe UI"
// #define FONT_SERIF "Times New Roman"
// #define FONT_MONO "Courier New"
// #define FONT_SANS_EX "Geneva"
// #define FONT_SERIF_EX "Palatino Linotype"
// #define FONT_SANS_FX "Tahoma"
// #define FONT_SERIF_FX "Georgia"



#ifdef __cplusplus

#define LOG_THIS_TAG (typeid(*this).name())
#define LOG_MEMBER_PREFIX __FUNCTION__

#define ALOG_FUNCTION __FUNCTION__
#define ALOG_FILE __FILE__
#define ALOG_LINE __LINE__

#endif


#define STR_NEWLINE "\r\n"



#ifndef UNICODE
#error "UNICODE not defined"
#endif



#ifndef _UNICODE
#error "_UNICODE not defined"
#endif



#define hcursor_null ((hcursor) nullptr)


#pragma once


#ifdef _WINDOWS_
#error WINDOWS.H already included.  ca2 apps must not #include <windows.h>
#endif


#define boolean windows_boolean
#undef ERROR
#undef __UNREFERENCED_PARAMETER


#define NOMINMAX


#ifdef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#define NOGDI
#endif


//
//
//// certain parts of WINDOWS.H are necessary
//#undef NOKERNEL
//#define NOGDI
//#undef NOUSER
//#undef NODRIVERS
//#undef NOLOGERROR
//#undef NOPROFILER
//#undef NOMEMMGR
//#undef NOLFILEIO
//#undef NOOPENFILE
//#undef NORESOURCE
//#undef NOATOM
//#undef NOMETAFILE
//#undef NOLANGUAGE
//#undef NOLSTRING
//#undef NODBCS
//#undef NOKEYBOARDINFO
//#undef NOGDICAPMASKS
//#undef NOCOLOR
//#undef NOGDIOBJ
//#undef NODRAWTEXT
//#undef NOTEXTMETRICW
//#undef NOSCALABLEFONT
//#undef NOBITMAP
//#undef NORASTEROPS
//#undef NOSYSMETRICS
//#undef NOSYSTEMPARAMSINFO
//#undef NOMSG
//#undef NOWINSTYLES
//#undef NOWINOFFSETS
//#undef NOSHOWWINDOW
//#undef NODEFERWINDOWPOS
//#undef NOVIRTUALKEYCODES
//#undef NOKEYSTATES
//#undef NOWH
//#undef NOMENUS
//#undef NOSCROLL
//#undef NOCLIPBOARD
//#undef NOICONS
//#undef NOMB
//#undef NOSYSCOMMANDS
//#undef NOMDI
//#undef NOCTLMGR
//#undef NOWINMESSAGES
//


#undef MAKEWORD
#undef LOWORD
#undef HIWORD
#undef HIBYTE


#ifndef WIN32
#define WIN32
#endif


#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif


#pragma warning(push)
#pragma warning(disable: 4311 4312)
#pragma warning(disable: 4201)  // winnt.h uses nameless structs


#include <windows.h>

#include <shlwapi.h>

#include <inttypes.h>

#pragma warning(pop)

#include <zmouse.h>

struct HKEY__;
typedef struct HKEY__ *HKEY;

#include <stdio.h>
#include <wchar.h>

#include <tchar.h>
#include <mbctype.h>
#include <mbstring.h>


#define WM_CTLCOLOR     0x0019


#include <winsock2.h>
#include <ws2tcpip.h>
#include <Psapi.h>
#include <ole2.h>


#define GDIPVER 0x0110



#undef minimum
#undef maximum
#undef boolean

#undef RGN_ERROR
#define RGN_ERROR 0

#undef ERROR
#define ERROR LOG_ERROR




#pragma once


#if defined(_M_X64) || defined(__x86_64__)  // x64 (AMD64)

#define AMD64
#define OS64BIT
#define OSBIT 64

#define __END_OSBIT(xxx) __CONCATENATE(xxx, 64)
#define __MID_OSBIT(xxx, zzz) __CONCATENATE3(xxx, 64, zzz)


#elif defined(_M_ARM64) || defined(__aarch64__)  // ARM64

#define ARM64
#define OS64BIT
#define OSBIT 64

#define __END_OSBIT(xxx) __CONCATENATE(xxx, 64)
#define __MID_OSBIT(xxx, zzz) __CONCATENATE3(xxx, 64, zzz)


#elif defined(_M_IX86) || defined(__i386__)  // x86 (32-bit)

#define X86
#define OS32BIT
#define OSBIT 32
#define _X86_

#define __END_OSBIT(xxx) __CONCATENATE(xxx, 32)
#define __MID_OSBIT(xxx, zzz) __CONCATENATE3(xxx, 32, zzz)


#elif defined(_M_ARM) || defined(__arm__)   // ARM32

#define ARM32
#define OS32BIT
#define OSBIT 32

#define __END_OSBIT(xxx) __CONCATENATE(xxx, 32)
#define __MID_OSBIT(xxx, zzz) __CONCATENATE3(xxx, 32, zzz)


#else

#error Currently unsupported architecture

#endif






#pragma once


#if defined(_M_X64)  // X64


#define AMD64
#define OS64BIT
#define OSBIT 64

#define __END_OSBIT(xxx) __CONCAT(xxx, 64)
#define __MID_OSBIT(xxx, zzz) __CONCAT3(xxx, 64, zzz)



#elif defined(_M_IX86)


#define X86
#define OS32BIT
#define OSBIT 32
#define _X86_

#define __END_OSBIT(xxx) __CONCAT(xxx, 32)
#define __MID_OSBIT(xxx, zzz) __CONCAT3(xxx, 32, zzz)


#endif












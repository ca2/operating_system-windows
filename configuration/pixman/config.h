// Created by camilo on 2023-02-28 01:35 BRT <3ThomasBorregaardSorensen!!
#pragma once


#define _CRT_SECURE_NO_WARNINGS



#pragma once


#include "config.h"


#ifdef WIN32
#define PIXMAN_API __declspec(dllexport)
#endif


/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
#undef AC_APPLE_UNIVERSAL_BUILD

/* Whether we have alarm() */
#undef HAVE_ALARM

/* Whether the compiler supports __builtin_clz */
#undef HAVE_BUILTIN_CLZ

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef HAVE_DLFCN_H

/* Whether we have feenableexcept() */
#undef HAVE_FEENABLEEXCEPT

/* Define to 1 if we have <fenv.h> */
#undef HAVE_FENV_H

/* Whether the tool chain supports __float128 */
#undef HAVE_FLOAT128

/* Whether the compiler supports GCC vector extensions */
#undef HAVE_GCC_VECTOR_EXTENSIONS

/* Define to 1 if you have the `getisax' function. */
#undef HAVE_GETISAX

/* Whether we have getpagesize() */
#undef HAVE_GETPAGESIZE

/* Whether we have gettimeofday() */
#undef HAVE_GETTIMEOFDAY

/* Define to 1 if you have the "_inttypes.h" header file. */
#undef HAVE_INTTYPES_H

/* Define to 1 if you have the `pixman-1' library (-lpixman-1). */
#undef HAVE_LIBPIXMAN_1

/* Whether we have libpng */
#undef HAVE_LIBPNG

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H

/* Whether we have mmap() */
#undef HAVE_MMAP

/* Whether we have mprotect() */
#undef HAVE_MPROTECT

/* Whether we have posix_memalign() */
#undef HAVE_POSIX_MEMALIGN

/* Whether pthreads is supported */
#if defined(LINUX) || defined(ANDROID)
#define HAVE_PTHREADS 1
#endif

/* Whether we have sigaction() */
#undef HAVE_SIGACTION

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#undef HAVE_STDLIB_H

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#undef HAVE_STRING_H

/* Define to 1 if we have <sys/mman.h> */
#undef HAVE_SYS_MMAN_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#undef LT_OBJDIR

/* Name of package */
#define PACKAGE "axispixman"

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the home page for this package. */
#undef PACKAGE_URL

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* enable TIMER_BEGIN/TIMER_END macros */
#undef PIXMAN_TIMERS

/* The size of `long', as computed by sizeof. */
#undef SIZEOF_LONG

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* The compiler supported TLS storage class */
#undef TLS

/* Whether the tool chain supports __attribute__((constructor)) */
#undef TOOLCHAIN_SUPPORTS_ATTRIBUTE_CONSTRUCTOR

/* use ARM IWMMXT compiler intrinsics */
#undef USE_ARM_IWMMXT

/* use ARM NEON assembly optimizations */
#undef USE_ARM_NEON

/* use ARM SIMD assembly optimizations */
#undef USE_ARM_SIMD

#ifdef __ARM_ARCH_7A__
#define USE_ARM_NEON 1
#define USE_ARM_SIMD 1
#endif


/* use GNU-style inline assembler */
#undef USE_GCC_INLINE_ASM

/* use Loongson Multimedia Instructions */
#undef USE_LOONGSON_MMI

/* use MIPS DSPr2 assembly optimizations */
#undef USE_MIPS_DSPR2

/* use OpenMP in the test suite */
#undef USE_OPENMP

/* use SSE2 compiler intrinsics */
#undef USE_SSE2

/* use SSSE3 compiler intrinsics */
#undef USE_SSSE3

/* use VMX compiler intrinsics */
#undef USE_VMX

/* use x86 MMX compiler intrinsics */
#undef USE_X86_MMX

/* Version number of package */
#undef VERSION

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  undef WORDS_BIGENDIAN
# endif
#endif

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#undef inline
#endif

/* Define to sqrt if you do not have the `sqrtf' function. */
#undef sqrtf


#ifdef WINDOWS
#define USE_SSE2 1
#define USE_SSE3 1
#endif

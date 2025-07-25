#pragma once


#define PACKAGE "idn"


/* config.h.in.  Generated from configure.ac by autoheader.  */

#include "configuration/config.h.h"
#include <stdlib.h>
#include <stdint.h>

/* Define to the number of bits in type 'ptrdiff_t'. */
#undef BITSIZEOF_PTRDIFF_T

/* Define to the number of bits in type 'sig_atomic_t'. */
#undef BITSIZEOF_SIG_ATOMIC_T

/* Define to the number of bits in type 'glong'. */
#undef BITSIZEOF_SIZE_T

/* Define to the number of bits in type 'wchar_t'. */
#undef BITSIZEOF_WCHAR_T

/* Define to the number of bits in type 'wint_t'. */
#undef BITSIZEOF_WINT_T

/* Define to one of `_getb67', `GETB67', `getb67' for Cray-2 and Cray-YMP
   systems. This function is required for `alloca.c' support on those systems.
   */
#undef CRAY_STACKSEG_END

/* Define if mono is the preferred C# implementation. */
#undef CSHARP_CHOICE_MONO

/* Define if pnet is the preferred C# implementation. */
#undef CSHARP_CHOICE_PNET

/* Define to 1 if using `alloca.c'. */
#undef C_ALLOCA

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#undef ENABLE_NLS

/* Define if gettimeofday clobbers the localtime buffer. */
#undef GETTIMEOFDAY_CLOBBERS_LOCALTIME

/* Define this to 'void' or 'struct timezone' to match the system's
   declaration of the second argument to gettimeofday. */
#undef GETTIMEOFDAY_TIMEZONE

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module fscanf shall be considered present. */
#undef GNULIB_FSCANF

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module lock shall be considered present. */
#undef GNULIB_LOCK

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module scanf shall be considered present. */
#undef GNULIB_SCANF

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module strerror shall be considered present. */
#undef GNULIB_STRERROR

/* Define to 1 when the gnulib module close should be tested. */
#undef GNULIB_TEST_CLOSE

/* Define to 1 when the gnulib module dup2 should be tested. */
#undef GNULIB_TEST_DUP2

/* Define to 1 when the gnulib module environ should be tested. */
#undef GNULIB_TEST_ENVIRON

/* Define to 1 when the gnulib module fdopen should be tested. */
#undef GNULIB_TEST_FDOPEN

/* Define to 1 when the gnulib module fstat should be tested. */
#undef GNULIB_TEST_FSTAT

/* Define to 1 when the gnulib module getcwd should be tested. */
#undef GNULIB_TEST_GETCWD

/* Define to 1 when the gnulib module getdtablesize should be tested. */
#undef GNULIB_TEST_GETDTABLESIZE

/* Define to 1 when the gnulib module getopt-gnu should be tested. */
#undef GNULIB_TEST_GETOPT_GNU

/* Define to 1 when the gnulib module gettimeofday should be tested. */
#undef GNULIB_TEST_GETTIMEOFDAY

/* Define to 1 when the gnulib module lstat should be tested. */
#undef GNULIB_TEST_LSTAT

/* Define to 1 when the gnulib module malloc-posix should be tested. */
#undef GNULIB_TEST_MALLOC_POSIX

/* Define to 1 when the gnulib module open should be tested. */
#undef GNULIB_TEST_OPEN

/* Define to 1 when the gnulib module putenv should be tested. */
#undef GNULIB_TEST_PUTENV

/* Define to 1 when the gnulib module setenv should be tested. */
#undef GNULIB_TEST_SETENV

/* Define to 1 when the gnulib module setlocale should be tested. */
#undef GNULIB_TEST_SETLOCALE

/* Define to 1 when the gnulib module stat should be tested. */
#undef GNULIB_TEST_STAT

/* Define to 1 when the gnulib module strerror should be tested. */
#undef GNULIB_TEST_STRERROR

/* Define to 1 when the gnulib module strverscmp should be tested. */
#undef GNULIB_TEST_STRVERSCMP

/* Define to 1 when the gnulib module symlink should be tested. */
#undef GNULIB_TEST_SYMLINK

/* Define to 1 when the gnulib module unsetenv should be tested. */
#undef GNULIB_TEST_UNSETENV

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u8-mbtoucr shall be considered present. */
#undef GNULIB_UNISTR_U8_MBTOUCR

/* Define to a C preprocessor expression that evaluates to 1 or 0, depending
   whether the gnulib module unistr/u8-uctomb shall be considered present. */
#undef GNULIB_UNISTR_U8_UCTOMB

/* Define to 1 if you have 'alloca' after including <alloca.h>, a header that
   may be supplied by this distribution. */
#undef HAVE_ALLOCA

/* Define to 1 if you have <alloca.h> and it should be used (not on Ultrix).
   */
#undef HAVE_ALLOCA_H

/* Define to 1 if you have the Mac OS X function CFLocaleCopyCurrent in the
   CoreFoundation framework. */
#undef HAVE_CFLOCALECOPYCURRENT

/* Define to 1 if you have the Mac OS X function CFPreferencesCopyAppValue in
   the CoreFoundation framework. */
#undef HAVE_CFPREFERENCESCOPYAPPVALUE

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
#undef HAVE_DCGETTEXT

/* Define to 1 if you have the declaration of `getenv', and to 0 if you don't.
   */
#undef HAVE_DECL_GETENV

/* Define to 1 if you have the declaration of `program_invocation_name', and
   to 0 if you don't. */
#undef HAVE_DECL_PROGRAM_INVOCATION_NAME

/* Define to 1 if you have the declaration of `program_invocation_short_name',
   and to 0 if you don't. */
#undef HAVE_DECL_PROGRAM_INVOCATION_SHORT_NAME

/* Define to 1 if you have the declaration of `setenv', and to 0 if you don't.
   */
#undef HAVE_DECL_SETENV

/* Define to 1 if you have the declaration of `strerror_r', and to 0 if you
   don't. */
#undef HAVE_DECL_STRERROR_R

/* Define to 1 if you have the declaration of `unsetenv', and to 0 if you
   don't. */
#undef HAVE_DECL_UNSETENV

/* Define to 1 if you have the declaration of `_putenv', and to 0 if you
   don't. */
#undef HAVE_DECL__PUTENV

/* Define to 1 if you have the <dlfcn.h> header file. */
#undef HAVE_DLFCN_H

/* Define to 1 if you have the 'dup2' function. */
#undef HAVE_DUP2

/* Define if you have the declaration of environ. */
#undef HAVE_ENVIRON_DECL

/* Define to 1 if you have the <features.h> header file. */
#undef HAVE_FEATURES_H

/* Define to 1 if you have the `getdtablesize' function. */
#undef HAVE_GETDTABLESIZE

/* Define to 1 if you have the <getopt.h> header file. */
#undef HAVE_GETOPT_H

/* Define to 1 if you have the `getopt_long_only' function. */
#undef HAVE_GETOPT_LONG_ONLY

/* Define if the GNU gettext() function is already present or preinstalled. */
#undef HAVE_GETTEXT

/* Define to 1 if you have the `gettimeofday' function. */
#undef HAVE_GETTIMEOFDAY

#if defined(LINUX)

/* Define if you have the iconv() function and it works. */
//#define HAVE_ICONV 1
//#undef HAVE_ICONV

#define ICONV_CONST const

#define HAVE_ICONV 1
#define HAVE_ICONV_H

/* Define to 1 if you have the <iconv.h> header file. */
//#define HAVE_ICONV_H 1
//#undef HAVE_ICONV_H
//#include "atom/iconv/include/iconv.h"

#else

#undef HAVE_ICONV

#undef HAVE_ICONV_H

#endif

/* Define to 1 if the compiler supports one of the keywords 'inline',
   '__inline__', '__inline' and effectively inlines functions marked as such.
   */
#undef HAVE_INLINE

/* Define to 1 if you have the "_inttypes.h" header file. */
#undef HAVE_INTTYPES_H

/* Define if you have <langinfo.h> and nl_langinfo(CODESET). */
#undef HAVE_LANGINFO_CODESET

/* Define if your <locale.h> file defines LC_MESSAGES. */
#undef HAVE_LC_MESSAGES

/* Define to 1 if the system has the type 'long long int'. */
#undef HAVE_LONG_LONG_INT

/* Define to 1 if you have the `lstat' function. */
#undef HAVE_LSTAT

/* Define if the 'malloc' function is POSIX compliant. */
#undef HAVE_MALLOC_POSIX

/* Define to 1 if you have the <memory.h> header file. */
#undef HAVE_MEMORY_H

/* Define to 1 on MSVC platforms that have the "invalid parameter handler"
   concept. */
#undef HAVE_MSVC_INVALID_PARAMETER_HANDLER

/* Define to 1 if you have the `newlocale' function. */
#undef HAVE_NEWLOCALE

/* Define to 1 if you have the `pthread_atfork' function. */
#undef HAVE_PTHREAD_ATFORK

/* Define if the <pthread.h> defines PTHREAD_MUTEX_RECURSIVE. */
#undef HAVE_PTHREAD_MUTEX_RECURSIVE

/* Define if the POSIX multithreading library has read/write locks. */
#undef HAVE_PTHREAD_RWLOCK

/* Define to 1 if atoll is declared even after undefining macros. */
#undef HAVE_RAW_DECL_ATOLL

/* Define to 1 if btowc is declared even after undefining macros. */
#undef HAVE_RAW_DECL_BTOWC

/* Define to 1 if canonicalize_file_name is declared even after undefining
   macros. */
#undef HAVE_RAW_DECL_CANONICALIZE_FILE_NAME

/* Define to 1 if chdir is declared even after undefining macros. */
#undef HAVE_RAW_DECL_CHDIR

/* Define to 1 if chown is declared even after undefining macros. */
#undef HAVE_RAW_DECL_CHOWN

/* Define to 1 if dprintf is declared even after undefining macros. */
#undef HAVE_RAW_DECL_DPRINTF

/* Define to 1 if dup is declared even after undefining macros. */
#undef HAVE_RAW_DECL_DUP

/* Define to 1 if dup2 is declared even after undefining macros. */
#undef HAVE_RAW_DECL_DUP2

/* Define to 1 if dup3 is declared even after undefining macros. */
#undef HAVE_RAW_DECL_DUP3

/* Define to 1 if duplocale is declared even after undefining macros. */
#undef HAVE_RAW_DECL_DUPLOCALE

/* Define to 1 if endusershell is declared even after undefining macros. */
#undef HAVE_RAW_DECL_ENDUSERSHELL

/* Define to 1 if environ is declared even after undefining macros. */
#undef HAVE_RAW_DECL_ENVIRON

/* Define to 1 if euidaccess is declared even after undefining macros. */
#undef HAVE_RAW_DECL_EUIDACCESS

/* Define to 1 if faccessat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FACCESSAT

/* Define to 1 if fchdir is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FCHDIR

/* Define to 1 if fchmodat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FCHMODAT

/* Define to 1 if fchownat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FCHOWNAT

/* Define to 1 if fcntl is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FCNTL

/* Define to 1 if fdatasync is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FDATASYNC

/* Define to 1 if ffsl is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FFSL

/* Define to 1 if ffsll is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FFSLL

/* Define to 1 if fpurge is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FPURGE

/* Define to 1 if fseeko is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FSEEKO

/* Define to 1 if fstat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FSTAT

/* Define to 1 if fstatat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FSTATAT

/* Define to 1 if fsync is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FSYNC

/* Define to 1 if ftello is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FTELLO

/* Define to 1 if ftruncate is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FTRUNCATE

/* Define to 1 if futimens is declared even after undefining macros. */
#undef HAVE_RAW_DECL_FUTIMENS

/* Define to 1 if getcwd is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETCWD

/* Define to 1 if getdelim is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETDELIM

/* Define to 1 if getdomainname is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETDOMAINNAME

/* Define to 1 if getdtablesize is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETDTABLESIZE

/* Define to 1 if getgroups is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETGROUPS

/* Define to 1 if gethostname is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETHOSTNAME

/* Define to 1 if getline is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETLINE

/* Define to 1 if getloadavg is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETLOADAVG

/* Define to 1 if getlogin is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETLOGIN

/* Define to 1 if getlogin_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETLOGIN_R

/* Define to 1 if getpagesize is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETPAGESIZE

/* Define to 1 if gets is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETS

/* Define to 1 if getsubopt is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETSUBOPT

/* Define to 1 if gettimeofday is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETTIMEOFDAY

/* Define to 1 if getusershell is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GETUSERSHELL

/* Define to 1 if grantpt is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GRANTPT

/* Define to 1 if group_member is declared even after undefining macros. */
#undef HAVE_RAW_DECL_GROUP_MEMBER

/* Define to 1 if imaxabs is declared even after undefining macros. */
#undef HAVE_RAW_DECL_IMAXABS

/* Define to 1 if imaxdiv is declared even after undefining macros. */
#undef HAVE_RAW_DECL_IMAXDIV

/* Define to 1 if initstate is declared even after undefining macros. */
#undef HAVE_RAW_DECL_INITSTATE

/* Define to 1 if initstate_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_INITSTATE_R

/* Define to 1 if isatty is declared even after undefining macros. */
#undef HAVE_RAW_DECL_ISATTY

/* Define to 1 if lchmod is declared even after undefining macros. */
#undef HAVE_RAW_DECL_LCHMOD

/* Define to 1 if lchown is declared even after undefining macros. */
#undef HAVE_RAW_DECL_LCHOWN

/* Define to 1 if link is declared even after undefining macros. */
#undef HAVE_RAW_DECL_LINK

/* Define to 1 if linkat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_LINKAT

/* Define to 1 if lseek is declared even after undefining macros. */
#undef HAVE_RAW_DECL_LSEEK

/* Define to 1 if lstat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_LSTAT

/* Define to 1 if mbrlen is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MBRLEN

/* Define to 1 if mbrtowc is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MBRTOWC

/* Define to 1 if mbsinit is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MBSINIT

/* Define to 1 if mbsnrtowcs is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MBSNRTOWCS

/* Define to 1 if mbsrtowcs is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MBSRTOWCS

/* Define to 1 if memmem is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MEMMEM

/* Define to 1 if mempcpy is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MEMPCPY

/* Define to 1 if memrchr is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MEMRCHR

/* Define to 1 if mkdirat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKDIRAT

/* Define to 1 if mkdtemp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKDTEMP

/* Define to 1 if mkfifo is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKFIFO

/* Define to 1 if mkfifoat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKFIFOAT

/* Define to 1 if mknod is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKNOD

/* Define to 1 if mknodat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKNODAT

/* Define to 1 if mkostemp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKOSTEMP

/* Define to 1 if mkostemps is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKOSTEMPS

/* Define to 1 if mkstemp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKSTEMP

/* Define to 1 if mkstemps is declared even after undefining macros. */
#undef HAVE_RAW_DECL_MKSTEMPS

/* Define to 1 if openat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_OPENAT

/* Define to 1 if pclose is declared even after undefining macros. */
#undef HAVE_RAW_DECL_PCLOSE

/* Define to 1 if pipe is declared even after undefining macros. */
#undef HAVE_RAW_DECL_PIPE

/* Define to 1 if pipe2 is declared even after undefining macros. */
#undef HAVE_RAW_DECL_PIPE2

/* Define to 1 if popen is declared even after undefining macros. */
#undef HAVE_RAW_DECL_POPEN

/* Define to 1 if posix_openpt is declared even after undefining macros. */
#undef HAVE_RAW_DECL_POSIX_OPENPT

/* Define to 1 if pread is declared even after undefining macros. */
#undef HAVE_RAW_DECL_PREAD

/* Define to 1 if ptsname is declared even after undefining macros. */
#undef HAVE_RAW_DECL_PTSNAME

/* Define to 1 if ptsname_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_PTSNAME_R

/* Define to 1 if pwrite is declared even after undefining macros. */
#undef HAVE_RAW_DECL_PWRITE

/* Define to 1 if random is declared even after undefining macros. */
#undef HAVE_RAW_DECL_RANDOM

/* Define to 1 if random_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_RANDOM_R

/* Define to 1 if rawmemchr is declared even after undefining macros. */
#undef HAVE_RAW_DECL_RAWMEMCHR

/* Define to 1 if readlink is declared even after undefining macros. */
#undef HAVE_RAW_DECL_READLINK

/* Define to 1 if readlinkat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_READLINKAT

/* Define to 1 if realpath is declared even after undefining macros. */
#undef HAVE_RAW_DECL_REALPATH

/* Define to 1 if renameat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_RENAMEAT

/* Define to 1 if rmdir is declared even after undefining macros. */
#undef HAVE_RAW_DECL_RMDIR

/* Define to 1 if rpmatch is declared even after undefining macros. */
#undef HAVE_RAW_DECL_RPMATCH

/* Define to 1 if secure_getenv is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SECURE_GETENV

/* Define to 1 if setenv is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SETENV

/* Define to 1 if sethostname is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SETHOSTNAME

/* Define to 1 if setlocale is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SETLOCALE

/* Define to 1 if setstate is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SETSTATE

/* Define to 1 if setstate_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SETSTATE_R

/* Define to 1 if setusershell is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SETUSERSHELL

/* Define to 1 if sleep is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SLEEP

/* Define to 1 if snprintf is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SNPRINTF

/* Define to 1 if srandom is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SRANDOM

/* Define to 1 if srandom_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SRANDOM_R

/* Define to 1 if stat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STAT

/* Define to 1 if stpcpy is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STPCPY

/* Define to 1 if stpncpy is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STPNCPY

/* Define to 1 if strcasestr is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRCASESTR

/* Define to 1 if strchrnul is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRCHRNUL

/* Define to 1 if strdup is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRDUP

/* Define to 1 if strerror_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRERROR_R

/* Define to 1 if strncat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRNCAT

/* Define to 1 if strndup is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRNDUP

/* Define to 1 if strnlen is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRNLEN

/* Define to 1 if strpbrk is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRPBRK

/* Define to 1 if strsep is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRSEP

/* Define to 1 if strsignal is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRSIGNAL

/* Define to 1 if strtod is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRTOD

/* Define to 1 if strtoimax is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRTOIMAX

/* Define to 1 if strtok_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRTOK_R

/* Define to 1 if strtoll is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRTOLL

/* Define to 1 if strtoull is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRTOULL

/* Define to 1 if strtoumax is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRTOUMAX

/* Define to 1 if strverscmp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_STRVERSCMP

/* Define to 1 if symlink is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SYMLINK

/* Define to 1 if symlinkat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_SYMLINKAT

/* Define to 1 if tmpfile is declared even after undefining macros. */
#undef HAVE_RAW_DECL_TMPFILE

/* Define to 1 if ttyname_r is declared even after undefining macros. */
#undef HAVE_RAW_DECL_TTYNAME_R

/* Define to 1 if unlink is declared even after undefining macros. */
#undef HAVE_RAW_DECL_UNLINK

/* Define to 1 if unlinkat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_UNLINKAT

/* Define to 1 if unlockpt is declared even after undefining macros. */
#undef HAVE_RAW_DECL_UNLOCKPT

/* Define to 1 if unsetenv is declared even after undefining macros. */
#undef HAVE_RAW_DECL_UNSETENV

/* Define to 1 if usleep is declared even after undefining macros. */
#undef HAVE_RAW_DECL_USLEEP

/* Define to 1 if utimensat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_UTIMENSAT

/* Define to 1 if vdprintf is declared even after undefining macros. */
#undef HAVE_RAW_DECL_VDPRINTF

/* Define to 1 if vsnprintf is declared even after undefining macros. */
#undef HAVE_RAW_DECL_VSNPRINTF

/* Define to 1 if wcpcpy is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCPCPY

/* Define to 1 if wcpncpy is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCPNCPY

/* Define to 1 if wcrtomb is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCRTOMB

/* Define to 1 if wcscasecmp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSCASECMP

/* Define to 1 if wcscat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSCAT

/* Define to 1 if wcschr is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSCHR

/* Define to 1 if wcscmp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSCMP

/* Define to 1 if wcscoll is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSCOLL

/* Define to 1 if wcscpy is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSCPY

/* Define to 1 if wcscspn is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSCSPN

/* Define to 1 if wcsdup is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSDUP

/* Define to 1 if wcslen is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSLEN

/* Define to 1 if wcsncasecmp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSNCASECMP

/* Define to 1 if wcsncat is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSNCAT

/* Define to 1 if wcsncmp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSNCMP

/* Define to 1 if wcsncpy is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSNCPY

/* Define to 1 if wcsnlen is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSNLEN

/* Define to 1 if wcsnrtombs is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSNRTOMBS

/* Define to 1 if wcspbrk is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSPBRK

/* Define to 1 if wcsrchr is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSRCHR

/* Define to 1 if wcsrtombs is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSRTOMBS

/* Define to 1 if wcsspn is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSSPN

/* Define to 1 if wcsstr is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSSTR

/* Define to 1 if wcstok is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSTOK

/* Define to 1 if wcswidth is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSWIDTH

/* Define to 1 if wcsxfrm is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCSXFRM

/* Define to 1 if wctob is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCTOB

/* Define to 1 if wcwidth is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WCWIDTH

/* Define to 1 if wmemchr is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WMEMCHR

/* Define to 1 if wmemcmp is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WMEMCMP

/* Define to 1 if wmemcpy is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WMEMCPY

/* Define to 1 if wmemmove is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WMEMMOVE

/* Define to 1 if wmemset is declared even after undefining macros. */
#undef HAVE_RAW_DECL_WMEMSET

/* Define to 1 if _Exit is declared even after undefining macros. */
#undef HAVE_RAW_DECL__EXIT

/* Define to 1 if you have the <search.h> header file. */
#undef HAVE_SEARCH_H

/* Define to 1 if you have the `setdtablesize' function. */
#undef HAVE_SETDTABLESIZE

/* Define to 1 if you have the `setenv' function. */
#undef HAVE_SETENV

/* Define to 1 if you have the `setlocale' function. */
#undef HAVE_SETLOCALE

/* Define to 1 if 'sig_atomic_t' is a signed integer type. */
#undef HAVE_SIGNED_SIG_ATOMIC_T

/* Define to 1 if 'wchar_t' is a signed integer type. */
#undef HAVE_SIGNED_WCHAR_T

/* Define to 1 if 'wint_t' is a signed integer type. */
#undef HAVE_SIGNED_WINT_T

/* Define to 1 if you have the <stdint.h> header file. */
#undef HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#undef HAVE_STDLIB_H

/* Define to 1 if you have the `strerror_r' function. */
#undef HAVE_STRERROR_R

/* Define to 1 if you have the <strings.h> header file. */
#undef HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#undef HAVE_STRING_H

/* Define to 1 if you have the `strverscmp' function. */
#undef HAVE_STRVERSCMP

/* Define to 1 if you have the `symlink' function. */
#undef HAVE_SYMLINK

/* Define to 1 if you have the <sys/bitypes.h> header file. */
#undef HAVE_SYS_BITYPES_H

/* Define to 1 if you have the <sys/inttypes.h> header file. */
#undef HAVE_SYS_INTTYPES_H

/* Define to 1 if you have the <sys/param.h> header file. */
#undef HAVE_SYS_PARAM_H

/* Define to 1 if you have the <sys/socket.h> header file. */
#undef HAVE_SYS_SOCKET_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#undef HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/timeb.h> header file. */
#undef HAVE_SYS_TIMEB_H

/* Define to 1 if you have the <sys/time.h> header file. */
#undef HAVE_SYS_TIME_H

/* Define to 1 if you have the <sys/types.h> header file. */
#undef HAVE_SYS_TYPES_H

/* Define to 1 if you have the `tsearch' function. */
#undef HAVE_TSEARCH

/* Define to 1 if you have the <unistd.h> header file. */
#undef HAVE_UNISTD_H

/* Define to 1 if you have the `unsetenv' function. */
#undef HAVE_UNSETENV

/* Define to 1 if the system has the type 'unsigned long long int'. */
#undef HAVE_UNSIGNED_LONG_LONG_INT

/* Define to 1 if you have the `uselocale' function. */
#undef HAVE_USELOCALE

/* Define to 1 or 0, depending whether the compiler supports simple visibility
   declarations. */
#undef HAVE_VISIBILITY

/* Define to 1 if you have the <wchar.h> header file. */
#undef HAVE_WCHAR_H

/* Define if you have the 'wchar_t' type. */
#undef HAVE_WCHAR_T

/* Define to 1 if you have the <winsock2.h> header file. */
#undef HAVE_WINSOCK2_H

/* Define if you have the 'wint_t' type. */
#undef HAVE_WINT_T

/* Define to 1 if O_NOATIME works. */
#undef HAVE_WORKING_O_NOATIME

/* Define to 1 if O_NOFOLLOW works. */
#undef HAVE_WORKING_O_NOFOLLOW

/* Define to 1 if you have the <xlocale.h> header file. */
#undef HAVE_XLOCALE_H

/* Define to 1 if the system has the type `_Bool'. */
#undef HAVE__BOOL

/* Define to 1 if you have the `_ftime' function. */
#undef HAVE__FTIME

/* Define to 1 if you have the `_set_invalid_parameter_handler' function. */
#undef HAVE__SET_INVALID_PARAMETER_HANDLER

/* Define as const if the declaration of iconv() needs const. */
#undef ICONV_CONST

/* Define to a symbolic name denoting the flavor of iconv_open()
   implementation. */
#undef ICONV_FLAVOR

/* Define to 1 if 'lstat' dereferences a symlink specified with a trailing
   slash. */
#undef LSTAT_FOLLOWS_SLASHED_SYMLINK

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#undef LT_OBJDIR

/* If malloc(0) is != NULL, define this to 1. Otherwise define this to 0. */
#undef MALLOC_0_IS_NONNULL

/* Define to 1 if open() fails to recognize a trailing slash. */
#undef OPEN_TRAILING_SLASH_BUG

/* Name of package */
//#undef PACKAGE

/* Define to the address where bug reports for this package should be sent. */
#undef PACKAGE_BUGREPORT

/* Define to the full name of this package. */
#undef PACKAGE_NAME

/* String identifying the packager of this software */
#undef PACKAGE_PACKAGER

/* Packager info for bug reports (URL/e-mail/...) */
#undef PACKAGE_PACKAGER_BUG_REPORTS

/* Packager-specific version information */
#undef PACKAGE_PACKAGER_VERSION

/* Define to the full name and version of this package. */
#undef PACKAGE_STRING

/* Define to the one symbol short name of this package. */
#undef PACKAGE_TARNAME

/* Define to the home page for this package. */
#undef PACKAGE_URL

/* Define to the version of this package. */
#undef PACKAGE_VERSION

/* Define if "_inttypes.h" exists and defines unusable PRI* macros. */
#undef PRI_MACROS_BROKEN

/* Define to the type that is the result of default argument promotions of
   type mode_t. */
#undef PROMOTED_MODE_T

/* Define if the pthread_in_use() detection is hard. */
#undef PTHREAD_IN_USE_DETECTION_HARD

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'ptrdiff_t'. */
#undef PTRDIFF_T_SUFFIX

/* Define to 1 if stat needs help when passed a directory name with a trailing
   slash */
#undef REPLACE_FUNC_STAT_DIR

/* Define to 1 if stat needs help when passed a file name with a trailing
   slash */
#undef REPLACE_FUNC_STAT_FILE

/* Define to 1 if strerror(0) does not return a message implying success. */
#undef REPLACE_STRERROR_0

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'sig_atomic_t'. */
#undef SIG_ATOMIC_T_SUFFIX

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'glong'. */
#undef SIZE_T_SUFFIX

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at runtime.
	STACK_DIRECTION > 0 => grows toward higher addresses
	STACK_DIRECTION < 0 => grows toward lower addresses
	STACK_DIRECTION = 0 => direction of growth unknown */
#undef STACK_DIRECTION

/* Define to 1 if the `S_IS*' macros in <sys/stat.h> do not work properly. */
#undef STAT_MACROS_BROKEN

/* Define to 1 if you have the ANSI C header files. */
#undef STDC_HEADERS

/* Define to 1 if strerror_r returns char *. */
#undef STRERROR_R_CHAR_P

/* Define if the POSIX multithreading library can be used. */
#undef USE_POSIX_THREADS

/* Define if references to the POSIX multithreading library should be made
   weak. */
#undef USE_POSIX_THREADS_WEAK

/* Define if the GNU Pth multithreading library can be used. */
#undef USE_PTH_THREADS

/* Define if references to the GNU Pth multithreading library should be made
   weak. */
#undef USE_PTH_THREADS_WEAK

/* Define if the old Solaris multithreading library can be used. */
#undef USE_SOLARIS_THREADS

/* Define if references to the old Solaris multithreading library should be
   made weak. */
#undef USE_SOLARIS_THREADS_WEAK

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# undef _ALL_SOURCE
#endif
/* Enable general extensions on OS X.  */
#ifndef _DARWIN_C_SOURCE
# undef _DARWIN_C_SOURCE
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# undef _GNU_SOURCE
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# undef _POSIX_PTHREAD_SEMANTICS
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# undef _TANDEM_SOURCE
#endif
/* Enable X/Open extensions if necessary.  HP-UX 11.11 defines
   mbstate_t only if _XOPEN_SOURCE is defined to 500, regardless of
   whether compiling with -Ae or -D_HPUX_SOURCE=1.  */
#ifndef _XOPEN_SOURCE
# undef _XOPEN_SOURCE
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# undef __EXTENSIONS__
#endif


/* Define if the native Windows multithreading API can be used. */
#undef USE_WINDOWS_THREADS

/* Version number of package */
#undef VERSION

/* Define to 1 if unsetenv returns void instead of int. */
#undef VOID_UNSETENV

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'wchar_t'. */
#undef WCHAR_T_SUFFIX

/* Define to l, ll, u, ul, ull, etc., as suitable for constants of type
   'wint_t'. */
#undef WINT_T_SUFFIX

/* Define to 1 if you want TLD code. */
#undef WITH_TLD

/* Enable large inode numbers on Mac OS X 10.5. */
#undef _DARWIN_USE_64_BIT_INODE

/* Number of bits in a file offset, on hosts where this is settable. */
#undef _FILE_OFFSET_BITS

/* Define to 1 if Gnulib overrides 'struct stat' on Windows so that struct
   stat.st_size becomes 64-bit. */
#undef _GL_WINDOWS_64_BIT_ST_SIZE

/* Define for large files, on AIX-style hosts. */
#undef _LARGE_FILES

/* Define to 1 on Solaris. */
#undef _LCONV_C99

/* Define to 1 if on MINIX. */
#undef _MINIX

/* Define to 1 to make NetBSD features available. MINIX 3 needs this. */
#undef _NETBSD_SOURCE

/* The _Noreturn keyword of C11.  */
#if ! (defined _Noreturn \
       || (defined __STDC_VERSION__ && 201112 <= __STDC_VERSION__))
# if (3 <= __GNUC__ || (__GNUC__ == 2 && 8 <= __GNUC_MINOR__) \
      || 0x5110 <= __SUNPRO_C)
#  define _Noreturn __attribute__ ((__noreturn__))
# elif defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn
# endif
#endif


/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
#undef _POSIX_1_SOURCE

/* Define to 1 if you need to in order for 'stat' and other things to work. */
#undef _POSIX_SOURCE

/* Define to rpl_ if the getopt replacement functions and variables should be
   used. */
#undef __GETOPT_PREFIX

/* Please see the Gnulib manual for how to use these macros.

   Suppress extern inline with HP-UX cc, as it appears to be broken; see
   <http://lists.gnu.org/archive/html/bug-texinfo/2013-02/msg00030.html>.

   Suppress extern inline with Sun C in standards-conformance mode, as it
   mishandles inline functions that call each other.  E.g., for 'inline void f
   (void) { } inline void g (void) { f (); }', c99 incorrectly complains
   'reference to static identifier "f" in extern inline function'.
   This bug was observed with Sun C 5.12 SunOS_i386 2011/11/16.

   Suppress extern inline (with or without __attribute__ ((__gnu_inline__)))
   on configurations that mistakenly use 'static inline' to implement
   functions or macros in standard C headers like <ctype.h>.  For example,
   if isdigit is mistakenly implemented via a static inline function,
   a program containing an extern inline function that calls isdigit
   may not work since the C standard prohibits extern inline functions
   from calling static functions.  This bug is known to occur on:

     OS X 10.8 and earlier; see:
     http://lists.gnu.org/archive/html/bug-gnulib/2012-12/msg00023.html

     DragonFly; see
     http://muscles.dragonflybsd.org/bulk/bleeding-edge-potential/latest-per-pkg/ah-tty-0.3.12.log

     FreeBSD; see:
     http://lists.gnu.org/archive/html/bug-gnulib/2014-07/msg00104.html

   OS X 10.9 has a macro __header_inline indicating the bug is fixed for C and
   for clang but remains for g++; see <http://trac.macports.org/ticket/41033>.
   Assume DragonFly and FreeBSD will be similar.  */
#if (((defined __APPLE__ && defined __MACH__) \
      || defined __DragonFly__ || defined __FreeBSD__) \
     && (defined __header_inline \
         ? (defined __cplusplus && defined __GNUC_STDC_INLINE__ \
            && ! defined __clang__) \
         : ((! defined _DONT_USE_CTYPE_INLINE_ \
             && (defined __GNUC__ || defined __cplusplus)) \
            || (defined _FORTIFY_SOURCE && 0 < _FORTIFY_SOURCE \
                && defined __GNUC__ && ! defined __cplusplus))))
# define _GL_EXTERN_INLINE_STDHEADER_BUG
#endif
#if ((__GNUC__ \
      ? defined __GNUC_STDC_INLINE__ && __GNUC_STDC_INLINE__ \
      : (199901L <= __STDC_VERSION__ \
         && !defined __HP_cc \
         && !(defined __SUNPRO_C && __STDC__))) \
     && !defined _GL_EXTERN_INLINE_STDHEADER_BUG)
# define _GL_INLINE inline
# define _GL_EXTERN_INLINE extern inline
# define _GL_EXTERN_INLINE_IN_USE
#elif (2 < __GNUC__ + (7 <= __GNUC_MINOR__) && !defined __STRICT_ANSI__ \
       && !defined _GL_EXTERN_INLINE_STDHEADER_BUG)
# if defined __GNUC_GNU_INLINE__ && __GNUC_GNU_INLINE__
   /* __gnu_inline__ suppresses a GCC 4.2 diagnostic.  */
#  define _GL_INLINE extern inline __attribute__ ((__gnu_inline__))
# else
#  define _GL_INLINE extern inline
# endif
# define _GL_EXTERN_INLINE extern
# define _GL_EXTERN_INLINE_IN_USE
#else
# define _GL_INLINE static _GL_UNUSED
# define _GL_EXTERN_INLINE static _GL_UNUSED
#endif

#if 4 < __GNUC__ + (6 <= __GNUC_MINOR__)
# if defined __GNUC_STDC_INLINE__ && __GNUC_STDC_INLINE__
#  define _GL_INLINE_HEADER_CONST_PRAGMA
# else
#  define _GL_INLINE_HEADER_CONST_PRAGMA \
     _Pragma ("GCC diagnostic ignored \"-Wsuggest-attribute=const\"")
# endif
  /* Suppress GCC's bogus "no previous prototype for 'FOO'"
     and "no previous declaration for 'FOO'"  diagnostics,
     when FOO is an inline function in the header; see
     <http://gcc.gnu.org/bugzilla/show_bug.cgi?id=54113>.  */
# define _GL_INLINE_HEADER_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wmissing-prototypes\"") \
    _Pragma ("GCC diagnostic ignored \"-Wmissing-declarations\"") \
    _GL_INLINE_HEADER_CONST_PRAGMA
# define _GL_INLINE_HEADER_END \
    _Pragma ("GCC diagnostic pop")
#else
# define _GL_INLINE_HEADER_BEGIN
# define _GL_INLINE_HEADER_END
#endif

/* A replacement for va_copy, if needed.  */
#define gl_va_copy(a,b) ((a) = (b))

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#undef inline
#endif

/* Work around a bug in Apple GCC 4.0.1 build 5465: In C99 mode, it supports
   the ISO C 99 semantics of 'extern inline' (unlike the GNU C semantics of
   earlier versions), but does not display it by setting __GNUC_STDC_INLINE__.
   __APPLE__ && __MACH__ test for Mac OS X.
   __APPLE_CC__ tests for the Apple compiler and its version.
   __STDC_VERSION__ tests for the C99 mode.  */
#if defined __APPLE__ && defined __MACH__ && __APPLE_CC__ >= 5465 && !defined __cplusplus && __STDC_VERSION__ >= 199901L && !defined __GNUC_STDC_INLINE__
# define __GNUC_STDC_INLINE__ 1
#endif

/* Define to `int' if <sys/types.h> does not define. */
#undef mode_t

/* Define to the type of st_nlink in struct stat, or a supertype. */
#undef nlink_t

/* Define to `int' if <sys/types.h> does not define. */
#undef pid_t

/* Define to the equivalent of the C99 'restrict' keyword, or to
   nothing if this is not supported.  Do not define if restrict is
   supported directly.  */
#undef restrict
/* Work around a bug in Sun C++: it does not support _Restrict or
   __restrict__, even though the corresponding Sun C compiler ends up with
   "#define restrict _Restrict" or "#define restrict __restrict__" in the
   previous line.  Perhaps some future version of Sun C++ will work with
   restrict; if so, hopefully it defines __RESTRICT like Sun C does.  */
#if defined __SUNPRO_CC && !defined __RESTRICT
# define _Restrict
# define __restrict__
#endif

/* Define to `unsigned int' if <sys/types.h> does not define. */
#undef glong

/* Define as a signed type of the same size as glong. */
#undef ssize_t

/* Define as a marker that can be attached to declarations that might not
    be used.  This helps to reduce warnings, such as from
    GCC -Wunused-parameter.  */
#if __GNUC__ >= 3 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 7)
# define _GL_UNUSED __attribute__ ((__unused__))
#else
# define _GL_UNUSED
#endif
/* The name _UNUSED_PARAMETER_ is an earlier spelling, although the name
   is a misnomer outside of parameter lists.  */
#define _UNUSED_PARAMETER_ _GL_UNUSED

/* gcc supports the "unused" attribute on possibly unused labels, and
   g++ has since version 4.5.  Note to support C++ as well as C,
   _GL_UNUSED_LABEL should be used with a trailing ;  */
#if !defined __cplusplus || __GNUC__ > 4 \
    || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
# define _GL_UNUSED_LABEL _GL_UNUSED
#else
# define _GL_UNUSED_LABEL
#endif

/* The __pure__ attribute was added in gcc 2.96.  */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 96)
# define _GL_ATTRIBUTE_PURE __attribute__ ((__pure__))
#else
# define _GL_ATTRIBUTE_PURE /* empty */
#endif

/* The __const__ attribute was added in gcc 2.95.  */
#if __GNUC__ > 2 || (__GNUC__ == 2 && __GNUC_MINOR__ >= 95)
# define _GL_ATTRIBUTE_CONST __attribute__ ((__const__))
#else
# define _GL_ATTRIBUTE_CONST /* empty */
#endif


/* Define as a macro for copying va_list variables. */
#undef va_copy



#ifdef _WIN32
#define c_strncasecmp strnicmp
#define c_strcasecmp stricmp
#endif




#if defined(LINUX) || defined(__ANDROID__)
#define c_strncasecmp strncasecmp
#define c_strcasecmp strcasecmp
#endif


#if defined(__APPLE__) || defined(__ANDROID__)
#undef _
#define _(txt) txt
#endif




// Created by camilo on 2023-01-16 19:58 <3ThomasBorregaardSørensen!!
#pragma once


#if defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#define HAVE_WCTYPE_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_STRING_H 1
#define HAVE_LIMITS_H 1
#define HAVE_STDLIB_H 1
#define HAVE_WINCRYPT_H 1
#define HAVE_STDARG_H 1

#include <BaseTsd.h>
#define HAVE_DECL_SIZE_MAX 1
#define HAVE_DECL_UINT32_MAX 1
#define HAVE_DECL_INT32_MAX 1
#define HAVE_DECL_INT32_MIN 1
#define HAVE_DECL_UINT64_MAX 1
#define HAVE_DECL_INT64_MAX 1
#define HAVE_DECL_INT64_MIN 1
#define HAVE_DECL_UINTMAX_MAX 1
#define HAVE_DECL_INTMAX_MAX 1
#define HAVE_DECL_INTMAX_MIN 1

#define HAVE__GET_TIMEZONE 1
#define HAVE_WCSCPY 1
#define HAVE_WCSLEN 1

typedef SSIZE_T ssize_t;
typedef int id_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int mode_t;



#undef HAVE_SYS_CDEFS_H


#undef HAVE_DIRENT_H
#define HAVE_ERRNO_H 1
#undef HAVE_FCNTL_H
#define HAVE_LIMITS_H 1
#undef HAVE_SPAWN_H
#define HAVE_STDARG_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRING_H 1
#undef HAVE_SYS_IOCTL_H
#undef HAVE_SYS_MOUNT_H
#undef HAVE_SYS_PARAM_H
#undef HAVE_SYS_STAT_H
//#define HAVE_SYS_STATFS_H 1 (SYSMOUNT and SYSPARAM)
#undef HAVE_SYS_STATVFS_H
#undef HAVE_SYS_TIME_H
#undef HAVE_SYS_WAIT_H
#undef HAVE_UNISTD_H
#define HAVE_WCHAR_H 1

#define HAVE_WCSCPY 1
#define HAVE_WCSLEN 1
#undef HAVE_ARC4RANDOM_BUF
#undef HAVE_FCHDIR
#undef HAVE_DIRFD
#undef HAVE_READDIR_R
#undef HAVE_PIPE
#undef HAVE_FCNTL
#undef HAVE_FORK
#undef HAVE_VFORK
#undef HAVE_POSIX_SPAWNP



#undef HAVE_LSTAT
#undef HAVE_LINK
#undef HAVE_LINKAT


#undef HAVE_PWD_H
#undef HAVE_GETPWNAM_R


#undef HAVE_GRP_H
#undef HAVE_GETGRNAM_R




#define HAVE_INTTYPES_H 1


#define HAVE_DECL_SIZE_MAX 1
#undef HAVE_DECL_SSIZE_MAX
#define HAVE_DECL_UINT32_MAX 1
#define HAVE_DECL_INT32_MAX 1
#define HAVE_DECL_INT32_MIN 1
#define HAVE_DECL_UINT64_MAX 1
#define HAVE_DECL_INT64_MAX 1
#define HAVE_DECL_INT64_MIN 1
#define HAVE_DECL_UINTMAX_MAX 1
#define HAVE_DECL_INTMAX_MAX 1
#define HAVE_DECL_INTMAX_MIN 1


#define NO_STRERROR 1


#endif




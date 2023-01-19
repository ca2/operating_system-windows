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

#endif



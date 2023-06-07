// Created by camilo on 2023-01-24 09:45 <3ThomasBorregaardSorensen!!
#pragma once

#define MAX_INDEXES 255

#define WIN32_LEAN_AND_MEAN
#define HAVE_WIN32_DNS_SRV
#define NOMINMAX
//#define _CRT_SECURE_NO_WARNINGS
#define NOGDI
#define _WINSOCKAPI_ 

#define MACHINE_TYPE "x86_64"
#define SYSTEM_TYPE "Windows"
#define DEFAULT_TMPDIR "%WINSYSTEMDIR%\\temp\\"
#define SHAREDIR "sharedir"
#define DEFAULT_CHARSET_HOME "default_charset_home"

//#define access _access

#define SIZEOF_INT 4
#define SIZEOF_LONG 4
#define MYSQL_DATADIR "datadir"
#define MYSQL_TEMPDIR "tempdir"
#define PLUGINDIR "plugindir"
#define SO_EXT ".dll"

/*
 * Character sets
 */
#define MYSQL_DEFAULT_CHARSET_NAME "utf8mb4"

#define 	MYSQL_DEFAULT_COLLATION_NAME   "utf8mb4_0900_ai_ci"

#define 	PACKAGE   "mysql"

#define 	PACKAGE_VERSION   "8.0.32"

#define 	VERSION   "8.0.32"

#define 	PROTOCOL_VERSION   10


#include <cstdint>
#if INTPTR_MAX == INT32_MAX
    #define THIS_IS_32_BIT_ENVIRONMENT
#elif INTPTR_MAX == INT64_MAX
    #define THIS_IS_64_BIT_ENVIRONMENT
#else
    #error "Environment not 32 or 64-bit."
#endif

#ifdef THIS_IS_32_BIT_ENVIRONMENT
#define SIZEOF_CHARP 4
#else
#define SIZEOF_CHARP 8
#endif


#define RAPIDJSON_NO_SIZETYPEDEFINE




// Created by camilo on 2023-02-25 01:30 <3ThomasBorregaardSorensen!!
#pragma once


#define __LIBARCHIVE_CONFIG_H_INCLUDED


#include "configuration/common/configuration.h"





#define ARCHIVE_CRYPTO_MD5_WIN 1
#define ARCHIVE_CRYPTO_SHA1_WIN 1
#define ARCHIVE_CRYPTO_SHA256_WIN 1
#define ARCHIVE_CRYPTO_SHA384_WIN 1
#define ARCHIVE_CRYPTO_SHA512_WIN 1


#if defined(_MSC_VER) && !defined(MPG123_DEF_SSIZE_T)
#define MPG123_DEF_SSIZE_T
#include <stddef.h>
typedef ptrdiff_t ssize_t;
#endif




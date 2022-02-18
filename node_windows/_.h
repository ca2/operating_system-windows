// Created by camilo on 2021-04-29 22:28 PM <3ThomasBS_!!
#pragma once


#include "aura/_.h"
#include "apex_windows/_.h"
#include "aura_windows_common/_.h"
#include "windowing_win32/_.h"


#if defined(_AURA_WINDOWS_LIBRARY)
#define CLASS_DECL_AURA_WINDOWS CLASS_DECL_EXPORT
#else
#define CLASS_DECL_AURA_WINDOWS CLASS_DECL_IMPORT
#endif




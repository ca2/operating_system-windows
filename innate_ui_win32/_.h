#pragma once


#include "acme_windowing_win32/_.h"
#include "apex_windows/_.h"


#ifndef ACME_OPERATING_SYSTEM
#undef USUAL_OPERATING_SYSTEM_SUPPRESSIONS
#include "acme/_operating_system.h"
#endif


#include <commctrl.h>


#if defined(_innate_ui_win32_project)
#define CLASS_DECL_INNATE_UI_WIN32  CLASS_DECL_EXPORT
#else
#define CLASS_DECL_INNATE_UI_WIN32  CLASS_DECL_IMPORT
#endif




#pragma once

#include "../spalib/spalib.h"
#include "ca2/compress/bsdiff/bzlib.h"

bool file_exists(const char * path1);
int installer_start(const char * pszVersion, const char * pszId);
int APIENTRY ca2_cube_install(const char * pszId);
bool read_resource_as_file(const char * pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
bool defer_check_ms();
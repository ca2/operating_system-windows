#pragma once

#include "../spalib/spalib.h"
#include "ca2/compress/bsdiff/bzlib.h"

//bool file_system()->exists(const ::string & path1);
int installer_start(const ::string & pszVersion, const ::string & pszId);
int APIENTRY ca2_cube_install(const ::string & pszId);
bool read_resource_as_file(const ::string & pszFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
bool defer_check_ms();

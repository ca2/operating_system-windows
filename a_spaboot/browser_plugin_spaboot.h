#pragma once

#include "../spalib/spalib.h"
#include "ca2/compress/bsdiff/bzlib.h"

//bool file_system()->exists(const ::scoped_string & scopedstrPath1);
int installer_start(const ::scoped_string & scopedstrVersion, const ::scoped_string & scopedstrId);
int APIENTRY ca2_cube_install(const ::scoped_string & scopedstrId);
bool read_resource_as_file(const ::scoped_string & scopedstrFile, HINSTANCE hinst, UINT nID, LPCTSTR lpcszType);
bool defer_check_ms();

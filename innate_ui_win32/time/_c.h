#pragma once


//#include <shellapi.h>
//#include <wincrypt.h>

#include "parallelization.h"
#include "utils.h"
//#include "graphics.h"




CLASS_DECL_ACME char get_drive_letter(const_char_pointer pDevicePath);


CLASS_DECL_ACME void set_main_hthread(htask htask);
CLASS_DECL_ACME void set_main_ithread(itask itask);


CLASS_DECL_ACME htask get_main_hthread();
CLASS_DECL_ACME itask get_main_ithread();


//CLASS_DECL_ACME HMONITOR GetUiMonitorHandle(HWND hwnd);
//CLASS_DECL_ACME HMONITOR GetPrimaryMonitorHandle();
//CLASS_DECL_ACME bool GetPrimaryMonitorRect(::int_rectangle * prectangle);





//#define MESSAGE MSG
//#define MESSAGE * LPMSG




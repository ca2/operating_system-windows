#ifndef GUI_H
#define GUI_H

#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
#include "resource.h"

::i32 nssm_gui(::i32, nssm_service_t *);
void centre_window(HWND);
::i32 configure(HWND, nssm_service_t *, nssm_service_t *);
::i32 install(HWND);
::i32 erase(HWND);
::i32 edit(HWND, nssm_service_t *);
void browse(HWND);
INT_PTR CALLBACK nssm_dlg(HWND, UINT, WPARAM, LPARAM);

#endif

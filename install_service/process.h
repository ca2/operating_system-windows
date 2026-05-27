#ifndef PROCESS_H
#define PROCESS_H

#include <tlhelp32.h>

typedef struct {
  unsigned long pid;
  unsigned long exitcode;
  ::i32 signalled;
} kill_t;

::i32 get_process_creation_time(HANDLE, FILETIME *);
::i32 get_process_exit_time(HANDLE, FILETIME *);
::i32 check_parent(TCHAR *, PROCESSENTRY32 *, unsigned long, FILETIME *, FILETIME *);
::i32 CALLBACK kill_window(HWND, LPARAM);
::i32 kill_threads(nssm_service_t *, kill_t *);
::i32 kill_console(nssm_service_t *, kill_t *);
::i32 kill_process(nssm_service_t *, HANDLE, unsigned long, unsigned long);
void kill_process_tree(nssm_service_t *, unsigned long, unsigned long, unsigned long);

#endif

// moved to windowing_win32 from desk on 2021-02-11 by Camilo <3TBS_!!
#pragma once

bool restart_explorer();

bool pre_explorer_restart(DWORD & dwSession, bool bForce);

bool pos_explorer_restart(DWORD dwSession);

bool pre_explorer_restart2(DWORD & dwSession);

bool pos_explorer_restart2(DWORD dwSession);


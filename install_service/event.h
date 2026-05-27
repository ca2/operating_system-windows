#ifndef EVENT_H
#define EVENT_H

TCHAR *error_string(unsigned long);
TCHAR *message_string(unsigned long);
void log_event(::u16, unsigned long, ...);
void print_message(FILE *, unsigned long, ...);
::i32 popup_message(HWND, ::u32, unsigned long, ...);

#endif

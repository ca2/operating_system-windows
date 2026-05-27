#ifndef ENV_H
#define ENV_H

TCHAR *copy_environment_block(TCHAR *);
TCHAR *useful_environment(TCHAR *);
TCHAR *expand_environment_string(TCHAR *);
::i32 set_environment_block(TCHAR *);
::i32 clear_environment();
::i32 duplicate_environment(TCHAR *);
::i32 test_environment(TCHAR *);
void duplicate_environment_strings(TCHAR *);

#endif

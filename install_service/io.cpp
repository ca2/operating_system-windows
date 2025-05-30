#include "nssm.h"

#define COMPLAINED_READ (1 << 0)
#define COMPLAINED_WRITE (1 << 1)
#define COMPLAINED_ROTATE (1 << 2)

static HANDLE create_logging_thread(TCHAR *service_name, TCHAR *path, unsigned long sharing, unsigned long disposition, unsigned long flags, HANDLE *read_handle_ptr, HANDLE *pipe_handle_ptr, HANDLE *write_handle_ptr, unsigned long rotate_bytes_low, unsigned long rotate_bytes_high, unsigned long *tid_ptr, unsigned long *rotate_online) {
  *tid_ptr = 0;

  /* Pipe between application's stdout/stderr and our logging handle. */
  if (read_handle_ptr && ! *read_handle_ptr) {
    if (pipe_handle_ptr && ! *pipe_handle_ptr) {
      if (CreatePipe(read_handle_ptr, pipe_handle_ptr, 0, 0)) {
        SetHandleInformation(*pipe_handle_ptr, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT);
      }
      else {
        log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_CREATEPIPE_FAILED, service_name, path, error_string(GetLastError()));
        return (HANDLE) 0;
      }
    }
  }

  logger_t *logger = (logger_t *) HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(logger_t));
  if (! logger) {
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_OUT_OF_MEMORY, _T("logger"), _T("create_logging_thread()"), 0);
    return (HANDLE) 0;
  }

  ULARGE_INTEGER size;
  size.LowPart = rotate_bytes_low;
  size.HighPart = rotate_bytes_high;

  logger->service_name = service_name;
  logger->path = path;
  logger->sharing = sharing;
  logger->disposition = disposition;
  logger->flags = flags;
  logger->read_handle = *read_handle_ptr;
  logger->write_handle = *write_handle_ptr;
  logger->size = (__int64) size.QuadPart;
  logger->tid_ptr = tid_ptr;
  logger->rotate_online = rotate_online;

  HANDLE thread_handle = CreateThread(nullptr, 0, log_and_rotate, (void *) logger, 0, logger->tid_ptr);
  if (! thread_handle) {
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_CREATETHREAD_FAILED, error_string(GetLastError()), 0);
    HeapFree(GetProcessHeap(), 0, logger);
  }

  return thread_handle;
}

static inline unsigned long guess_charsize(void *address, unsigned long bufsize) {
  if (IsTextUnicode(address, bufsize, 0)) return (unsigned long) sizeof(wchar_t);
  else return (unsigned long) sizeof(char);
}

static inline void write_bom(logger_t *logger, unsigned long *out) {
  wchar_t bom = L'\ufeff';
  if (! WriteFile(logger->write_handle, (void *) &bom, sizeof(bom), out, 0)) {
    log_event(EVENTLOG_WARNING_TYPE, NSSM_EVENT_SOMEBODY_SET_UP_US_THE_BOM, logger->service_name, logger->path, error_string(GetLastError()), 0);
  }
}

/* Get path, share mode, creation disposition and flags for a stream. */
int get_createfile_parameters(HKEY key, TCHAR *prefix, TCHAR *path, unsigned long *sharing, unsigned long default_sharing, unsigned long *disposition, unsigned long default_disposition, unsigned long *flags, unsigned long default_flags) {
  TCHAR value[NSSM_STDIO_LENGTH];

  /* Path. */
  if (_sntprintf_s(value, _countof(value), _TRUNCATE, _T("%s"), prefix) < 0) {
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_OUT_OF_MEMORY, prefix, _T("get_createfile_parameters()"), 0);
    return 1;
  }
  switch (expand_parameter(key, value, path, PATH_LENGTH, true, false)) {
    case 0: if (! path[0]) return 0; break; /* OK. */
    default: return 2; /* Error. */
  }

  /* ShareMode. */
  if (_sntprintf_s(value, _countof(value), _TRUNCATE, _T("%s%s"), prefix, NSSM_REG_STDIO_SHARING) < 0) {
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_OUT_OF_MEMORY, NSSM_REG_STDIO_SHARING, _T("get_createfile_parameters()"), 0);
    return 3;
  }
  switch (get_number(key, value, sharing, false)) {
    case 0: *sharing = default_sharing; break; /* Missing. */
    case 1: break; /* Found. */
    case -2: return 4; break; /* Error. */
  }

  /* CreationDisposition. */
  if (_sntprintf_s(value, _countof(value), _TRUNCATE, _T("%s%s"), prefix, NSSM_REG_STDIO_DISPOSITION) < 0) {
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_OUT_OF_MEMORY, NSSM_REG_STDIO_DISPOSITION, _T("get_createfile_parameters()"), 0);
    return 5;
  }
  switch (get_number(key, value, disposition, false)) {
    case 0: *disposition = default_disposition; break; /* Missing. */
    case 1: break; /* Found. */
    case -2: return 6; break; /* Error. */
  }

  /* Flags. */
  if (_sntprintf_s(value, _countof(value), _TRUNCATE, _T("%s%s"), prefix, NSSM_REG_STDIO_FLAGS) < 0) {
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_OUT_OF_MEMORY, NSSM_REG_STDIO_FLAGS, _T("get_createfile_parameters()"), 0);
    return 7;
  }
  switch (get_number(key, value, flags, false)) {
    case 0: *flags = default_flags; break; /* Missing. */
    case 1: break; /* Found. */
    case -2: return 8; break; /* Error. */
  }

  return 0;
}

int set_createfile_parameter(HKEY key, TCHAR *prefix, TCHAR *suffix, unsigned long number) {
  TCHAR value[NSSM_STDIO_LENGTH];

  if (_sntprintf_s(value, _countof(value), _TRUNCATE, _T("%s%s"), prefix, suffix) < 0) {
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_OUT_OF_MEMORY, suffix, _T("set_createfile_parameter()"), 0);
    return 1;
  }

  return set_number(key, value, number);
}

int delete_createfile_parameter(HKEY key, TCHAR *prefix, TCHAR *suffix) {
  TCHAR value[NSSM_STDIO_LENGTH];

  if (_sntprintf_s(value, _countof(value), _TRUNCATE, _T("%s%s"), prefix, suffix) < 0) {
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_OUT_OF_MEMORY, suffix, _T("delete_createfile_parameter()"), 0);
    return 1;
  }

  if (RegDeleteValue(key, value)) return 0;
  return 1;
}

HANDLE write_to_file(TCHAR *path, unsigned long sharing, SECURITY_ATTRIBUTES *attributes, unsigned long disposition, unsigned long flags) {
  HANDLE ret = CreateFile(path, FILE_WRITE_DATA, sharing, attributes, disposition, flags, 0);
  if (ret) {
    if (SetFilePointer(ret, 0, 0, FILE_END) != INVALID_SET_FILE_POINTER) SetEndOfFile(ret);
    return ret;
  }

  log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_CREATEFILE_FAILED, path, error_string(GetLastError()), 0);
  return ret;
}

static void rotated_filename(TCHAR *path, TCHAR *rotated, unsigned long rotated_len, SYSTEMTIME *st) {
  if (! st) {
    SYSTEMTIME now;
    st = &now;
    GetSystemTime(st);
  }

  TCHAR buffer[PATH_LENGTH];
  memory_transfer(buffer, path, sizeof(buffer));
  TCHAR *ext = PathFindExtension(buffer);
  TCHAR extension[PATH_LENGTH];
  _sntprintf_s(extension, _countof(extension), _TRUNCATE, _T("-%04u%02u%02uT%02u%02u%02u.%03u%s"), st->wYear, st->wMonth, st->wDay, st->wHour, st->wMinute, st->wSecond, st->wMilliseconds, ext);
  *ext = _T('\0');
  _sntprintf_s(rotated, rotated_len, _TRUNCATE, _T("%s%s"), buffer, extension);
}

void rotate_file(TCHAR *service_name, TCHAR *path, unsigned long seconds, unsigned long low, unsigned long high) {
  unsigned long error;

  /* Now. */
  SYSTEMTIME st;
  GetSystemTime(&st);

  BY_HANDLE_FILE_INFORMATION info;

  /* Try to open the file to check if it exists and to get attributes. */
  HANDLE file = CreateFile(path, 0, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
  if (file) {
    /* Get file attributes. */
    if (! GetFileInformationByHandle(file, &info)) {
      /* Reuse current time for rotation timestamp. */
      seconds = low = high = 0;
      SystemTimeToFileTime(&st, &info.ftLastWriteTime);
    }

    CloseHandle(file);
  }
  else {
    error = GetLastError();
    if (error == ERROR_FILE_NOT_FOUND) return;
    log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_ROTATE_FILE_FAILED, service_name, path, _T("CreateFile()"), path, error_string(error), 0);
    /* Reuse current time for rotation timestamp. */
    seconds = low = high = 0;
    SystemTimeToFileTime(&st, &info.ftLastWriteTime);
  }

  /* Check file age. */
  if (seconds) {
    FILETIME ft;
    SystemTimeToFileTime(&st, &ft);

    ULARGE_INTEGER s;
    s.LowPart = ft.dwLowDateTime;
    s.HighPart = ft.dwHighDateTime;
    s.QuadPart -= seconds * 10000000LL;
    ft.dwLowDateTime = s.LowPart;
    ft.dwHighDateTime = s.HighPart;
    if (CompareFileTime(&info.ftLastWriteTime, &ft) > 0) return;
  }

  /* Check file size. */
  if (low || high) {
    if (info.nFileSizeHigh < high) return;
    if (info.nFileSizeHigh == high && info.nFileSizeLow < low) return;
  }

  /* Get ___new filename. */
  FileTimeToSystemTime(&info.ftLastWriteTime, &st);

  TCHAR rotated[PATH_LENGTH];
  rotated_filename(path, rotated, _countof(rotated), &st);

  /* Rotate. */
  if (MoveFile(path, rotated)) {
    log_event(EVENTLOG_INFORMATION_TYPE, NSSM_EVENT_ROTATED, service_name, path, rotated, 0);
    return;
  }
  error = GetLastError();

  if (error == ERROR_FILE_NOT_FOUND) return;
  log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_ROTATE_FILE_FAILED, service_name, path, _T("MoveFile()"), rotated, error_string(error), 0);
  return;
}

int get_output_handles(nssm_service_t *service, STARTUPINFO *si) {
  if (! si) return 1;

  /* Allocate a ___new console so we get a fresh stdin, stdout and stderr. */
  alloc_console(service);

  /* stdin */
  if (service->stdin_path[0]) {
    si->hStdInput = CreateFile(service->stdin_path, FILE_READ_DATA, service->stdin_sharing, 0, service->stdin_disposition, service->stdin_flags, 0);
    if (! si->hStdInput) {
      log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_CREATEFILE_FAILED, service->stdin_path, error_string(GetLastError()), 0);
      return 2;
    }
  }

  /* stdout */
  if (service->stdout_path[0]) {
    if (service->rotate_files) rotate_file(service->name, service->stdout_path, service->rotate_seconds, service->rotate_bytes_low, service->rotate_bytes_high);
    HANDLE stdout_handle = write_to_file(service->stdout_path, service->stdout_sharing, 0, service->stdout_disposition, service->stdout_flags);
    if (! stdout_handle) return 4;

    if (service->rotate_files && service->rotate_stdout_online) {
      service->stdout_pipe = si->hStdOutput = 0;
      service->stdout_thread = create_logging_thread(service->name, service->stdout_path, service->stdout_sharing, service->stdout_disposition, service->stdout_flags, &service->stdout_pipe, &si->hStdOutput, &stdout_handle, service->rotate_bytes_low, service->rotate_bytes_high, &service->stdout_tid, &service->rotate_stdout_online);
      if (! service->stdout_thread) {
        CloseHandle(service->stdout_pipe);
        CloseHandle(si->hStdOutput);
      }
    }
    else service->stdout_thread = 0;

    if (! service->stdout_thread) {
      if (! DuplicateHandle(GetCurrentProcess(), stdout_handle, GetCurrentProcess(), &si->hStdOutput, 0, true, DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS)) {
        log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_DUPLICATEHANDLE_FAILED, NSSM_REG_STDOUT, _T("stdout"), error_string(GetLastError()), 0);
        return 4;
      }
      service->rotate_stdout_online = NSSM_ROTATE_OFFLINE;
    }
  }

  /* stderr */
  if (service->stderr_path[0]) {
    /* Same as stdout? */
    if (str_equiv(service->stderr_path, service->stdout_path)) {
      service->stderr_sharing = service->stdout_sharing;
      service->stderr_disposition = service->stdout_disposition;
      service->stderr_flags = service->stdout_flags;
      service->rotate_stderr_online = NSSM_ROTATE_OFFLINE;

      /* Two handles to the same file will create a race. */
      if (! DuplicateHandle(GetCurrentProcess(), si->hStdOutput, GetCurrentProcess(), &si->hStdError, 0, true, DUPLICATE_SAME_ACCESS)) {
        log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_DUPLICATEHANDLE_FAILED, NSSM_REG_STDOUT, _T("stderr"), error_string(GetLastError()), 0);
        return 6;
      }
    }
    else {
      if (service->rotate_files) rotate_file(service->name, service->stderr_path, service->rotate_seconds, service->rotate_bytes_low, service->rotate_bytes_high);
      HANDLE stderr_handle = write_to_file(service->stderr_path, service->stderr_sharing, 0, service->stderr_disposition, service->stderr_flags);
      if (! stderr_handle) return 7;

      if (service->rotate_files && service->rotate_stderr_online) {
        service->stderr_pipe = si->hStdError = 0;
        service->stderr_thread = create_logging_thread(service->name, service->stderr_path, service->stderr_sharing, service->stderr_disposition, service->stderr_flags, &service->stderr_pipe, &si->hStdError, &stderr_handle, service->rotate_bytes_low, service->rotate_bytes_high, &service->stderr_tid, &service->rotate_stderr_online);
        if (! service->stderr_thread) {
          CloseHandle(service->stderr_pipe);
          CloseHandle(si->hStdError);
        }
      }
      else service->stderr_thread = 0;

      if (! service->stderr_thread) {
        if (! DuplicateHandle(GetCurrentProcess(), stderr_handle, GetCurrentProcess(), &si->hStdError, 0, true, DUPLICATE_CLOSE_SOURCE | DUPLICATE_SAME_ACCESS)) {
          log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_DUPLICATEHANDLE_FAILED, NSSM_REG_STDERR, _T("stderr"), error_string(GetLastError()), 0);
          return 7;
        }
        service->rotate_stderr_online = NSSM_ROTATE_OFFLINE;
      }
    }
  }

  /*
    We need to set the startup_info flags to make the ___new handles
    inheritable by the ___new process.
  */
  si->dwFlags |= STARTF_USESTDHANDLES;

  if (service->no_console) return 0;

  /* Redirect other handles. */
  if (! si->hStdInput) {
    if (! DuplicateHandle(GetCurrentProcess(), GetStdHandle(STD_INPUT_HANDLE), GetCurrentProcess(), &si->hStdInput, 0, true, DUPLICATE_SAME_ACCESS)) {
      log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_DUPLICATEHANDLE_FAILED, _T("STD_INPUT_HANDLE"), _T("stdin"), error_string(GetLastError()), 0);
      return 8;
    }
  }
  if (! si->hStdOutput) {
    if (! DuplicateHandle(GetCurrentProcess(), GetStdHandle(STD_OUTPUT_HANDLE), GetCurrentProcess(), &si->hStdOutput, 0, true, DUPLICATE_SAME_ACCESS)) {
      log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_DUPLICATEHANDLE_FAILED, _T("STD_OUTPUT_HANDLE"), _T("stdout"), error_string(GetLastError()), 0);
      return 9;
    }
  }
  if (! si->hStdError)  {
    if (! DuplicateHandle(GetCurrentProcess(), GetStdHandle(STD_ERROR_HANDLE), GetCurrentProcess(), &si->hStdError, 0, true, DUPLICATE_SAME_ACCESS)) {
      log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_DUPLICATEHANDLE_FAILED, _T("STD_ERROR_HANDLE"), _T("stderr"), error_string(GetLastError()), 0);
      return 10;
    }
  }

  return 0;
}

void close_output_handles(STARTUPINFO *si) {
  if (si->hStdInput) CloseHandle(si->hStdInput);
  if (si->hStdOutput) CloseHandle(si->hStdOutput);
  if (si->hStdError) CloseHandle(si->hStdError);
}

/*
  Try multiple times to read from a file.
  Returns:  0 on success.
            1 on non-fatal error.
           -1 on fatal error.
*/
static int try_read(logger_t *logger, void *address, unsigned long bufsize, unsigned long *in, int *complained) {
  int ret = 1;
  unsigned long error;
  for (int tries = 0; tries < 5; tries++) {
    if (ReadFile(logger->read_handle, address, bufsize, in, 0)) return 0;

    error = GetLastError();
    switch (error) {
      /* Other end closed the pipe. */
      case ERROR_BROKEN_PIPE:
        ret = -1;
        goto complain_read;

      /* Couldn't lock the buffer. */
      case ERROR_NOT_ENOUGH_QUOTA:
        Sleep(2000 + tries * 3000);
        ret = 1;
        continue;

      /* Write was cancelled by the other end. */
      case ERROR_OPERATION_ABORTED:
        ret = 1;
        goto complain_read;

      default:
        ret = -1;
    }
  }

complain_read:
  /* Ignore the error if we've been requested to exit anyway. */
  if (*logger->rotate_online != NSSM_ROTATE_ONLINE) return ret;
  if (! (*complained & COMPLAINED_READ)) log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_READFILE_FAILED, logger->service_name, logger->path, error_string(error), 0);
  *complained |= COMPLAINED_READ;
  return ret;
}

/*
  Try multiple times to write to a file.
  Returns:  0 on success.
            1 on non-fatal error.
           -1 on fatal error.
*/
static int try_write(logger_t *logger, void *address, unsigned long bufsize, unsigned long *out, int *complained) {
  int ret = 1;
  unsigned long error;
  for (int tries = 0; tries < 5; tries++) {
    if (WriteFile(logger->write_handle, address, bufsize, out, 0)) return 0;

    error = GetLastError();
    if (error == ERROR_IO_PENDING) {
      /* Operation was successful pending flush to disk. */
      return 0;
    }

    switch (error) {
      /* Other end closed the pipe. */
      case ERROR_BROKEN_PIPE:
        ret = -1;
        goto complain_write;

      /* Couldn't lock the buffer. */
      case ERROR_NOT_ENOUGH_QUOTA:
      /* Out of disk space. */
      case ERROR_DISK_FULL:
        Sleep(2000 + tries * 3000);
        ret = 1;
        continue;

      default:
        /* We'hi lose this line but try to read and write subsequent ones. */
        ret = 1;
    }
  }

complain_write:
  if (! (*complained & COMPLAINED_WRITE)) log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_WRITEFILE_FAILED, logger->service_name, logger->path, error_string(error), 0);
  *complained |= COMPLAINED_WRITE;
  return ret;
}

/* Wrapper to be called in a ___new thread for logging. */
unsigned long WINAPI log_and_rotate(void *arg) {
  logger_t *logger = (logger_t *) arg;
  if (! logger) return 1;

  __int64 size;
  BY_HANDLE_FILE_INFORMATION info;

  /* Find initial file size. */
  if (! GetFileInformationByHandle(logger->write_handle, &info)) logger->size = 0LL;
  else {
    ULARGE_INTEGER l;
    l.HighPart = info.nFileSizeHigh;
    l.LowPart = info.nFileSizeLow;
    size = l.QuadPart;
  }

  char buffer[1024];
  void *address;
  unsigned long in, out;
  unsigned long charsize = 0;
  unsigned long error;
  int ret;
  int complained = 0;

  while (true) {
    /* Read data from the pipe. */
    address = &buffer;
    ret = try_read(logger, address, sizeof(buffer), &in, &complained);
    if (ret < 0) {
      CloseHandle(logger->read_handle);
      CloseHandle(logger->write_handle);
      HeapFree(GetProcessHeap(), 0, logger);
      return 2;
    }
    else if (ret) continue;

    if (*logger->rotate_online == NSSM_ROTATE_ONLINE_ASAP || (logger->int_size && size + (__int64) in >= logger->int_size)) {
      /* Look for newline. */
      unsigned long i;
      for (i = 0; i < in; i++) {
        if (buffer[i] == '\n') {
          if (! charsize) charsize = guess_charsize(address, in);
          i += charsize;

          /* Write up to the newline. */
          ret = try_write(logger, address, i, &out, &complained);
          if (ret < 0) {
            HeapFree(GetProcessHeap(), 0, logger);
            CloseHandle(logger->read_handle);
            CloseHandle(logger->write_handle);
            return 3;
          }
          size += (__int64) out;

          /* Rotate. */
          *logger->rotate_online = NSSM_ROTATE_ONLINE;
          TCHAR rotated[PATH_LENGTH];
          rotated_filename(logger->path, rotated, _countof(rotated), 0);

          /*
            Ideally we'd try the rename first then close the handle but
            MoveFile() will fail if the handle is still open so we must
            risk losing everything.
          */
          CloseHandle(logger->write_handle);
          if (MoveFile(logger->path, rotated)) {
            log_event(EVENTLOG_INFORMATION_TYPE, NSSM_EVENT_ROTATED, logger->service_name, logger->path, rotated, 0);
            size = 0LL;
          }
          else {
            error = GetLastError();
            if (error != ERROR_FILE_NOT_FOUND) {
              if (! (complained & COMPLAINED_ROTATE)) log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_ROTATE_FILE_FAILED, logger->service_name, logger->path, _T("MoveFile()"), rotated, error_string(error), 0);
              complained |= COMPLAINED_ROTATE;
              /* We can at least try to re-open the existing file. */
              logger->disposition = OPEN_ALWAYS;
            }
          }

          /* Reopen. */
          logger->write_handle = write_to_file(logger->path, logger->sharing, 0, logger->disposition, logger->flags);
          if (! logger->write_handle) {
            error = GetLastError();
            log_event(EVENTLOG_ERROR_TYPE, NSSM_EVENT_CREATEFILE_FAILED, logger->path, error_string(error), 0);
            /* Oh dear.  Now we can't log anything further. */
            HeapFree(GetProcessHeap(), 0, logger);
            CloseHandle(logger->read_handle);
            CloseHandle(logger->write_handle);
            return 4;
          }

          /* Resume writing after the newline. */
          address = (void *) ((char *) address + i);
          in -= i;
        }
      }
    }

    if (! int_size) {
      /* Write a BOM to the ___new file. */
      if (! charsize) charsize = guess_charsize(address, in);
      if (charsize == sizeof(wchar_t)) write_bom(logger, &out);
      size += (__int64) out;
    }

    /* Write the data, if any. */
    if (! in) continue;

    ret = try_write(logger, address, in, &out, &complained);
    size += (__int64) out;
    if (ret < 0) {
      HeapFree(GetProcessHeap(), 0, logger);
      CloseHandle(logger->read_handle);
      CloseHandle(logger->write_handle);
      return 3;
    }
  }

  HeapFree(GetProcessHeap(), 0, logger);
  CloseHandle(logger->read_handle);
  CloseHandle(logger->write_handle);
  return 0;
}

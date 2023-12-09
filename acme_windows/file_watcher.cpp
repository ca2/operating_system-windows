//
//
//	   Main header for the file_watcher class. Declares all implementation
//	   classes to reduce compilation overhead.
//
//	   @author James Wynn
//	   @date 4/15/2009
//
//	   Copyright (c) 2009 James Wynn (james@jameswynn.com)
//
//	   Permission is hereby granted, free of charge, to any person obtaining a copy
//	   of this software and associated documentation files (the "Software"), to deal
//	   in the Software without restriction, including without limitation the rights
//	   to uxse, cxopy, mxodify, mxerge, pxublish, dxistribute, sxublicense, and/or sxell
//	   copies of the Software, and to permit persons to whom the Software is
//	   furnished to do so, topic to the following conditions:
//
//
#include "framework.h"
#include "file_watcher.h"
#include "acme/parallelization/event.h"
#include "acme/filesystem/watcher/action.h"
#include "acme/filesystem/watcher/listener.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   /// Starts monitoring a directory.
   file_watch::file_watch()
   {


   }


   file_watch::~file_watch()
   {

      m_bRefresh = false;

      m_bStop = true;

      CancelIo(m_hDirectory);

      file_watch_step();

      if (!HasOverlappedIoCompleted(&m_overlapped))
      {

         SleepEx(5, true);

      }

      if (m_overlapped.hEvent != INVALID_HANDLE_VALUE)
      {

         CloseHandle(m_overlapped.hEvent);

         m_overlapped.hEvent = INVALID_HANDLE_VALUE;

      }

      if (m_hDirectory != INVALID_HANDLE_VALUE)
      {

         CloseHandle(m_hDirectory);

         m_hDirectory = INVALID_HANDLE_VALUE;

      }

   }


   bool file_watch::open(const ::file::path & pathFolder, bool bRecursive)
   {

      if (!watch::open(pathFolder, bRecursive))
      {

         return false;

      }

      wstring wstrFolder(pathFolder);

      memset(&m_overlapped, 0, sizeof(m_overlapped));

      m_bRefresh = true;

      m_overlapped.hEvent = INVALID_HANDLE_VALUE;

      m_hDirectory = INVALID_HANDLE_VALUE;

      m_hDirectory = CreateFileW(wstrFolder, FILE_LIST_DIRECTORY,
                                 FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                                 OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);

      ::u32 dwLen = GetFinalPathNameByHandleW(m_hDirectory, nullptr, 0, 0);

      if (dwLen > 0)
      {

         wstring wstr;

         auto pwsz = wstr.get_buffer(dwLen + 1);

         if (GetFinalPathNameByHandleW(m_hDirectory, pwsz, dwLen + 1, 0) > 0)
         {

            CloseHandle(m_hDirectory);

            m_hDirectory = CreateFileW(pwsz, FILE_LIST_DIRECTORY,
                                       FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, nullptr,
                                       OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS | FILE_FLAG_OVERLAPPED, nullptr);

         }


      }

      if (m_hDirectory == INVALID_HANDLE_VALUE)
      {

         return false;

      }

      m_overlapped.hEvent = CreateEvent(nullptr, true, false, nullptr);

      m_overlapped.Pointer = this;

      m_dwNotify = FILE_NOTIFY_CHANGE_CREATION
                   | FILE_NOTIFY_CHANGE_SIZE
                   | FILE_NOTIFY_CHANGE_FILE_NAME
                   | FILE_NOTIFY_CHANGE_LAST_WRITE;

      m_bRecursive = bRecursive;

      m_bStop = false;

      m_bRefresh = true;

      return true;

   }


   void CALLBACK file_watch::callback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered,LPOVERLAPPED pOverlapped)
   {

      //TCHAR szFile[MAX_PATH];

      PFILE_NOTIFY_INFORMATION pNotify;

      file_watch * pwatch = (file_watch*)pOverlapped->Pointer;


      size_t offset = 0;

      if (dwNumberOfBytesTransfered == 0)
      {

         return;

      }

      if(dwErrorCode == ERROR_SUCCESS)
      {

         do
         {

            pNotify = (PFILE_NOTIFY_INFORMATION)&pwatch->m_buffer[offset];

            offset += pNotify->NextEntryOffset;

            wstring wstrFile(pNotify->FileName, pNotify->FileNameLength / sizeof(WCHAR));

            string strFile = wstrFile;

            ULONG ulAction = pNotify->Action;

            ::file::action action;

            action.m_pwatch = pwatch;

            action.m_watchid = pwatch->m_watchid;

            action.m_pathFolder = pwatch->m_pathFolder;

            action.m_pathFile = strFile;

            ::file::enum_action eaction = ::file::e_action_none;

            switch (ulAction)
            {
            case FILE_ACTION_RENAMED_NEW_NAME:
            case FILE_ACTION_ADDED:
               eaction = ::file::e_action_add;
               break;
            case FILE_ACTION_RENAMED_OLD_NAME:
            case FILE_ACTION_REMOVED:
               eaction = ::file::e_action_delete;
               break;
            case FILE_ACTION_MODIFIED:
               eaction = ::file::e_action_modify;
               break;
            };

            action.m_eaction = eaction;

            pwatch->handle_action(&action);

         }
         while(pNotify->NextEntryOffset != 0);

      }

      if(!pwatch->m_bStop)
      {

         pwatch->m_bRefresh = true;

      }

   }


   bool file_watch::file_watch_step()
   {

      return ReadDirectoryChangesW(
             m_hDirectory,
             m_buffer,
             sizeof(m_buffer),
             m_bRecursive ? true : false,
             m_dwNotify,
             nullptr,
             &m_overlapped,
             m_bStop ? NULL : &file_watch::callback) != 0;

   }


   file_watcher::file_watcher()
   {

   }


   file_watcher::~file_watcher()
   {

      m_watchmap.clear();

   }


   bool file_watcher::file_watcher_step()
   {

      MsgWaitForMultipleObjectsEx(0,nullptr,500,QS_ALLINPUT,MWMO_ALERTABLE);

      if (!::task_get_run())
      {

         return false;

      }

      if (!watcher::file_watcher_step())
      {

         return false;

      }

      return true;

   }


} // namespace acme_windows





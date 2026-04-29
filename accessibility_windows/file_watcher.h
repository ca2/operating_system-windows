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
#pragma once


#include "acme/filesystem/watcher/watch.h"
#include "acme/filesystem/watcher/watcher.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS file_watch :
      virtual public ::file::watch
   {
   public:


      //__creatable_from_base(os_watch, ::file::watch);


      OVERLAPPED           m_overlapped;
      HANDLE               m_hDirectory;
      unsigned char                 m_buffer[32 * 1024];
      LPARAM               m_lparam;
      DWORD                m_dwNotify;
      bool                 m_bRefresh;


      file_watch();
      ~file_watch() override;

      bool open(const ::file::path & pathFolder, bool bRecursive) override;

      static void CALLBACK callback(DWORD dwErrorCode, DWORD dwNumberOfBytesTransfered, LPOVERLAPPED pOverlapped);

      bool file_watch_step() override;


   };


   class CLASS_DECL_ACME_WINDOWS file_watcher :
      virtual public ::file::watcher
   {
   public:


      //__creatable_from_base(os_watcher, ::file::watcher);


      file_watcher();
      ~file_watcher() override;


      //virtual void     run() override;

      bool file_watcher_step() override;


   };


} // namespace acme_windows




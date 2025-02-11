#pragma once


#include "acme/prototype/prototype/particle.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS file_find :
      public ::particle
   {
      // ementation
   protected:


      WIN32_FIND_DATAW     m_dataFound;
      WIN32_FIND_DATAW     m_dataNext;
      WIN32_FIND_DATAW *   m_pFoundInfo;
      WIN32_FIND_DATAW *   m_pNextInfo;
      HANDLE               m_hContext;
      bool                 m_bGotLast;
      string               m_strRoot;
      char                 m_chDirSeparator;     // not '\\' for Internet classes


   public:


      file_find();
      ~file_find() override;


      //void assert_ok() const override;
      //void dump(dump_context & dumpcontext) const override;


      
      long long get_length() const;
      virtual ::file::path GetFileName() const;
      virtual ::file::path GetFilePath() const;
      virtual string GetFileTitle() const;
      virtual string GetFileURL() const;
      virtual string GetRoot() const;

      virtual bool GetLastWriteTime(FILETIME* pTimeStamp) const;
      virtual bool GetLastAccessTime(FILETIME* pTimeStamp) const;
      virtual bool GetCreationTime(FILETIME* pTimeStamp) const;
      virtual bool GetLastWriteTime(::earth::time& refTime) const;
      virtual bool GetLastAccessTime(::earth::time& refTime) const;
      virtual bool GetCreationTime(::earth::time& refTime) const;

      bool MatchesMask(unsigned int dwMask) const;

      virtual bool IsDots() const;
      // these aren't virtual because they all use MatchesMask(), which is
      bool IsReadOnly() const;
      bool IsDirectory() const;
      bool IsCompressed() const;
      bool IsSystem() const;
      bool IsHidden() const;
      bool IsTemporary() const;
      bool IsNormal() const;
      bool IsArchived() const;

      
      void close();
      virtual bool find_file(const ::string & pstrName = nullptr, unsigned int dwUnused = 0);
      virtual bool find_next_file();

      virtual void CloseContext();



   };

   inline bool file_find::IsReadOnly() const
   {

      return MatchesMask(FILE_ATTRIBUTE_READONLY);

   }

   inline bool file_find::IsDirectory() const
   {

      return MatchesMask(FILE_ATTRIBUTE_DIRECTORY);

   }

   inline bool file_find::IsCompressed() const
   {

      return MatchesMask(FILE_ATTRIBUTE_COMPRESSED);

   }

   inline bool file_find::IsSystem() const
   {

      return MatchesMask(FILE_ATTRIBUTE_SYSTEM);

   }

   inline bool file_find::IsHidden() const
   {

      return MatchesMask(FILE_ATTRIBUTE_HIDDEN);

   }

   inline bool file_find::IsTemporary() const
   {

      return MatchesMask(FILE_ATTRIBUTE_TEMPORARY);

   }

   inline bool file_find::IsNormal() const
   {

      return MatchesMask(FILE_ATTRIBUTE_NORMAL);

   }

   inline bool file_find::IsArchived() const
   {

      return MatchesMask(FILE_ATTRIBUTE_ARCHIVE);

   }

   inline bool file_find::MatchesMask(unsigned int dwMask) const
   {


      if (m_pFoundInfo != nullptr)
         return (m_pFoundInfo->dwFileAttributes & dwMask) != false;
      else
         return false;

   }

   inline long long file_find::get_length() const
   {

      if (m_pFoundInfo != nullptr)
         return m_pFoundInfo->nFileSizeLow + (((long long)m_pFoundInfo->nFileSizeHigh) << 32);
      else
         return 0;

   }


} // namespace acme_windows




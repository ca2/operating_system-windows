#pragma once


#ifndef WINDOWS_DESKTOP
#error "This file is designed to be used only as Windows Desktop Source"
#endif


class FileException;
struct FileStatus;


void CLASS_DECL_ACME_WINDOWS vfxGetRoot(const unichar * pszPath, string& wstrRoot);

void CLASS_DECL_ACME_WINDOWS vfxGetRoot(wstring & wstrRoot, const wstring & wstrPath);


namespace windows
{


   class CLASS_DECL_ACME_WINDOWS file :
      virtual public ::file::file
   {
   public:


      //__creatable_from_base(file, ::file::file);


     /* enum Attribute
      {
         normal =    0x00,
         readOnly =  0x01,
         hidden =    0x02,
         system =    0x04,
         volume =    0x08,
         directory = 0x10,
         archive =   0x20
      };


      enum BufferCommand
      {

         bufferRead,
         bufferWrite,
         bufferCommit,
         bufferCheck

      };*/

      HANDLE            m_handleFile;
      ::u32             m_dwAccessMode;
      int               m_iCharacterPutBack;


      file();
      file(HANDLE hFile);
      file(const ::string & pszFileName, const ::file::e_open & eopen);
      ~file() override;


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;



      operator HANDLE() const;

      virtual filesize get_position() const override;
      virtual bool get_status(::file::file_status & rStatus) const override;
      virtual ::file::path get_file_path() const override;
      virtual void set_file_path(const ::file::path & path) override;


      virtual void open(const ::file::path & pszFileName, const ::file::e_open & eopen) override;


      virtual filesize translate(filesize filesize, ::enum_seek nFrom) override;
      virtual void set_size(filesize dwNewLen) override;
      virtual filesize get_size() const override;

      virtual memsize read(void * pdata, memsize nCount) override;

      virtual void write(const void * pdata, memsize nCount) override;


      virtual int peek_character();
      virtual int get_character();
      virtual int put_character_back(int iCharacter);


      virtual void lock(filesize dwPos, filesize dwCount) override;
      virtual void unlock(filesize dwPos, filesize dwCount) override;

      virtual void flush() override;
      virtual void close() override;

      virtual bool is_opened() const override;

   };
  

} // namepsace windows




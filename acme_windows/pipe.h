#pragma once


#include "acme/operating_system/pipe.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS pipe :
      virtual public ::operating_system::pipe
   {
   public:


      //__creatable_from_base(pipe, ::operating_system::pipe);


      class overlapped
      {
      public:
         pipe * m_ppipe;
         OVERLAPPED m_overlapped;
         inline overlapped * from(OVERLAPPED * poverlapped)
         {
            return (overlapped *)((byte *)poverlapped - sizeof(pipe *));
         }
      };


      char *               m_pchBuf;
      string               m_strRead;

      overlapped           m_overlapped;

      SECURITY_ATTRIBUTES  m_sa;
      HANDLE               m_hRead;
      HANDLE               m_hWrite;


      pipe();
      virtual ~pipe();


      virtual bool create(bool bBlock = true, bool bInherit = false);


      virtual bool not_inherit_read();
      virtual bool not_inherit_write();

      virtual bool write(const ::string & psz);
      virtual string read();
      virtual string one_pass_read();


      virtual void readex();


      static void WINAPI read_complete(
         u32 dwErrorCode,
         u32 dwNumberOfBytesTransfered,
         LPOVERLAPPED pOverlapped

         );

   };


} // namespace acme_windows




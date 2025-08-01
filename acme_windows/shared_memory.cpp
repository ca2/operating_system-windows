#include "framework.h"
#include "shared_memory.h"
#include "acme/prototype/prototype/pointer.h"
#include "acme/exception/exception.h"


shared_memory::shared_memory(const memory_base & s)
{

   m_nAllocFlags = 0;
   m_hGlobalMemory = nullptr;
   m_bAllowGrow = true;
   m_beginStorage = nullptr;
   m_begin = nullptr;

   memory_base::operator             = (s);

}

shared_memory::shared_memory(memory_container * pcontainer, double dAllocationRateUp, unsigned int nAllocFlags)
{

   m_nAllocFlags = nAllocFlags;
   m_bAllowGrow = true;
   m_pcontainer = pcontainer;
   m_dAllocationRateUp = dAllocationRateUp;
   m_beginStorage = nullptr;
   m_begin = nullptr;

}


shared_memory::shared_memory(memory_container * pcontainer, const void * pMemory, memsize dwSize)
{

   m_nAllocFlags = 0;
   m_pcontainer = pcontainer;
   m_bAllowGrow = true;
   m_beginStorage = nullptr;
   m_begin = nullptr;

   set_size(dwSize);

   ASSERT(is_memory_segment_ok(pMemory, (uptr)dwSize));

   ::memory_copy(m_beginStorage, pMemory, (size_t)dwSize);

}


shared_memory::shared_memory(const void * pMemory, memsize dwSize)
{

   m_nAllocFlags = 0;
   m_pcontainer = nullptr;
   m_bAllowGrow = true;
   m_beginStorage = nullptr;
   m_begin = nullptr;

   set_size(dwSize);

   ASSERT(is_memory_segment_ok(pMemory, (uptr)dwSize));

   ::memory_copy(m_beginStorage, pMemory, (size_t)dwSize);

}


shared_memory::~shared_memory()
{

   if (m_beginStorage != nullptr)
   {

      impl_free(m_beginStorage);

   }

}


unsigned char * shared_memory::detach_shared_memory(HGLOBAL & hglobal)
{

   if (this->offset() > 0)
   {

      ::pointer<shared_memory>pusermessage = clone();

      impl_free(m_beginStorage);

      pusermessage->detach_shared_memory(hglobal);

   }
   else
   {

      hglobal = m_hGlobalMemory;

   }

   unsigned char * pbStorage = m_beginStorage;

   m_hGlobalMemory = nullptr;
   m_beginStorage = nullptr;
   m_begin = nullptr;
   m_sizeStorage = 0;
   m_end = 0;

   return pbStorage;

}


void shared_memory::SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow)
{

   __UNREFERENCED_PARAMETER(bAllowGrow);

   ASSERT(m_hGlobalMemory == nullptr);        // do once only

   ASSERT(m_beginStorage == nullptr);     // do once only

   if (hGlobalMemory == nullptr)
   {

      throw ::exception(error_bad_argument);

   }

   m_hGlobalMemory = hGlobalMemory;

   m_beginStorage = (unsigned char *)::GlobalLock(m_hGlobalMemory);

   m_begin = m_beginStorage;

   m_end = m_begin + (m_sizeStorage = ::GlobalSize(m_hGlobalMemory));

   // xxx m_bAllowGrow = bAllowGrow;

}


unsigned char * shared_memory::impl_alloc(memsize nBytes)
{

   ASSERT(m_hGlobalMemory == nullptr);        // do once only

   m_hGlobalMemory = ::GlobalAlloc(m_nAllocFlags, (SIZE_T)nBytes);

   if (m_hGlobalMemory == nullptr)
      return nullptr;

   return (unsigned char *) ::GlobalLock(m_hGlobalMemory);

}


unsigned char * shared_memory::impl_realloc(void *, memsize nBytes)
{

   if (!m_bAllowGrow)
      return nullptr;

   ASSERT(m_hGlobalMemory != nullptr);

   ::GlobalUnlock(m_hGlobalMemory);

   HGLOBAL hNew;

   hNew = ::GlobalReAlloc(m_hGlobalMemory, (SIZE_T)nBytes, m_nAllocFlags);

   if (hNew == nullptr)
      return nullptr;

   m_hGlobalMemory = hNew;

   return (unsigned char *) ::GlobalLock(m_hGlobalMemory);

}


void shared_memory::impl_free(unsigned char *)
{

   ASSERT(m_hGlobalMemory != nullptr);

   ::GlobalUnlock(m_hGlobalMemory);

   ::GlobalFree(m_hGlobalMemory);

}


//unsigned char * * shared_memory::detach()
//{

//   throw ::exception(not_supported_exception("not valid for Global Memory(\"HGLOBAL\")"));

//}


//void shared_memory::free_data()
//{
//   if(m_beginStorage != nullptr)
//   {
//      m_end    = 0;
//      try
//      {
//         ::GlobalUnlock(m_hGlobalMemory);
//         ::GlobalFree(m_hGlobalMemory);
//      }
//      catch(...)
//      {
//      }
//      m_beginStorage       = nullptr;
//      m_begin = nullptr;
//   }
//}

















/*void shared_memory::copy_from(const memory_base *pstorage)
{
   ASSERT(pstorage != nullptr);
   allocate(pstorage->get_size());
   ::memory_copy(get_data(), pstorage->get_data(), (size_t) this->get_size());

}

void shared_memory::set_data(void *pdata, memsize uiSize)
{
   allocate(uiSize);
   ::memory_copy(get_data(), pdata, (size_t) uiSize);
}
*/

/*void shared_memory::To(string & str, memsize iStart, memsize iEnd)
{
   iStart = maximum(iStart, 0);
   if(iEnd == -1)
      iEnd = this->get_size() - 1;
   char * pch = (char *) get_data();
   for(memsize i = iStart; i <= iEnd; i++)
   {
      if(((pch[i] & 0xf0) >> 4) < 10)
         str += (char)(((pch[i] & 0xf0) >> 4) + '0');
      else
         str += (char)(((pch[i] & 0xf0) >> 4) + 'A' - 10);
      if(((pch[i] & 0x0f)) < 10)
         str += (char)((pch[i] & 0x0f) + '0');
      else
         str += (char)((pch[i] & 0x0f) + 'A' - 10);
   }
}

void shared_memory::From(const ::scoped_string & scopedstr)
{
   char ch;
   int iLen = strlen(psz);
   allocate(iLen / 2);
   char * pch = (char *) get_data();
   while(*psz != '\0')
   {
      ch = 0;
      if(*psz > '9')
         ch |= ((*psz - 'A' + 10) & 0x0f) << 4;
      else
         ch |= ((*psz - '0') & 0x0f) << 4;
      if(*psz == '\0')
         break;
      psz++;
      if(*psz > '9')
         ch |= ((*psz - 'A' + 10) & 0x0f);
      else
         ch |= ((*psz - '0') & 0x0f);
      *pch = ch;
      psz++;
      pch++;
   }
}

void shared_memory::ToAsc(string & str)
{
   string strTo;
   To(strTo);
   char ch;
   int iLen = strTo.length() - 1;
   for(int i = 0; i < iLen; i+=2)
   {
      if(strTo[i] <= '9')
         ch = (strTo[i] - '0') << 4;
      else
         ch = (strTo[i] - 'A' + 10) << 4;
      if(strTo[i + 1] <= '9')
         ch |= (strTo[i + 1] - '0');
      else
         ch |= (strTo[i + 1] - 'A' + 10);
      str += ch;
   }
}

void shared_memory::FromAsc(const ::scoped_string & scopedstr)
{
   string str;
   while(*psz)
   {
      char ch = ((*psz & 0xf0) >> 4);
      if(ch < 10)
         ch += '0';
      else
         ch += 'A' - 10;
      str += ch;
      ch = ((*psz & 0xf));
      if(ch < 10)
         ch += '0';
      else
         ch += 'A' - 10;
      str += ch;
      psz++;
   }
   From(str);
}*/


/*void shared_memory::from_string(const unichar * pwsz)
{
   from_string(unicode_to_utf8(pwsz));
}

void shared_memory::from_string(const ::scoped_string & scopedstr)
{
   allocate(strlen(psz));
   ::memory_copy(get_data(), psz, this->get_size());
}

void shared_memory::to_string(string & str)
{
   char * psz = str.get_buffer(this->get_size() + 1);

   ::memory_copy(psz, get_data(), this->get_size());

   psz[this->get_size()] = '\0';

   str.ReleaseBuffer();
}
*/




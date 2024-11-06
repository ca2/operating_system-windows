#pragma once


#include "acme/prototype/prototype/memory_base.h"
#include "acme/_operating_system.h"


class CLASS_DECL_ACME_WINDOWS shared_memory :
   public memory_base
{
public:


   unsigned int                                   m_nAllocFlags;
   HGLOBAL                                m_hGlobalMemory;
   bool                                   m_bAllowGrow;


   shared_memory(const memory_base & memory);
   shared_memory(memory_container * pmsc = nullptr, double dAllocationRateUp = 4096, unsigned int nAllocFlags = 0);
   shared_memory(memory_container * pmsc, const void * pMemory, memsize dwSize);
   shared_memory(const void *, memsize iCount);
   ~shared_memory() override;


   virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = true);

   virtual unsigned char * impl_alloc(memsize nBytes) override;
   virtual unsigned char * impl_realloc(void * pdata, memsize nBytes) override;
   virtual void impl_free(unsigned char * pMem) override;



   unsigned char * detach_shared_memory(HGLOBAL & hglobal);
   //unsigned char * detach(HGLOBAL & hglobal);
//      virtual bool allocate_internal(memsize dwNewLength);



      //virtual ::matter * clone() override;

};




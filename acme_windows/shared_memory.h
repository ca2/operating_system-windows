#pragma once


#include "acme/prototype/prototype/memory_base.h"
#include "acme/_operating_system.h"


class CLASS_DECL_ACME_WINDOWS shared_memory :
   public memory_base
{
public:


   ::u32                                   m_nAllocFlags;
   HGLOBAL                                m_hGlobalMemory;
   bool                                   m_bAllowGrow;


   shared_memory(const memory_base & memory);
   shared_memory(memory_container * pmsc = nullptr, double dAllocationRateUp = 4096, ::u32 nAllocFlags = 0);
   shared_memory(memory_container * pmsc, const void * pMemory, memsize dwSize);
   shared_memory(const void *, memsize iCount);
   ~shared_memory() override;


   virtual void SetHandle(HGLOBAL hGlobalMemory, bool bAllowGrow = true);

   virtual ::u8 * impl_alloc(memsize nBytes) override;
   virtual ::u8 * impl_realloc(void * pdata, memsize nBytes) override;
   virtual void impl_free(::u8 * pMem) override;



   ::u8 * detach_shared_memory(HGLOBAL & hglobal);
   //::u8 * detach(HGLOBAL & hglobal);
//      virtual bool allocate_internal(memsize dwNewLength);



      //virtual ::matter * clone() override;

};




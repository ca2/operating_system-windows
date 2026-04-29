// From acme/platform/exclusive.h by camilo on 2022-10-28 15:25 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/exclusive.h"
#include "acme/prototype/prototype/pointer.h"


namespace acme_windows
{


   class CLASS_DECL_ACME_WINDOWS exclusive :
      virtual public ::acme::exclusive
   {
   public:


      unsigned int                         m_dwLastError;
      bool                          m_bResourceException;
      ::pointer < ::mutex >         m_pmutex;


      exclusive(::particle * pparticle, const ::scoped_string & scopedstrName, security_attributes * psecurityattributes);
      ~exclusive() override;


      bool exclusive_fails() const override;


   };


} // namespace acme_windows




// From acme/platform/exclusive.h by camilo on 2022-10-28 15:25 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "exclusive.h"
#include "acme_windows_common/mutex.h"
#include "acme_windows_common/node.h"
#include "acme/exception/exception.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/platform/node.h"
#include "acme/platform/system.h"
#include "acme/prototype/prototype/object.h"
#include "acme/_operating_system.h"


namespace acme_windows
{


   exclusive::exclusive(::particle * pparticle, const ::scoped_string & scopedstrId, security_attributes * psecurityattributes)
   {

      m_strId = scopedstrId;

      m_bResourceException = false;

      try
      {

         ::pointer <::acme_windows_common::node>pnode = pparticle->node();

         m_pmutex = pnode->create_named_mutex(pparticle, false,scopedstrId);

         //m_pmutex = //__allocate ::pointer < ::mutex > (pparticle, false, strId ADD_PARAM_SEC_ATTRS);

         //m_dwLastError = ::GetLastError();

      }
      catch (const ::exception &)
      {

         try
         {

            m_pmutex = __allocate ::acme_windows_common::mutex(pparticle, false, scopedstrId);

            m_dwLastError = ::GetLastError();

         }
         catch (const ::exception &)
         {

            m_bResourceException = true;

         }

      }

   }


   //#else
   //
   //
   //   exclusive::exclusive(::particle * pparticle, const ::scoped_string & scopedstrId ARG_SEC_ATTRS)
   //   {
   //
   //      initialize(pparticle);
   //
   //      m_strId = strId;
   //
   //      ::file::path path;
   //
   //      if(strId.case_insensitive_begins("Local\\"))
   //      {
   //
   //         path = pparticle->directory_system()->home() / ".config/acme";
   //
   //      }
   //      else
   //      {
   //
   //         path = "/var/tmp/acme";
   //
   //      }
   //
   //      path /= strId;
   //
   //      directory_system()->create(path.folder());
   //
   //      m_iFile = open(path, O_WRONLY | O_CREAT, 0777);
   //
   //      m_iLock = lockf(m_iFile, F_TLOCK, 0);
   //
   //   }
   //
   //
   //#endif
   //

   exclusive::~exclusive()
   {

   }


   bool exclusive::exclusive_fails() const
   {

      return m_bResourceException || m_pmutex->has_already_exists_flag();

      //#ifdef WINDOWS
      //
      //      return m_dwLastError == ERROR_ALREADY_EXISTS || m_bResourceException;
      //
      //#else
      //
      //      return m_iLock < 0;
      //
      //#endif

   }


} // namespace acme_windows




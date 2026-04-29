// From multimedia_mmsystem by camilo on 2023-04-08 05:22 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "mmresult.h"


CLASS_DECL_ACME_WINDOWS ::e_status mmresult_status(MMRESULT mmr)
{

   switch (mmr)
   {
   case MMSYSERR_NOERROR:

      return ::success;

   case MMSYSERR_BADDEVICEID:

      return error_bad_device_id;

   case MMSYSERR_ALLOCATED:

      return error_already_allocated;

   default:

      return error_failed;

   };

}




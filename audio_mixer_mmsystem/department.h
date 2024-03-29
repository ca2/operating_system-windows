#pragma once


#include "acme/platform/department.h"
#include "aura/user/user/interaction.h"

//
//namespace multimedia
//{


namespace audio_mixer_mmsystem
{


   class CLASS_DECL_AUDIO_MIXER_MMSYSTEM department :
      virtual public ::acme::department,
      virtual public ::user::interaction
   {
   public:



      enum EIds
      {

         IdsMuteAll,
         IdsMute

      };


      department();
      virtual ~department();


      virtual bool initialize1();



      bool initialize();


      virtual void destroy() override;





   };


} // namespace mixguserbase

//
//} // namespace multimedia
//
//
//
//
//
//

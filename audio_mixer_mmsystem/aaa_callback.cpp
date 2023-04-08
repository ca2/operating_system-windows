#include "framework.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      callback::callback()
      {

      }


      callback::~callback()
      {

      }


      ::audio_mixer_user::level_control * callback::allocate_level_control()
      {

         return nullptr;

      }


      ::audio_mixer_user::toggle_control * callback::allocate_toggle_control()
      {

         return nullptr;

      }


      ::audio_mixer_user::label * callback::allocate_label()
      {

         return nullptr;

      }


   } // namespace audio_mixer_mmsystem


} // namespace multimedia


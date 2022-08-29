#pragma once


#include "source.h"
#include "app-core/multimedia/audio_mixer/destination.h"


namespace multimedia
{


   namespace audio_mixer_mmsystem
   {


      class CLASS_DECL_AUDIO_MIXER_MMSYSTEM destination :
         virtual public ::multimedia::audio_mixer_mmsystem::source,
         virtual public ::multimedia::audio_mixer::destination
      {
      public:



         destination();
         virtual ~destination();


         u32 get_component_type();
         void update_all_controls();
         void     initialize_all_controls();
         void     initialize_source_info();

         ::multimedia::audio_mixer::source_array & get_source_info();

         ::multimedia::audio_mixer::device * get_device();
         void set_device(::multimedia::audio_mixer::device * pdevice);


         virtual u32 get_mixer_line_id();

      };


   } // namespace audio_mixer_mmsystem



} // namespace multimedia





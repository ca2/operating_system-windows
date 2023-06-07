#include "framework.h"
#include "control.h"
#include "line_info.h"
#include "source.h"
#include "audio_mixer.h"
#include "device.h"
#include "destination.h"
//#include "audio-system/audio_mixer/user/control.h"

//namespace multimedia
//{
//
//
//   namespace audio_mixer_mmsystem
//   {
//
//
//      factory_exchange::factory_exchange(::particle * pparticle) :
//         ::object(pobject),
//         ::multimedia::mmsystem::factory_exchange(pobject)
//      {
//
//         add_factory_item <control, ::audio_mixer::control>();
//         //add_factory_item <control_data                >  (__type(::audio_mixer::control_data));
//         add_factory_item <destination,::audio_mixer::destination>();
//         add_factory_item <device,::audio_mixer::device>();
//         add_factory_item <line_info,::audio_mixer::line_info>();
//         add_factory_item < audio_mixer, ::audio_mixer::audio_mixer >();
//         //add_factory_item < department, ::audio_mixer::font >();
//         add_factory_item <source,::audio_mixer::source>();
//         add_factory_item <thread,::audio_mixer::thread>();
//         /*add_factory_item <user::label                 >  (__type(::audio_mixer_user::label));
//         add_factory_item <user::interaction               >  (__type(::audio_mixer::user_control));
//         add_factory_item <user::level_control         >  (__type(::audio_mixer_user::level_control));
//         add_factory_item <user::toggle_control        >  (__type(::audio_mixer_user::toggle_control));*/
//
//      }
//
//
//      factory_exchange::~factory_exchange()
//      {
//
//      }
//
//
//   } // namespace audio_mmsystem
//
//
//} // namespace multimedia

__FACTORY_EXPORT void audio_mixer_mmsystem_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item <::audio_mixer_mmsystem::control, ::audio_mixer::control>();
            //add_factory_item <control_data                >  (__type(::audio_mixer::control_data));
   pfactory->add_factory_item <::audio_mixer_mmsystem::destination,::audio_mixer::destination>();
   pfactory->add_factory_item <::audio_mixer_mmsystem::device,::audio_mixer::device>();
   pfactory->add_factory_item <::audio_mixer_mmsystem::line_info,::audio_mixer::line_info>();
   pfactory->add_factory_item <::audio_mixer_mmsystem::audio_mixer, ::aqua::audio_mixer >();
            //add_factory_item < department, ::audio_mixer::font >();
   pfactory->add_factory_item <::audio_mixer_mmsystem::source,::audio_mixer::source>();
   //pfactory->add_factory_item <::audio_mixer_mmsystem::thread,::audio_mixer::thread>();
            /*add_factory_item <user::label                 >  (__type(::audio_mixer_user::label));
            add_factory_item <user::interaction               >  (__type(::audio_mixer::user_control));
            add_factory_item <user::level_control         >  (__type(::audio_mixer_user::level_control));
            add_factory_item <user::toggle_control        >  (__type(::audio_mixer_user::toggle_control));*/

}




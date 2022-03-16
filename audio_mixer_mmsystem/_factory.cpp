#include "framework.h"


//namespace multimedia
//{
//
//
//   namespace audio_mixer_mmsystem
//   {
//
//
//      factory_exchange::factory_exchange(::object * pobject) :
//         ::object(pobject),
//         ::multimedia::mmsystem::factory_exchange(pobject)
//      {
//
//         add_factory_item <control, ::multimedia::audio_mixer::control>();
//         //add_factory_item <control_data                >  (__type(::multimedia::audio_mixer::control_data));
//         add_factory_item <destination,::multimedia::audio_mixer::destination>();
//         add_factory_item <device,::multimedia::audio_mixer::device>();
//         add_factory_item <line_info,::multimedia::audio_mixer::line_info>();
//         add_factory_item < audio_mixer, ::multimedia::audio_mixer::audio_mixer >();
//         //add_factory_item < department, ::multimedia::audio_mixer::font >();
//         add_factory_item <source,::multimedia::audio_mixer::source>();
//         add_factory_item <thread,::multimedia::audio_mixer::thread>();
//         /*add_factory_item <user::label                 >  (__type(::multimedia::audio_mixer::user::label));
//         add_factory_item <user::interaction               >  (__type(::multimedia::audio_mixer::user::control));
//         add_factory_item <user::level_control         >  (__type(::multimedia::audio_mixer::user::level_control));
//         add_factory_item <user::toggle_control        >  (__type(::multimedia::audio_mixer::user::toggle_control));*/
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

   pfactory->add_factory_item <::multimedia::audio_mixer_mmsystem::control, ::multimedia::audio_mixer::control>();
            //add_factory_item <control_data                >  (__type(::multimedia::audio_mixer::control_data));
   pfactory->add_factory_item <::multimedia::audio_mixer_mmsystem::destination,::multimedia::audio_mixer::destination>();
   pfactory->add_factory_item <::multimedia::audio_mixer_mmsystem::device,::multimedia::audio_mixer::device>();
   pfactory->add_factory_item <::multimedia::audio_mixer_mmsystem::line_info,::multimedia::audio_mixer::line_info>();
   pfactory->add_factory_item <::multimedia::audio_mixer_mmsystem::audio_mixer, ::multimedia::audio_mixer::audio_mixer >();
            //add_factory_item < department, ::multimedia::audio_mixer::font >();
   pfactory->add_factory_item <::multimedia::audio_mixer_mmsystem::source,::multimedia::audio_mixer::source>();
   //pfactory->add_factory_item <::multimedia::audio_mixer_mmsystem::thread,::multimedia::audio_mixer::thread>();
            /*add_factory_item <user::label                 >  (__type(::multimedia::audio_mixer::user::label));
            add_factory_item <user::interaction               >  (__type(::multimedia::audio_mixer::user::control));
            add_factory_item <user::level_control         >  (__type(::multimedia::audio_mixer::user::level_control));
            add_factory_item <user::toggle_control        >  (__type(::multimedia::audio_mixer::user::toggle_control));*/

}




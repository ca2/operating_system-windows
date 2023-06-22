#include "framework.h"
#include "in.h"
#include "out.h"


IMPLEMENT_FACTORY(audio_mmsystem)
{

   pfactory->add_factory_item < ::audio_mmsystem::in, ::wave::in >();

   pfactory->add_factory_item < ::audio_mmsystem::out, ::wave::out >();

}










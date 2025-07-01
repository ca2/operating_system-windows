#include "framework.h"
//#include "_opengl.h"
//#include "image.h"
//#include "graphics.h"
//#include "bitmap.h"
//#include "pen.h"
//#include "brush.h"
//#include "region.h"
//#include "font.h"
//#include "path.h"
//#include "draw2d.h"
#include "face.h"
//#ifdef WINDOWS_DESKTOP
//#include "face_gdiplus.h"
//#else
//#include "face_freetype.h"
//#endif

__FACTORY_EXPORT void typeface_gdiplus_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::typeface_gdiplus::face, ::typeface::face >();

}




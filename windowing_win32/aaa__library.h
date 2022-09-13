#pragma once


#include "aura_windows/_library.h"
#include "aura/user/user/_component.h"
#include "aura/operating_system/windows/message_window.h"


namespace windowing_win32
{


   CLASS_DECL_WINDOWING_WIN32 void wingdi_enum_fonts(::write_text::font_enumeration_item_array& itema, bool bRaster, bool bTrueType, bool bOther);
   CLASS_DECL_WINDOWING_WIN32::enum_character_set wingdi_get_cs(int iCharSet);

   


   class window;




} // namespace windowing_win32




//#include "window_util.h"
//#include "win32.h"



//#include "buffer.h"
//#include "display.h"
//#include "cursor.h"
//#include "icon.h"
//#include "imm_client.h"
//#include "imm_context.h"
//#include "monitor.h"
//#include "keyboard.h"
//
//
//#include "notification_area.h"
//#include "notify_icon.h"
//
//
//#include "copydesk.h"
//
//
//#include "shell.h"
//
//
//#include "system_interaction.h"
//
//
//#include "window.h"
//
//
//#include "windowing.h"
//
//
//#include "top_level_enum.h"
//
//
////#include "node.h"
//
//#include "desktop_environment.h"
//
//#include "_impl.h"




//DECLARE_FACTORY(CLASS_DECL_WINDOWING_WIN32, windowing_win32);


//BEGIN_FACTORY(windowing_win32)
//FACTORY_ITEM(node)
//END_FACTORY()

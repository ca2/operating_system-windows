#include "platform/os/metrowin.h"



[Platform::MTAThread]
::i32 main(Platform::Array<Platform::String^>^)
{

   auto source = ::metrowin::new_directx_application_source("m_app.exe : app=app-core/hellomultiverse");

   ::winrt::Windows::ApplicationModel::Core::CoreApplication::Run(source);
   
   return 0;

}



/*[Platform::MTAThread]
::i32 main(Platform::Array<Platform::String^>^)
{
   
   // No Depends
   
   return 0;

}
*/

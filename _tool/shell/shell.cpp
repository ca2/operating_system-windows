// LAUNCHER SETTINGS
// Copy this file for another launcher and change these two values.
// These replace the folder= and executable= arguments formerly in shell.lnk.
namespace launcher_settings
{
   const wchar_t folder[] = L"operating_system/operating_system-windows/tool/bin";
   const wchar_t executable[] = L"launch_shell.exe";
}


// SHARED LAUNCHER IMPLEMENTATION
#include "../architecure_launcher/launcher.h"

extern "C" void WINAPI launcher_main()
{
   ExitProcess(architecture_launcher::run(
      launcher_settings::folder, launcher_settings::executable));
}

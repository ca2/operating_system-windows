#include "launcher.h"

extern "C" void WINAPI launcher_main()
{
   ExitProcess(architecture_launcher::run());
}

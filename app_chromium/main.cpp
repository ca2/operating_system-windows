#include "aura/.h"

extern int APIENTRY app_chromium_deferred_run(HINSTANCE hInstance,
      HINSTANCE hPrevInstance,
      LPTSTR lpCmdLine,
      int nCmdShow);

//int app_chromium_runner(HINSTANCE hInstance);

//#define MAIN_RUNNER0 &::app_chromium_runner
#define MAIN_DEFERRED_RUN &::app_chromium_deferred_run

#include "aura/inline/app.inl"

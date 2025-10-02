#include "framework.h"
#include "acme/exception/error_number.h"
#include "acme/_library.h"



#pragma comment (lib, "gdiplus.lib")

Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput = nullptr;
Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput = nullptr;
DWORD_PTR                        g_gdiplusToken = NULL;
DWORD_PTR                        g_gdiplusHookToken = NULL;


CLASS_DECL_DRAW2D_GDIPLUS void initialize_gdiplus()
{

   if (g_pgdiplusStartupInput != nullptr)
   {

      return;

   }

   g_pgdiplusStartupInput = øraw_new Gdiplus::GdiplusStartupInput ();

   g_pgdiplusStartupOutput = øraw_new Gdiplus::GdiplusStartupOutput ();

   g_gdiplusToken = NULL;

   g_gdiplusHookToken = NULL;

   g_pgdiplusStartupInput->SuppressBackgroundThread = true;

   Gdiplus::Status statusStartup = GdiplusStartup(&g_gdiplusToken, g_pgdiplusStartupInput, g_pgdiplusStartupOutput);

   if (statusStartup != Gdiplus::Ok)
   {

      output_debug_string("Gdiplus Failed to Startup. ca cannot continue.");

      return;

   }

   statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   if (statusStartup != Gdiplus::Ok)
   {

      output_debug_string("Gdiplus Failed to Hook. ca cannot continue.");

      throw ::exception(error_failed);

   }

}


CLASS_DECL_DRAW2D_GDIPLUS void terminate_gdiplus()
{

   if (g_pgdiplusStartupOutput != nullptr)
   {

      g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);

      ::Gdiplus::GdiplusShutdown(g_gdiplusToken);

      ::acme::del(g_pgdiplusStartupInput);
      ::acme::del(g_pgdiplusStartupOutput);

   }

}




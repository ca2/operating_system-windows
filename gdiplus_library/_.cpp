#include "framework.h"
#include "acme/exception/error_number.h"
#include "acme/_library.h"
#include <mutex>



#pragma comment (lib, "gdiplus.lib")

Gdiplus::GdiplusStartupInput *   g_pgdiplusStartupInput = nullptr;
Gdiplus::GdiplusStartupOutput *  g_pgdiplusStartupOutput = nullptr;
DWORD_PTR                        g_gdiplusToken = NULL;
DWORD_PTR                        g_gdiplusHookToken = NULL;
::i32                            g_iGdiplusReferenceCount = 0;
std::mutex                       g_mutexGdiplus;


CLASS_DECL_GDIPLUS_LIBRARY void initialize_gdiplus()
{

   std::scoped_lock lock(g_mutexGdiplus);

   if (g_iGdiplusReferenceCount > 0)
   {

      g_iGdiplusReferenceCount++;

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

      ::acme::del(g_pgdiplusStartupInput);
      ::acme::del(g_pgdiplusStartupOutput);

      throw ::exception(error_failed, "GdiplusStartup failed");

   }

   statusStartup = g_pgdiplusStartupOutput->NotificationHook(&g_gdiplusHookToken);

   if (statusStartup != Gdiplus::Ok)
   {

      output_debug_string("Gdiplus Failed to Hook. ca cannot continue.");

      ::Gdiplus::GdiplusShutdown(g_gdiplusToken);

      ::acme::del(g_pgdiplusStartupInput);
      ::acme::del(g_pgdiplusStartupOutput);

      throw ::exception(error_failed, "GDI+ notification hook failed");

   }

   g_iGdiplusReferenceCount = 1;

}


CLASS_DECL_GDIPLUS_LIBRARY void terminate_gdiplus()
{

   std::scoped_lock lock(g_mutexGdiplus);

   if (g_iGdiplusReferenceCount <= 0)
   {

      return;

   }

   g_iGdiplusReferenceCount--;

   if (g_iGdiplusReferenceCount == 0 && g_pgdiplusStartupOutput != nullptr)
   {

      g_pgdiplusStartupOutput->NotificationUnhook(g_gdiplusHookToken);

      ::Gdiplus::GdiplusShutdown(g_gdiplusToken);

      ::acme::del(g_pgdiplusStartupInput);
      ::acme::del(g_pgdiplusStartupOutput);

      g_gdiplusToken = NULL;
      g_gdiplusHookToken = NULL;

   }

}




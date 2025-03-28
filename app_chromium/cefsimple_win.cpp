// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#include <windows.h>

#include "include/cef_sandbox_win.h"
#include "simple_app.h"

// When generating projects with CMake the CEF_USE_SANDBOX value will be defined
// automatically if using the required compiler version. Pass -DUSE_SANDBOX=OFF
// to the CMake command-line to disable use of the sandbox.
// Uncomment this line to manually enable sandbox support.
// #define CEF_USE_SANDBOX 1


// Entry int_point function for all processes.
//int APIENTRY cef_main(HINSTANCE hInstance,
//                      HINSTANCE hPrevInstance,
//                      LPTSTR lpCmdLine,
//                      int nCmdShow)
//{
//   __UNREFERENCED_PARAMETER(hPrevInstance);
//   __UNREFERENCED_PARAMETER(lpCmdLine);

int APIENTRY app_chromium_deferred_run(HINSTANCE hInstance,
                                       HINSTANCE hPrevInstance,
                                       LPTSTR lpCmdLine,
                                       int nCmdShow)
{

   // Enable High-DPI support on Windows 7 or newer.
   CefEnableHighDPISupport();

   void* sandbox_info = nullptr;

#if defined(CEF_USE_SANDBOX)
   // Manage the life span of the sandbox information object. This is necessary
   // for sandbox support on Windows. See cef_sandbox_win.h for complete details.
   CefScopedSandboxInfo scoped_sandbox;
   sandbox_info = scoped_sandbox.sandbox_info();
#endif

   // Provide CEF with command-line arguments.
   CefMainArgs main_args(hInstance);

   // CEF applications have multiple sub-processes (render, plugin, GPU, etc)
   // that share the same executable. This function checks the command-line and,
   // if this is a sub-process, executes the appropriate logic.
   return CefExecuteProcess(main_args, nullptr, sandbox_info);

}



//int cef_main(HINSTANCE hInstance)
//{
//   // Enable High-DPI support on Windows 7 or newer.
//   CefEnableHighDPISupport();
//
//   void* sandbox_info = nullptr;
//
//#if defined(CEF_USE_SANDBOX)
//   // Manage the life span of the sandbox information object. This is necessary
//   // for sandbox support on Windows. See cef_sandbox_win.h for complete details.
//   CefScopedSandboxInfo scoped_sandbox;
//   sandbox_info = scoped_sandbox.sandbox_info();
//#endif
//
//   // Provide CEF with command-line arguments.
//   CefMainArgs main_args(hInstance);
//
//   //// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
//   //// that share the same executable. This function checks the command-line and,
//   //// if this is a sub-process, executes the appropriate logic.
//   //int exit_code = CefExecuteProcess(main_args, nullptr, sandbox_info);
//   //if (exit_code >= 0)
//   //{
//   //   // The sub-process has completed so return here.
//   //   return exit_code;
//   //}
//
//   // Specify CEF global settings here.
//   CefSettings settings;
//
//#if !defined(CEF_USE_SANDBOX)
//   settings.no_sandbox = true;
//#endif
//
//   // SimpleApp implements application-level callbacks for the browser process.
//   // It will create the first browser instance in OnContextInitialized() after
//   // CEF has initialized.
//   CefRefPtr<SimpleApp> app(___new SimpleApp);
//
//   // Initialize CEF.
//   CefInitialize(main_args, settings, app.get(), sandbox_info);
//
//   // Run the CEF message loop. This will block until CefQuitMessageLoop() is
//   // called.
//   CefRunMessageLoop();
//
//
//   return 0;
//}

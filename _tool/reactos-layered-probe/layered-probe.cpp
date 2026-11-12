// Standalone Windows XP-compatible test: no ca2, GDI+, or external runtime DLLs.
#define WINVER 0x0501
#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static FILE *report;
static HWND backgroundWindow, layeredWindow;
static HDC sourceDC;
static HBITMAP sourceBitmap;
static HGDIOBJ previousBitmap;
static unsigned long frame, failures, frameLimit;
static bool checkerboardMode;
static DWORD *sourcePixels, *textPixels;
static HDC textDC;
static HBITMAP textBitmap;
static HGDIOBJ previousTextBitmap;
static COLORREF firstColor = CLR_INVALID;
static const int width = 360, height = 180;
static POINT position = {100, 100};

static LRESULT CALLBACK BackgroundProc(HWND window, UINT message, WPARAM wp, LPARAM lp)
{
   if (message == WM_CLOSE)
   {
      PostQuitMessage(failures ? 1 : 0);
      return 0;
   }
   if (message == WM_PAINT)
   {
      PAINTSTRUCT paint;
      HDC dc = BeginPaint(window, &paint);
      HBRUSH brush = CreateSolidBrush(RGB(32, 64, 96));
      FillRect(dc, &paint.rcPaint, brush);
      HBRUSH lightBrush = CreateSolidBrush(RGB(200, 210, 220));
      RECT client;
      GetClientRect(window, &client);
      for (int y = 0; y < client.bottom; y += 24)
         for (int x = 0; x < client.right; x += 24)
            if (((x / 24) + (y / 24)) % 2)
            {
               RECT square = {x, y, x + 24, y + 24};
               FillRect(dc, &square, lightBrush);
            }
      // A fixed-color patch remains under the lower-right sample point.
      RECT samplePatch = {width - 12, height - 12, width + 12, height + 12};
      FillRect(dc, &samplePatch, brush);
      DeleteObject(lightBrush);
      DeleteObject(brush);
      EndPaint(window, &paint);
      return 0;
   }
   return DefWindowProcA(window, message, wp, lp);
}

static LRESULT CALLBACK LayeredProc(HWND window, UINT message, WPARAM wp, LPARAM lp)
{
   if (message == WM_CLOSE || message == WM_LBUTTONDOWN
      || (message == WM_KEYDOWN && wp == VK_ESCAPE))
   {
      PostQuitMessage(failures ? 1 : 0);
      return 0;
   }
   if (message == WM_TIMER)
   {
      // Sample the preceding presentation after the display had time to update.
      if (frame > 0)
      {
         HDC screen = GetDC(NULL);
         COLORREF color = GetPixel(screen, position.x + width - 20, position.y + height - 20);
         ReleaseDC(NULL, screen);
         if (frame == 1) firstColor = color;
         // Allow small compositor/rounding differences, but detect buildup.
         int dr = (int)GetRValue(color) - 144;
         int dg = (int)GetGValue(color) - 32;
         int db = (int)GetBValue(color) - 48;
         bool bad = color == CLR_INVALID || (checkerboardMode
            && (dr < -3 || dr > 3 || dg < -3 || dg > 3 || db < -3 || db > 3));
         if (bad) ++failures;
         fprintf(report, "frame=%lu source=0x80800000 screen=(%u,%u,%u) %s %s\n",
            frame, GetRValue(color), GetGValue(color), GetBValue(color),
            checkerboardMode ? "expected~(144,32,48)" : "desktop background varies",
            bad ? "MISMATCH" : (checkerboardMode ? "OK" : "OBSERVED"));
         fflush(report);
      }
      if (frameLimit && frame >= frameLimit)
      {
         PostQuitMessage(failures ? 1 : 0);
         return 0;
      }
      // Reconstruct both surfaces on every tick. Text changes every frame;
      // the lower-right sample remains plain half-transparent red.
      GdiFlush();
      ZeroMemory(textPixels, width * height * sizeof(DWORD));
      char counter[80];
      sprintf(counter, "Frame: %lu", frame + 1);
      SetBkMode(textDC, TRANSPARENT);
      SetTextColor(textDC, RGB(255, 255, 255));
      TextOutA(textDC, 20, 20, counter, (int)strlen(counter));
      const char *label = checkerboardMode
         ? "Checkerboard test - 20 FPS"
         : "Desktop translucency - 20 FPS";
      TextOutA(textDC, 20, 55, label, (int)strlen(label));
      const char *hint = "Click this translucent window to stop";
      TextOutA(textDC, 20, 90, hint, (int)strlen(hint));
      GdiFlush();
      for (int i = 0; i < width * height; ++i)
      {
         // GDI text supplies coverage in RGB but no valid alpha. Composite
         // its white mask over red ourselves to keep premultiplied BGRA.
         unsigned coverage = GetRValue(textPixels[i]);
         unsigned alpha = 128 + (127 * coverage + 127) / 255;
         sourcePixels[i] = (alpha << 24) | (alpha << 16)
            | (coverage << 8) | coverage;
      }
      SIZE size = {width, height};
      POINT origin = {0, 0};
      BLENDFUNCTION blend = {AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
      SetLastError(0);
      BOOL ok = UpdateLayeredWindow(window, NULL, &position, &size,
         sourceDC, &origin, 0, &blend, ULW_ALPHA);
      DWORD error = ok ? 0 : GetLastError();
      if (!ok) ++failures;
      fprintf(report, "present=%lu success=%d error=%lu\n", frame, ok, error);
      fflush(report);
      GdiFlush();
      ++frame;
      return 0;
   }
   return DefWindowProcA(window, message, wp, lp);
}

int main(int argc, char **argv)
{
   // Keep window coordinates and screen-pixel sampling in the same units
   // on scaled Windows desktops. This optional API is absent on XP/ReactOS.
   typedef BOOL (WINAPI *SetDpiAware)();
   SetDpiAware setDpiAware = reinterpret_cast<SetDpiAware>(
      GetProcAddress(GetModuleHandleA("user32.dll"), "SetProcessDPIAware"));
   if (setDpiAware) setDpiAware();
   for (int arg = 1; arg < argc; ++arg)
   {
      if (strcmp(argv[arg], "--checkerboard") == 0) checkerboardMode = true;
      else if (strcmp(argv[arg], "--frames") == 0 && arg + 1 < argc)
         frameLimit = strtoul(argv[++arg], NULL, 10);
      else
      {
         fprintf(stderr, "Usage: layered-probe.exe [--checkerboard] [--frames N]\n");
         return 2;
      }
   }
   char path[MAX_PATH];
   if (!GetModuleFileNameA(NULL, path, MAX_PATH)) return 2;
   char *end = path;
   for (char *c = path; *c; ++c) if (*c == '\\' || *c == '/') end = c + 1;
   const char name[] = "layered-probe.log";
   if (end - path + sizeof(name) > MAX_PATH) return 2;
   CopyMemory(end, name, sizeof(name));
   report = fopen(path, "w");
   if (!report) return 2;
   fprintf(report, "Premultiplied alpha probe. Mode=%s; sample source=(128,0,0,128).\n"
      "Continuous redraw with frame counter. Click the red surface to stop.\n",
      checkerboardMode ? "checkerboard with fixed sample background" : "actual desktop; no opaque backing window");
   HINSTANCE instance = GetModuleHandleA(NULL);
   WNDCLASSA backgroundClass = {};
   backgroundClass.hInstance = instance;
   backgroundClass.lpfnWndProc = BackgroundProc;
   backgroundClass.lpszClassName = "Ca2LayeredProbeBackground";
   WNDCLASSA layeredClass = backgroundClass;
   layeredClass.lpfnWndProc = LayeredProc;
   layeredClass.lpszClassName = "Ca2LayeredProbeForeground";
   RegisterClassA(&backgroundClass);
   RegisterClassA(&layeredClass);
   if (checkerboardMode)
   {
   backgroundWindow = CreateWindowExA(WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
      backgroundClass.lpszClassName, "Layered probe - close to stop", WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
      position.x - 20, position.y - 20, width + 60, height + 90,
      NULL, NULL, instance, NULL);
   position.x = 20;
   position.y = 20;
   ClientToScreen(backgroundWindow, &position);
   }
   layeredWindow = CreateWindowExA(WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW,
      layeredClass.lpszClassName, "Layered probe", WS_POPUP,
      position.x, position.y, width, height, NULL, NULL, instance, NULL);
   BITMAPINFO info = {};
   info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
   info.bmiHeader.biWidth = width;
   info.bmiHeader.biHeight = -height;
   info.bmiHeader.biPlanes = 1;
   info.bmiHeader.biBitCount = 32;
   info.bmiHeader.biCompression = BI_RGB;
   void *pixels = NULL;
   sourceDC = CreateCompatibleDC(NULL);
   sourceBitmap = CreateDIBSection(sourceDC, &info, DIB_RGB_COLORS, &pixels, NULL, 0);
   sourcePixels = (DWORD *)pixels;
   void *maskPixels = NULL;
   textDC = CreateCompatibleDC(NULL);
   textBitmap = CreateDIBSection(textDC, &info, DIB_RGB_COLORS, &maskPixels, NULL, 0);
   textPixels = (DWORD *)maskPixels;
   if ((checkerboardMode && !backgroundWindow) || !layeredWindow || !sourceDC || !sourceBitmap || !pixels
      || !textDC || !textBitmap || !textPixels)
   {
      fprintf(report, "SETUP FAILED error=%lu\n", GetLastError());
      fclose(report);
      return 2;
   }
   previousBitmap = SelectObject(sourceDC, sourceBitmap);
   previousTextBitmap = SelectObject(textDC, textBitmap);
   if (checkerboardMode)
   {
      ShowWindow(backgroundWindow, SW_SHOWNOACTIVATE);
      UpdateWindow(backgroundWindow);
   }
   ShowWindow(layeredWindow, SW_SHOWNOACTIVATE);
   if (!SetTimer(layeredWindow, 1, 50, NULL)) return 2;
   MSG message;
   BOOL next;
   while ((next = GetMessageA(&message, NULL, 0, 0)) > 0)
   {
      TranslateMessage(&message);
      DispatchMessageA(&message);
   }
   int result = next == -1 ? 2 : (int)message.wParam;
   KillTimer(layeredWindow, 1);
   fprintf(report, "RESULT: %s; frames=%lu mismatches=%lu; first=(%u,%u,%u)\n",
      failures ? "FAIL (check for overlap or opacity buildup)"
         : (checkerboardMode ? "PASS" : "OBSERVATION COMPLETE (desktop mode has no fixed-color assertion)"),
      frame, failures, GetRValue(firstColor), GetGValue(firstColor), GetBValue(firstColor));
   DestroyWindow(layeredWindow);
   if (backgroundWindow) DestroyWindow(backgroundWindow);
   SelectObject(sourceDC, previousBitmap);
   DeleteObject(sourceBitmap);
   DeleteDC(sourceDC);
   SelectObject(textDC, previousTextBitmap);
   DeleteObject(textBitmap);
   DeleteDC(textDC);
   fclose(report);
   printf("Layered-window probe finished. See %s\n", path);
   return result;
}

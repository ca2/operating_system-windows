#include "framework.h"
#include "console.h"
#include "file_system.h"

#include "acme/_operating_system.h"

#include <io.h>
#include <stdio.h>
#include <fcntl.h>


namespace acme_windows
{


   console::console()
      //:      m_cout(nullptr)
   {


      //SetThreadLocale(437);
      //SetThreadUILanguage(437);
      


      AllocConsole();

      SetConsoleOutputCP(437);

      m_pfileOut = __create_new< std_out_buffer >();

      m_cout.m_pfile = m_pfileOut;


      //CONSOLE_FONT_INFOEX info = {};
      //info.cbSize = sizeof(info);
      //GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),false,&info);


      //info.dwFontSize.X = 14;
      //info.dwFontSize.Y = 24;
      ////wcscpy(info.FaceName,L"Consolas");
      //wcscpy(info.FaceName, L"Comic Code");
      //info.FontFamily = 54;
      //info.FontWeight = 800;
      //info.nFont = 0;

      //if(!SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE),false,&info))
      //{
      //   //TRACELASTERROR();
      //}

   }


   console::~console()
   {

      FreeConsole();

   }


   //::write_text_stream < ::file::file > & console::cout()
   //{

   //   return m_cout;

   //}

   // maximum mumber of lines the output console should have

   static const unsigned short MAX_CONSOLE_LINES = 500;

   void console::redirect_io()
   {

      //int hConHandle;

      //HANDLE lStdHandle;

      //CONSOLE_SCREEN_BUFFER_INFO coninfo;

      //FILE *fp;

      //// allocate a console for this app

      //// set the screen buffer to be big enough to let us scroll text

      //GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),

      //                           &coninfo);

      //coninfo.dwSize.Y = MAX_CONSOLE_LINES;

      //SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),

      //                           coninfo.dwSize);

      //// redirect unbuffered STDOUT to the console

      //lStdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

      //hConHandle = _open_osfhandle((intptr_t) lStdHandle,_O_TEXT);

      //fp = _fdopen(hConHandle,"w");

      //*stdout = *fp;

      //setvbuf(stdout,nullptr,_IONBF,0);

      //// redirect unbuffered STDIN to the console

      //lStdHandle = GetStdHandle(STD_INPUT_HANDLE);

      //hConHandle = _open_osfhandle((intptr_t) lStdHandle,_O_TEXT);

      //fp = _fdopen(hConHandle,"r");

      //*stdin = *fp;

      //setvbuf(stdin,nullptr,_IONBF,0);

      //// redirect unbuffered STDERR to the console

      //lStdHandle = GetStdHandle(STD_ERROR_HANDLE);

      //hConHandle = _open_osfhandle((intptr_t) lStdHandle,_O_TEXT);

      //fp = _fdopen(hConHandle,"w");

      //*stderr = *fp;

      //setvbuf(stderr,nullptr,_IONBF,0);

      //make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog

      //int_point to console as well

      //ios::sync_with_stdio();

   }


   void console::SetWindowSize(int height,int width)
   {
      m_iH = height;
      m_iW = width;
      SMALL_RECT window;
      window.Top = 0;
      window.Left = 0;
      window.Bottom = height - 1;
      window.Right = width - 1;
      SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE),true,&window);
      COORD buffer = {(SHORT)width,(SHORT)height};
      SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),buffer);

   }

   void console::SetCursorVisibility(bool show)
   {
      CONSOLE_CURSOR_INFO cursor;
      GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
      cursor.bVisible = show;
      SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor);
   }

   void console::SetCursorPosition(int y,int x)
   {
      COORD cursor = {(SHORT)x,(SHORT)y};
      SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),cursor);
   }

   void console::SetTextColor(int color)
   {
      m_iTextColor = color;
      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
   }

   
   void console::SetScreenColor(enum_dos_color edoscolor, int iLineStart, int iLineCount)
   {

      COORD coord = {0,(SHORT)iLineStart};

      DWORD dwWritten;

      if (iLineCount < 0)
      {

         iLineCount = m_iH + iLineCount + 1;

      }

      if (iLineCount > m_iH - iLineStart)
      {

         iLineCount = m_iH - iLineStart;

      }

      FillConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int) edoscolor,iLineCount * m_iW,coord,&dwWritten);

   }


   void console::write(const ::scoped_string & scopedstr)
   {

      m_pfileOut->write( scopedstr.c_str(),scopedstr.length() );

   }


} // namespace acme_windows









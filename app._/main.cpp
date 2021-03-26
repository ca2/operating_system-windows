#define NO_DRAW2D
#define NO_IMAGING
#include "apex/console.h"
#include "apex/user/_.h"

#define PATH_INSTALL_FOLDER_EXE_ARG 1

#include "acme/os/_os.h"
#include <stdio.h>
#include <psapi.h>
#include <tlhelp32.h>
#include "aura/_defer.h"


#define IDI_CC_CA2_SPA       107
#define IDI_CC_CA2_LEVEL    108

string path_dir_name_for_relative(const char * pszPath);
//string solve_relative(const char * pszAbsolute);
//string path_defer_solve_relative_name(const char * pszRelative, const char * pszAbsolute);


// These next two structs represent how the icon information is stored
// in an ICO file.
struct ICON_ITEM
{
   BYTE  bWidth;               // Width of the image
   BYTE  bHeight;              // Height of the image (times 2)
   BYTE  bColorCount;          // Number of colors in image (0 if >=8bpp)
   BYTE  bReserved;            // Reserved
   WORD  wPlanes;              // Color Planes
   WORD  wBitCount;            // Bits per pixel
   DWORD dwBytesInRes;         // how many bytes in this resource?
   DWORD dwImageOffset;        // where in the file is this image
};

struct ICON_HEADER
{
   WORD        idReserved;   // Reserved
   WORD        idType;       // resource type (1 for icons)
   WORD        idCount;      // how many images?
};


void dprint(const char * psz)
{



   //string str;

   //str.Format("app._ : %s : %s\n",_wargv[2],psz);

   //printf("%s", str);



}


struct MEM_ICON_ITEM
{
   BYTE  bWidth;               // Width of the image
   BYTE  bHeight;              // Height of the image (times 2)
   BYTE  bColorCount;          // Number of colors in image (0 if >=8bpp)
   BYTE  bReserved;            // Reserved
   WORD  wPlanes;              // Color Planes
   WORD  wBitCount;            // Bits per pixel
   DWORD dwBytesInRes;         // how many bytes in this resource?
   WORD  nID;                  // the ID

};

struct MEM_ICON_HEADER
{
   WORD        idReserved;   // Reserved
   WORD        idType;       // resource type (1 for icons)
   WORD        idCount;      // how many images?
};


void copy(MEM_ICON_ITEM * dst, ICON_ITEM * pitem)
{
   dst->bWidth = pitem->bWidth;
   dst->bHeight = pitem->bHeight;
   dst->bColorCount = pitem->bColorCount;
   dst->bReserved = pitem->bReserved;
   dst->wPlanes = pitem->wPlanes;
   dst->wBitCount = pitem->wBitCount;
   dst->dwBytesInRes = pitem->dwBytesInRes;
}


//namespace appfy
//{
//
//
//
//   application::application()
//   {
//
//      //{
//
//      //   string_array stra;
//
//      //   stra.add("C:\\a\\b\\c\\..\\..\\..\\d\\");
//      //   stra.add("C:\\");
//      //   stra.add("C:\\.");
//      //   stra.add("C:\\.\\");
//      //   stra.add("C:\\..");
//      //   stra.add("C:\\..\\");
//      //   stra.add("C:\\a\\");
//      //   stra.add("C:\\a\\.");
//      //   stra.add("C:\\a\\.\\");
//      //   stra.add("C:\\a\\..\\");
//      //   stra.add("C:\\a\\.\\b");
//      //   stra.add("C:\\a\\.\\b\\");
//      //   stra.add("C:\\a\\..\\b");
//      //   stra.add("C:\\a\\..\\b\\");
//
//      //   for (auto& str : stra)
//      //   {
//
//      //      output_debug_string("Converting: \"" + str + "\"\n");
//
//      //      ::file::path path = solve_relative(str);
//
//      //      output_debug_string("into: -> \"" + string(path.c_str()) + "\"\n");
//
//      //   }
//
//      //}
//      ////////////////////////////////////////////////////////////
//      // configuration encryption system : with C:\\" hardware :-)
//      // short login               short password  access configuration
//      // |                         |               |
//      // -----------------------   --       --------
//      //                       |    |       |
//      if (file_exists(::dir::system() / "config\\appfy\\appfy_beg_debug_box.txt"))
//      {
//         debug_box("app_app_admin", "app", 0);
//      }
//
//      //m_hinstance = ::GetModuleHandleA(nullptr);
//
//      //get_application() = this;
//
//      m_bLicense = false;
//
//
//   }
//
//
//   application::~application()
//   {
//
//   }
//
//
//   void application::on_request(::create* pcreate)
//   {
//
//      appfy();
//
//      set_finish();
//
//   }


void wmain(int argc, wchar_t * wargv[])
{

   console console(argc, wargv);

   string strSrc;

   string strApp;

   {

      if (file_exists(::dir::system() / "config/plugin/appfy_beg_debug_box.txt"))
      {

         ::MessageBoxA(nullptr,"appfy run", "appfy run", MB_OK);

      }


      if (__argc < 4)
      {

         os_message_box("Incorrect Number of Arguments passed to appfy. Expected 3 or 4; passed " + __str(__argc - 1), "", e_message_box_ok);

         papplication->m_result.add(error_invalid_argument);

         return;

      }

      dprint("Starting!!");

      strSrc = solve_relative(psystem->get_arg(1));

      strApp = psystem->get_arg(2);

      string strDst = solve_relative(psystem->get_arg(3));

      string strBuild = psystem->get_arg(4);

      if (strBuild.is_empty())
      {

         //      strBuild = ca2_get_build("stage");

      }


      string strRoot;

      string strDomain;

      index iFind = strApp.find("/");

      if (iFind >= 0)
      {
         strRoot = strApp.Left(iFind);
         strDomain = strApp.Mid(iFind + 1);
      }
      else
      {
         string strParse(strApp);

            
         if (::str::begins_eat_ci(strParse, "app_core_"))
         {
            strRoot = "app-core";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "app_veriwell_"))
         {
            strRoot = "app-veriwell";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "app_cidadedecuritiba_"))
         {
            strRoot = "app-cidadedecuritiba";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "app_gtech_"))
         {
            strRoot = "app-gtech";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "app_frontpage_"))
         {
            strRoot = "app-frontpage";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "app_sysutils_"))
         {
            strRoot = "app-sysutils";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "design_"))
         {
            strRoot = "design";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "game_"))
         {
            strRoot = "game";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "rootkiller_"))
         {
            strRoot = "rootkiller";
            strDomain = strParse;
         }
         else if (::str::begins_eat_ci(strParse, "app_"))
         {

            auto iFind = strParse.find("_");

            if (iFind < 0)
            {
               strRoot = "app";
               strDomain = strParse;
            }
            else
            {
               strRoot = "app-" + strParse.Left(iFind);
               strDomain = strParse.Mid(iFind + 1);
            }
         }
         else if (::str::begins_eat_ci(strParse, "platform_"))
         {
            
            strRoot = "platform";
            strDomain = strParse;

         }
         else
         {

            ::file::listing listing;

            string strListing = strBuild;
            
            solve_relative(strBuild);

            ::file::path pathListing = strListing;

            pathListing = pathListing.folder(4);

            auto& dir = papplication->dir();

            dir.ls_dir(listing, pathListing);

            string_array straPrefix;

            for (auto& path : listing)
            {

               string strPrefix(path.name());

               strPrefix.replace("-", "_");

               strPrefix += "_";

               straPrefix.add(strPrefix);

            }

            auto iFind = straPrefix.prefix_find_first_ci(strParse);

            if (iFind >= 0)
            {

               string strPrefix = straPrefix[iFind];

               if (::str::begins_eat_ci(strParse, strPrefix))
               {

                  strRoot = listing[iFind].name();

                  strDomain = strParse;

               }

            }
            else
            {

               auto iFind = strParse.find("_");

               if (iFind > 0)
               {
                  strRoot = strParse.Left(iFind);
                  strDomain = strParse.Mid(iFind + 1);
               }
               else
               {
                  strRoot = strApp;
                  strDomain = "";
               }

            }

         }

      }

      dprint("a bit of parsing!!");

      if (!file_exists(strSrc))
      {

         printf("%s", 
            ("Couldn't update resources for \"" + strApp + "\".\n\nDoes the file \"" + strSrc + "\" exists at the moment of this application call?").c_str());

         return;

      }

      pcontext->m_pcontext->file().copy(strDst, strSrc, false);

      dprint("main copy should be done!!");

      ::file::path pathIcon;

      ::file::path pathMatter = pcontext->m_pcontext->dir().matter("main/icon.ico", false, strRoot, strDomain);

      pathMatter |= ::file::e_flag_get_local_path;

      pathMatter = psystem->get_matter_cache_path(pathMatter);

      if (pcontext->m_pcontext->file().exists(pathMatter))
      {

         pathIcon = pathMatter;

      }

      dprint("does main frame icon exist 1!!");

      if (pathIcon.is_empty())
      {

         pathMatter = pcontext->m_pcontext->dir().matter("main/icon.ico", false);

         pathMatter |= ::file::e_flag_get_local_path;

         if (pcontext->m_pcontext->file().exists(pathMatter))
         {

            pathIcon = pathMatter;

         }

         dprint("does main frame icon exist 2!!");

      }


      HANDLE hupdate = BeginUpdateResourceW(wstring(strDst), false);

      dprint("BeginUpdateResource");

      dprint(strDst);

      if (hupdate != nullptr)
      {

         dprint("hupdate ok");

      }
      else
      {

         dprint("hupdate false");

         papplication->m_result.add(error_failed);

         message_box("Couldn't update resources for \"" + strApp + "\".\n\nDoes the file \"" + strSrc + "\" exists at the moment of this application call and is it valid so far?", nullptr, e_message_box_icon_exclamation);

         return;

      }

      if (pcontext->m_pcontext->file().exists(pathIcon))
      {

         memory memory;
            
         ::memory memoryItem;

         auto pfileHd = create_memory_file();

         pcontext->m_pcontext->file().as_memory(pathIcon, memory);

         dprint("icon as memory");

         ICON_HEADER* phd = (ICON_HEADER*)memory.get_data();

         int iTotalHd = sizeof(ICON_HEADER) + (sizeof(ICON_ITEM) * phd->idCount);

         ICON_ITEM* itema = (ICON_ITEM*)(memory.get_data() + 6);

         MEM_ICON_HEADER hd;

         hd.idReserved = phd->idReserved;
         hd.idType = phd->idType;
         hd.idCount = phd->idCount;

         pfileHd->write(&hd, sizeof(hd));

         int iSize = iTotalHd;
         for (int i = 0; i < phd->idCount; i++)
         {
            ICON_ITEM* pitem = &itema[i];
            MEM_ICON_ITEM item;
            ::copy(&item, pitem);
            item.nID = IDI_CC_CA2_SPA + i + 1;
            UpdateResourceW(hupdate, RT_ICON, MAKEINTRESOURCE(IDI_CC_CA2_SPA + i + 1), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), memory.get_data() + pitem->dwImageOffset, pitem->dwBytesInRes);
               
            pfileHd->write(&item, 14);

         }

         UpdateResourceW(hupdate, RT_GROUP_ICON, L"MAINICON", MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), pfileHd->get_data(), (DWORD)(pfileHd->get_size()));

         dprint("icon should be updated");

      }

//      UpdateResourceW(hupdate, L"LEVEL", MAKEINTRESOURCE(IDI_CC_CA2_LEVEL), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (LPVOID) strLevel.c_str(), strLevel.get_length());

      string strCoreApp;

      if (strRoot.has_char())
      {
         if (strDomain.has_char())
         {
            strCoreApp = strRoot + "/" + strDomain;
         }
         else
         {
            strCoreApp = strRoot;
         }
      }
      else
      {
         if (strDomain.has_char())
         {
            strCoreApp = strDomain;
         }
      }
      if (strCoreApp.has_char())
      {
         UpdateResourceW(hupdate, L"APPID", MAKEINTRESOURCE(1), MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (LPVOID)(LPCSTR)strCoreApp, (DWORD)(strCoreApp.get_length()));
         dprint("APPID should be updated");
      }

      EndUpdateResourceW(hupdate, false);

      printf("%s", ("Program \"" + strDst + "\" successfully generated!!").c_str());

   }

}



#define PATH_SEP1 "\\"
#define PATH_SEP2 "/"


   string path_url_dir_name_for_relative(const char* pszPath)
   {
      string strDir(pszPath);

      if (str::ends(strDir, PATH_SEP1))
         return strDir;

      if (str::ends(strDir, PATH_SEP2))
         return strDir;

      strsize iFind1 = strDir.reverse_find(PATH_SEP1);
      strsize iFind2 = strDir.reverse_find(PATH_SEP2);
      strsize iFind = maximum(iFind1, iFind2);

      if (iFind < 0)
         return PATH_SEP1;

      return strDir.substr(0, iFind + 1);

   }


#undef new
void init_exception_engine(class ::exception_engine * pexceptionengine)
{

   new(pexceptionengine) class ::PLATFORM_NAMESPACE::exception_engine;

}







//::aura::application * get_acid_app()
//{
//
//   return new ::appfy::application();
//
//}




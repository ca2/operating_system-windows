// Created by camilo on 2023-08-17 09:54 <3ThomasBorregaardSorensen!
#include "framework.h"
#include "node.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/_operating_system.h"
#include <mmsystem.h>
#pragma comment( lib, "Winmm.lib" )


namespace acme_windows
{



   void node::play_sound(const ::file::path& path)
   {

      ::string pathFileSystem = file()->get_filesystem_file(path);

      wstring wstr(pathFileSystem);

      ::PlaySound(wstr, NULL, SND_FILENAME | SND_ASYNC);

   }



} // namespace acme_windows




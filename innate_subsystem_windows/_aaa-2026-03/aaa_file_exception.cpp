// Created by camilo on 2022-08-30 09:25 <3ThomasBorregaardSorensen!! (ThomasLikesNumber5!!)
#include "../framework.h"
#include "file_exception.h"


windows_file_exception::windows_file_exception(const ::e_status & estatus, int iOsError, const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrMessage) :
   ::file_exception(estatus, iOsError, strPath, strMessage)
{

}




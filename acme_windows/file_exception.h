// Created by camilo on 2021-06-03 01:37 <3ThomasBS_!!
#pragma once


class CLASS_DECL_ACME_WINDOWS windows_file_exception :
   public ::file_exception
{
public:


   windows_file_exception(const ::e_status & estatus, int iOsError, const ::string & strPath);


};




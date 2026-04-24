// Copyright (C) 2009,2010,2011,2012 GlavSoft LLC.
// All rights reserved.
//
//-------------------------------------------------------------------------
// This file is part of the TightVNC software.  Please visit our Web site:
//
//                       http://www.tightvnc.com/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, w_rite to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
//-------------------------------------------------------------------------
//

 #pragma once


#include "subsystem/node/OperatingSystem.h"
 //////#include "subsystem/platform/::string.h"
 //#include "log_writer/LogWriter.h"

 // #include aaa_<winnt.h>

 namespace subsystem_windows
 {
    
    
    class CLASS_DECL_SUBSYSTEM_WINDOWS OperatingSystem : public ::subsystem::OperatingSystem
    {
    public:
       //static const int APPLICATION_DATA_SPECIAL_FOLDER = 0x0;
       //static const int COMMON_APPLICATION_DATA_SPECIAL_FOLDER = 0x1;
    //public:
       OperatingSystem();
       ~OperatingSystem();

       // Formates string from last system error code.
       // @return false on an error.
       ::string getErrStr() override;

       // Formates string from last system error code with specification before.
       // @return ::string object that contain error describing with
       // secificatioin.
       ::string getErrStr(const ::scoped_string &scopedstrSpecification) override;

       //
       // Sets path to special folder value to out argument.
       //
       // Valid values for specialFolderId argument are:
       //  - Node::APPLICATION_DATA_SPECIAL_FOLDER
       //  - Node::COMMON_APPLICATION_DATA_SPECIAL_FOLDER
       //
       // Remark: if caller set invalid value into specialFolderId assertion
       // will be failed.
       //

       ::string getSpecialFolderPath(int specialFolderId) override;

       // Sets full path to current executing process file to out argument
       ::string getCurrentModulePath() override;

       // pId - the process id that be tested
       // return true if tested process has the same path as current process
       // else return false
       // throw Exception an error.
       bool isItTheSamePathAsCurrent(unsigned int pId) override;

       // Sets full path to folder (without last directory separator character)
       // where current executing process file is located to out argument.
       ::string getCurrentModuleFolderPath() override;

       // Returns user name of the current desktop
       //bool getCurrentUserName(::string & out, LogWriter *log) override;
       ::string getCurrentUserName() override;

      // Fills "out" by computer name string.
      // Returns true if success.
       ::string getComputerName() override;

       // Returns true if run under a windows NT family
       bool isWinNTFamily() override;
       // Returns true if run under windows XP
       bool isWin2000() override;
       // Returns true if run under windows XP
       bool isWinXP() override;
       // Returns true if run windows 2003 server.
       bool isWin2003Server() override;
       // Returns true if run under Windows Vista or later
       bool isVistaOrLater() override;
       // Returns true if run Windows7 or Win2008 R2 server.
       bool isWin7() override;

       // Simulates the "ctrl + alt + del" combination under WindowsXP.
       void simulateCtrlAltDel(::subsystem::LogWriter *log) override;

       // Simulates the "ctrl + alt + del" combination by using the "SAS" lib.
       void simulateCtrlAltDelUnderVista(::subsystem::LogWriter *log) override;

       // Returns true if the Aero is On.
       bool isAeroOn(::subsystem::LogWriter *log) override;

       bool isUserAnAdmin() override;

    //private:
       //void init() override;
       // Operation system version info.
       //OSVERSIONINFO m_osVerInfo;
    };


 } // namespace subsystem



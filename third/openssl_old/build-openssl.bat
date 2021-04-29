@echo off
SETLOCAL EnableExtensions EnableDelayedExpansion
::
:: ========================================================================================================
:: ==== OpenSSL Library compilation with MSVC
:: ========================================================================================================
:: 
::      Author: stathis <stathis@npcglib.org>
::    Revision: $Id: build-openssl-1.1.0e.bat 4862 2017-02-17 18:54:35Z stathis $
::
:: Description: This script can be used to compile the OpenSSL Library with MSVC
::              The script builds all (8) permutations of:
::              (x86 | x64) - (static | shared) - (debug | release)
::
::              ATTENTION: Before compiling OpenSSL, you need to patch the sources to enable building 
::                         the libraries with different suffixes. (see usage on how to patch)
::
::  Changelog:
::
:: 17/02/2017 - Built 1.1.0e.
::
:: 26/01/2017 - Built 1.1.0d. Added ssl, html and log dirs.
::              The logs dir includes the config, build, test and install logs for reference.
::
:: 25/01/2017 - Fixed a problem in shlibload test [thanks Diego]
::
:: 10/11/2016 - Built 1.1.0c, but tests fail on most compilers 2013/2012/2010/2008.
::              It works on VS2015, but I opt for no release.
::
:: 02/10/2016 - First attempt on the 1.1.x build script
::
:: 02/12/2015 - Added some of the OpenSSL info files (e.g. LICENSE, README, etc.)
::
:: 22/10/2015 - Headers of 64-bit and 32-bit builds are now in separate directories (include vs include64)
::              [thanks Paul H.]
::
:: 22/07/2015 - Build log files are now produced during builds.
::
:: 25/10/2013 - Various fixes to enable packaging the required debug symbols for the produced libraries.
::            - Patching has now been migrated to a single patch per release (for the whole source tree)
::
:: 04/03/2013 - created patches for mk1mf.pl, mkdef.pl and util/VC-32.pl to enable different library
::              suffixes, according to the run-time library linked against:
::
::              {libname}MT   -- statically linked release OpenSSL libraries
::              {libname}MTd  -- statically linked debug OpenSSL libraries
::              {libname}MD   -- dynamically linked release OpenSSL libraries
::              {libname}MDd  -- dynamically linked release OpenSSL libraries
::
:: ========================================================================================================
:: ==== <CONFIGURATION>
:: ========================================================================================================
::
:: Set the version of Visual Studio. This will just add a suffix to the string
:: of your directories to avoid mixing them up.
SET VS_VERSION=2017

:: Set this to the directory that contains vcvarsall.bat file of the 
:: VC Visual Studio version you want to use for building the library.
SET VISUAL_STUDIO_VC=C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Auxiliary\Build

:: Set CYGWIN_DIR to the location of your Cygwin root ( one level up from /bin )
:: You can use any Cygwin installation, including a portable cygwin: 
:: https://github.com/search?q=cygwin+portable
:: Make sure you install the following cygwin packages: p7zip, md5sum, patch

SET CYGWIN_DIR=C:\Cygwin

SET PERL_ROOT=C:\Strawberry\

rem ========================================================================================================

:: Set here the 7z command line to use for creating packages
:: Use an absolute path to the 7z.exe utility if it is not in your path.
:: -mx0 store compression
:: -mx9 ultimate compression
SET SEVENZIP_CMD=7z
::SET SEVENZIP_CMD_OPTIONS=a -r -mx9

:: Set here the location of the md5sum command, which is used to create md5 
:: checksums for the archives after packaging
:: Use an absolute path to the md5sum.exe utility or append its directory in your PATH.
SET MD5SUM_CMD=md5sum

:: Set here the date command
:: Use an absolute path to the date.exe utility or append its directory in your PATH.
SET DATE_CMD=date

:: Set here the patch command
:: Use an absolute path to the patch.exe utility or append its directory in your PATH.
SET PATCH_CMD=patch

:: Set here the patch command
:: Use an absolute path to the patch.exe utility or append its directory in your PATH.
SET DOS2UNIX_CMD=dos2unix

rem ========================================================================================================

:: Set this to the name of the project
SET BUILD_PROJECT=openssl

:: Set this to the version of the project you are building
SET PROJECT_VERSION=1.1.1a

:: SET PROJECT_SRC_DIR=D:\opensource\!BUILD_PROJECT!-!PROJECT_VERSION!
SET PROJECT_SRC_DIR=C:\third\windows\source\!BUILD_PROJECT!
SET PROJECT_BUILD_DIR=C:\third\windows\build\!BUILD_PROJECT!
SET PROJECT_INSTALL_DIR=C:\third\windows\dist\!BUILD_PROJECT!

rem ========================================================================================================
rem == PLEASE DO NOT EDIT BELOW THIS LINE
rem ========================================================================================================

rem We load the config file first
call :loadconfig "%~dpn0"

rem we then carry on execution
call :execScript %0 %1 %2 %3 %4

ENDLOCAL

@exit /B 0

rem ========================================================================================================
rem == Pseudo-function to load config
rem ========================================================================================================

:loadconfig
rem set the variable HOSTNAME by executing the command (that's the computer's name)
FOR /F "delims=" %%a IN ('hostname') DO @set HOSTNAME=%%a

rem strip double quotes
set scriptFile=%1
set scriptFile=%scriptFile:"=%

rem We use two files: myScript.conf and myScript.<HOSTNAME>
rem myScript.<HOSTNAME> overrides myScript.conf
rem %~dpn0 is the full file minus the extension.
FOR %%c IN (
	"!scriptFile!.conf"
	"!scriptFile!.!HOSTNAME!"
) DO (
	IF EXIST "%%c" (
		ECHO.
		ECHO # Loading local configuration from: %%c
		ECHO.
		FOR /F "usebackq delims=" %%v IN (%%c) DO (set %%v)
	)
)

GOTO :eof

rem ========================================================================================================

:execScript
rem Use this pseudo-function to write the code of your main script
SETLOCAL EnableExtensions EnableDelayedExpansion

SET scriptName=%1
SET arg[0]=%2
SET arg[1]=%3
SET arg[2]=%4
SET arg[3]=%5

:: ATTENTION: this is down here because out-of-source builds are not supported DO NOT CHANGE IT!
:: SET PROJECT_BUILD_DIR=!PROJECT_SRC_DIR!\build

IF "!SEVENZIP_CMD_OPTIONS!" == "" (
	SET SEVENZIP_CMD_OPTIONS=a -r -mx9
)

FOR /F "delims=" %%a IN ('!CYGWIN_DIR!/bin/cygpath -p -u !SEVENZIP_CMD!') DO @set __SEVENZIP_CMD=%%a


IF "!arg[0]!" == "" GOTO usage
IF NOT EXIST "!PROJECT_SRC_DIR!" (
	ECHO.
	CALL :exitB "ERROR: Source directory !PROJECT_SRC_DIR! does not exist or does not contain the !BUILD_PROJECT! sources. Aborting."
	GOTO :eof
)

IF NOT EXIST "!VISUAL_STUDIO_VC!\vcvarsall.bat" (
	ECHO.
	CALL :exitB "ERROR: !VISUAL_STUDIO_VC!\vcvarsall.bat does not exist. Aborting."
	GOTO :eof
)


IF "!DATE_CMD_OPTIONS!" == "" (
	SET DATE_CMD_OPTIONS=%%d %%b %%Y
)


SET argC=-1
FOR %%x in (%*) DO SET /A argC+=1

if /i "!arg[0]!" == "build" (

	if !argC! == 2 (

		if /i "!arg[1]!" == "all" (

			echo.
			echo You are about to build all permutations [x86^|x64] [static^|shared] [debug^|release]
			echo.

			timeout /t 5
					
			call :buildall
			goto :eof
			
		) else (
			goto usage
		)
		
	) else if !argC! == 4 (

		call :callArch !arg[1]! !arg[2]! !arg[3]!
		goto :eof
		
	) else (
		goto usage
	)
	
) else if /i "!arg[0]!" == "package" (

	if !argC! == 2 (

		if /i "!arg[1]!" == "all" (

			echo.
			echo You are about to package all permutations [x86^|x64] [static^|shared] [debug^|release]
			echo.

			timeout /t 5
			
			call :createPackage
			goto :eof
			
		) else (
			goto usage
		)
		
	) else if !argC! == 3 (
		
		echo.
		echo This feature is currently unsupported. Only "package all" is supported at this time.
		echo.
			
		goto usage
		
		REM set archGood=false
		REM if /i "!arg[1]!" == "x86" set archGood=true
		REM if /i "!arg[1]!" == "x64" set archGood=true

		REM if /i "!archGood!" == "true" (

			REM call :createPackage !arg[0]! !arg[1]!
			REM goto :eof
			
		REM ) else (
			REM goto usage
		REM )
	) else (
		goto usage
	)
	
) else if /i "!arg[0]!" == "patch" (
	call :patch !PROJECT_VERSION!
) else if /i "!arg[0]!" == "unpatch" (
	call :unpatch !PROJECT_VERSION!
) else if !argC! == 3 (
	call :callArch !arg[0]! !arg[1]! !arg[2]!
	GOTO :eof
) else (
	GOTO usage
)

ENDLOCAL
GOTO :eof

rem ========================================================================================================
:printConfiguration
SETLOCAL EnableExtensions EnableDelayedExpansion
SET PATH=!CYGWIN_DIR!\bin;!CYGWIN_DIR!\usr\bin;!PATH!

echo.
echo                    PATH: !PATH!
echo.

echo              VS_VERSION: !VS_VERSION!
echo        VISUAL_STUDIO_VC: !VISUAL_STUDIO_VC!
echo              CYGWIN_DIR: !CYGWIN_DIR!
echo.
bash -c "echo -n \"           SEVENZIP_CMD: \" & which !__SEVENZIP_CMD!"
echo    SEVENZIP_CMD_OPTIONS: !SEVENZIP_CMD_OPTIONS!
bash -c "echo -n \"             MD5SUM_CMD: \" & which !MD5SUM_CMD!"
bash -c "echo -n \"               DATE_CMD: \" & which !DATE_CMD!"
bash -c "echo -n \"              PATCH_CMD: \" & which !PATCH_CMD!"
echo.
echo           BUILD_PROJECT: !BUILD_PROJECT!
echo         PROJECT_VERSION: !PROJECT_VERSION!
echo         PROJECT_SRC_DIR: !PROJECT_SRC_DIR!
echo       PROJECT_BUILD_DIR: !PROJECT_BUILD_DIR!
echo     PROJECT_INSTALL_DIR: !PROJECT_INSTALL_DIR!
ENDLOCAL
goto :eof

rem ========================================================================================================

:callArch
set archGood=false
if /i "%1" == "x86" set archGood=true
if /i "%1" == "x64" set archGood=true
if /i "!archGood!" == "true" (

	set linkGood=false
	if /i "%2"=="static" set linkGood=true
	if /i "%2"=="shared" set linkGood=true

	if /i "!linkGood!" == "true" (

		set buildGood=false
		if /i "%3" == "debug" set buildGood=true
		if /i "%3" == "release" set buildGood=true

		if /i "!buildGood!" == "true" (
		
			call :build %1 %2 %3
			goto :eof
			
		)
	)
	
)
goto usage
goto :eof

rem ========================================================================================================

:usage
call :printConfiguration
ECHO: 
ECHO Error in script usage. The correct usage is:
ECHO:
ECHO     !scriptName! [patch^|unpatch] - apply/remove patches to the sources
ECHO     !scriptName! build [all^|x86^|x64] ^<[static^|shared] [debug^|release]^> - builds all or specific permutations
ECHO     !scriptName! package [all^|x86^|x64] ^<[static^|shared]^> - creates a package file
ECHO:    
GOTO :eof

rem ========================================================================================================

:unpatch
rem remove patches from the sources
call :patch %1 unpatch
goto :eof

:patch
rem patch sources
::
:: To create a patch for mkdef.pl:
:: $ diff -u "F:\openssl-1.0.1e-orig\util\mk1mf.pl" "F:\openssl-1.0.1e\util\mk1mf.pl" > "%SSBUILDER_ROOT%\misc\openssl-1.0.1e-mk1mf.pl.patch"
:: $ diff -u "F:\openssl-1.0.1e-orig\util\mkdef.pl" "F:\openssl-1.0.1e\util\mkdef.pl" > "%SSBUILDER_ROOT%\misc\openssl-1.0.1e-mkdef.pl.patch"
:: $ diff -u "F:\openssl-1.0.1e-orig\util\pl\VC-32.pl" "F:\openssl-1.0.1e\util\pl\VC-32.pl" > "%SSBUILDER_ROOT%\misc\openssl-1.0.1e-VC-32.pl.patch"
::
:: To apply the patch:
::   cd into the unmodified openssl-x.x.x source directory
::   patch [--dry-run] -p2 -i "D:\dev\ssbuilder\misc\openssl-1.0.1e-mkdef.pl.patch"
::   patch [--dry-run] -p2 -i "D:\dev\ssbuilder\misc\openssl-1.0.1e-mkdef.pl.patch"
::
SETLOCAL EnableExtensions EnableDelayedExpansion

if /i "%2" == "unpatch" (
	SET EXTRA_TEXT=Removing
	SET EXTRA_FLAGS=-R
) else (
	SET EXTRA_TEXT=Applying
)

SET PATH=!CYGWIN_DIR!\bin;!CYGWIN_DIR!\usr\bin;

SET CYGWIN=nodosfilewarning

ECHO.
ECHO !EXTRA_TEXT! patches to [!BUILD_PROJECT! v%~1] sources
ECHO.

pushd "!PROJECT_SRC_DIR!"

	call :applyPatch !BUILD_PROJECT!-%~1.patch
	
popd

ENDLOCAL
goto :eof

:applyPatch
SET PATCH_FILE=%~dp0
SET PATCH_FILE=!PATCH_FILE!%1

IF NOT EXIST "!PATCH_FILE!" (

	call :exitB "Patch: [!PATCH_FILE!] does not exist. Aborting."

) ELSE (

	!DOS2UNIX_CMD! "!PATCH_FILE!"
	!PATCH_CMD! --binary !EXTRA_FLAGS! -N -p1 -i "!PATCH_FILE!"
	
)
goto :eof

rem ========================================================================================================

:createPackage

call :printConfiguration

echo:
echo Packaging OpenSSL Library
echo:

SET DIST_DIR=!PROJECT_INSTALL_DIR!\!BUILD_PROJECT!-!PROJECT_VERSION!-vs!VS_VERSION!

echo !DIST_DIR!

@mkdir !DIST_DIR!\bin 2>nul
@mkdir !DIST_DIR!\bin64 2>nul
@mkdir !DIST_DIR!\lib 2>nul
@mkdir !DIST_DIR!\lib64 2>nul
@mkdir !DIST_DIR!\include 2>nul
@mkdir !DIST_DIR!\include64 2>nul
@mkdir !DIST_DIR!\ssl 2>nul
@mkdir !DIST_DIR!\logs 2>nul

call :packagetype

echo:


ENDLOCAL
@exit /B 0

rem ========================================================================================================

:: %1 library type (e.g. static)
:packagetype

SET DST_DIST=!BUILD_PROJECT!-!PROJECT_VERSION!-vs!VS_VERSION!
SET DST_DIST_DIR=!PROJECT_INSTALL_DIR!\!DST_DIST!

for %%l in (static shared) do (
	for %%a in (x86 x64_amd64) do (
	
		if /i "%%a" == "x86" (
			SET BITS=32
			SET BITSTR=
		) else (
			SET BITS=64
			SET BITSTR=!BITS!
			SET PREFIX_WIN=!PREFIX_WIN!!BITS!
		)
		
		for %%b in (debug release) do (

			SET __ARCH=%%a
			SET __BUILD=%%b
			SET __LINK=%%l
			
			SET SRC_DIST_DIR=!PROJECT_INSTALL_DIR!\!BUILD_PROJECT!-!__ARCH!-!__LINK!-!__BUILD!-vs!VS_VERSION!

			echo [copy] !SRC_DIST_DIR! =^> !DST_DIST_DIR!
		
			if exist "!SRC_DIST_DIR!" (
						
				xcopy /Q /Y !SRC_DIST_DIR!\bin\*.dll !DST_DIST_DIR!\bin!BITSTR!\
				xcopy /Q /Y !SRC_DIST_DIR!\bin\*.lib !DST_DIST_DIR!\bin!BITSTR!\
				xcopy /Q /Y !SRC_DIST_DIR!\bin\*.pdb !DST_DIST_DIR!\bin!BITSTR!\
				xcopy /Q /Y !SRC_DIST_DIR!\bin\*.exe !DST_DIST_DIR!\bin!BITSTR!\
				xcopy /Q /Y !SRC_DIST_DIR!\lib\*.lib !DST_DIST_DIR!\lib!BITSTR!\
				xcopy /Q /Y !SRC_DIST_DIR!\lib\*.pdb !DST_DIST_DIR!\lib!BITSTR!\
				xcopy /Q /Y /E /I !SRC_DIST_DIR!\include !DST_DIST_DIR!\include!BITSTR!
				xcopy /Q /Y /E /I !SRC_DIST_DIR!\ssl !DST_DIST_DIR!\ssl
				xcopy /Q /Y /E /I !SRC_DIST_DIR!\html !DST_DIST_DIR!\html
				xcopy /Q /Y /E /I !SRC_DIST_DIR!\logs !DST_DIST_DIR!\logs
				
			)
			
		)
	)
)

echo Copied all files for: !BUILD_PROJECT! v!PROJECT_VERSION!

set README=!DST_DIST_DIR!\readme.precompiled.txt
echo !README!

pushd !PROJECT_INSTALL_DIR!

	SETLOCAL EnableExtensions EnableDelayedExpansion

	SET PATH=!CYGWIN_DIR!\bin;!CYGWIN_DIR!\usr\bin;!PATH!

	echo. > !README!
	bash -c "!DATE_CMD! +\"!DATE_CMD_OPTIONS!\"" >> !README!
	echo ====================================================================================================================== >> !README!	
	echo  url: http://www.npcglib.org/~stathis/blog/precompiled-openssl >> !README!	
	echo ====================================================================================================================== >> !README!
	echo These are custom pre-built OpenSSL Libraries v!PROJECT_VERSION! (http://www.openssl.org). >> !README!
	echo They are compiled with Cygwin/MSVC for 32/64-bit Windows, using Visual Studio !VS_VERSION!. >> !README!
	echo. >> !README!
	echo Please note that the OpenSSL Project (http://www.openssl.org) is the only official source of OpenSSL. >> !README!
	echo These builds are created for my own personal use and therefore you are utilizing them at your own risk. >> !README!
	echo My builds are unsupported and not endorsed by The OpenSSL Project. >> !README!
	echo. >> !README!
	echo I build these in the context of my own work and spare time,  >> !README!
	echo I do NOT charge any money, I do NOT make any money ... and NO I do NOT accept any donations^^! >> !README!
	echo If you really like OpenSSL, if it has helped you or your company in any way, >> !README!
	echo or you are feeling like giving back anyway, then please  >> !README!
	echo donate directly to the OpenSSL Project: https://www.openssl.org/support/donations.html >> !README!
	echo The developers and countless contributors deserve it^^!  >> !README!
	echo. >> !README!
	echo ------------------------------------------------------------------------------ >> !README!
	echo 32-bit OpenSSL Libraries [shared] [runtime: dynamic (/MD)]]>> !README!
	echo ------------------------------------------------------------------------------ >> !README!
	echo release runtime dlls: bin\libcryptoMD.dll bin\libsslMD.dll >> !README!
	echo  release import libs: lib\libcryptoMD.lib lib\libsslMD.lib >> !README!	
	echo   debug runtime dlls: bin\libcryptoMDd.dll bin\libsslMDd.dll >> !README!
	echo    debug import libs: lib\libcryptoMDd.lib lib\libsslMDd.lib >> !README!
	echo. >> !README!
	echo ------------------------------------------------------------------------------ >> !README!
	echo 32-bit OpenSSL Libraries [static] [runtime: static (/MT)]]>> !README!
	echo ------------------------------------------------------------------------------ >> !README!
	echo         release libs: lib\libcryptoMT.lib lib\libsslMT.lib >> !README!	
	echo           debug libs: lib\libcryptoMTd.lib lib\libsslMTd.lib >> !README!	
	echo. >> !README!
	echo ------------------------------------------------------------------------------ >> !README!
	echo 64-bit OpenSSL Libraries [shared] [runtime: dynamic (/MD)]]>> !README!
	echo ------------------------------------------------------------------------------ >> !README!
	echo release runtime dlls: bin64\libcryptoMD.dll bin64\libsslMD.dll >> !README!
	echo  release import libs: lib64\libcryptoMD.lib lib64\libsslMD.lib >> !README!	
	echo   debug runtime dlls: bin64\libcryptoMDd.dll bin64\libsslMDd.dll >> !README!
	echo    debug import libs: lib64\libcryptoMDd.lib lib64\libsslMDd.lib >> !README!
	echo. >> !README!
	echo ------------------------------------------------------------------------------ >> !README!
	echo 64-bit OpenSSL Libraries [static] [runtime: static (/MT)]]>> !README!
	echo ------------------------------------------------------------------------------ >> !README!
	echo         release libs: lib64\libcryptoMT.lib lib64\libsslMT.lib >> !README!	
	echo           debug libs: lib64\libcryptoMTd.lib lib64\libsslMTd.lib >> !README!	
	echo. >> !README!
	echo ====================================================================================================================== >> !README!
	echo. >> !README!
	echo If you have any comments or problems send me an email at: >> !README!
	echo stathis ^<stathis@npcglib.org^> >> !README!

	bash -c "cp -f \"!PROJECT_SRC_DIR!\AUTHORS\" \"!DST_DIST_DIR!\AUTHORS.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\ACKNOWLEDGEMENTS\" \"!DST_DIST_DIR!\ACKNOWLEDGEMENTS.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\CHANGES\" \"!DST_DIST_DIR!\CHANGES.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\CONTRIBUTING\" \"!DST_DIST_DIR!\CONTRIBUTING.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\README\" \"!DST_DIST_DIR!\README.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\README.ECC\" \"!DST_DIST_DIR!\README.ECC.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\FAQ\" \"!DST_DIST_DIR!\FAQ.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\NEWS\" \"!DST_DIST_DIR!\NEWS.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\NOTES.WIN\" \"!DST_DIST_DIR!\NOTES.WIN.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\LICENSE\" \"!DST_DIST_DIR!\LICENSE.txt\""
	bash -c "cp -f \"!PROJECT_SRC_DIR!\FAQ\" \"!DST_DIST_DIR!\FAQ.txt\""
	
	set __FILENAME=!DST_DIST!

	set COMPRESSED_FILE=!__FILENAME!.7z

	echo.
	echo Packaging !BUILD_PROJECT! Library [v!PROJECT_VERSION!]
	echo ----------------------------------------------------------------------------
	echo [     Build in: !PROJECT_BUILD_DIR!] 
	echo [ Installation: !PROJECT_INSTALL_DIR!] 
	echo [    Packaging: !PROJECT_INSTALL_DIR!]
	echo [   Compressed: !COMPRESSED_FILE!]
	echo [       Readme: !README!]
	echo ----------------------------------------------------------------------------
	echo.

	echo Compressing with: !__SEVENZIP_CMD! !SEVENZIP_CMD_OPTIONS! !COMPRESSED_FILE! !DST_DIST!
	bash -c "!__SEVENZIP_CMD! !SEVENZIP_CMD_OPTIONS! !COMPRESSED_FILE! !DST_DIST!" 

	echo Compressing in: !COMPRESSED_FILE!

	IF EXIST !COMPRESSED_FILE! (
		
		for %%I in (!COMPRESSED_FILE!) do (
			SET /A _fsize=%%~zI / 1024 / 1024
		)
		
		!MD5SUM_CMD! !COMPRESSED_FILE! 1> !__FILENAME!.md5
		
		echo Generated md5sum !__FILENAME!.md5 [!_fsize!MB]

	)

	ENDLOCAL

popd

goto :eof

rem ========================================================================================================

:buildall

IF NOT EXIST "!PERL_ROOT!\perlenv.bat" (
	ECHO.
	call :exitB "Make sure !PERL_ROOT! points to a valid Perl root directory. (perlenv.bat is missing)"
	goto :eof
)

call !PERL_ROOT!\perlenv.bat

for %%a in (x86 x64) do (
	for %%l in (shared static) do (
		for %%b in (debug release) do (
			call :build %%a %%l %%b
		)
	)
)

goto :eof

rem ========================================================================================================

:: call :build <x86|x64> <static|shared> <debug|release>
:build
SET __ARCH=%~1
SET __LINK=%~2
SET __BUILD=%~3

if /i "!__ARCH!" == "x86" (
	SET BITS=32
	SET BIT_STR=
) else (
	SET BITS=64
	SET BIT_STR=64
)


IF NOT EXIST "!PERL_ROOT!\perlenv.bat" (
	ECHO.
	call :exitB "Make sure !PERL_ROOT! points to a valid Perl root directory. (perlenv.bat is missing)"
	goto :eof
)

call !PERL_ROOT!\perlenv.bat

echo:
echo Building OpenSSL Library [!__ARCH!] [!__LINK!] [!__BUILD!]
echo:

SETLOCAL EnableExtensions EnableDelayedExpansion

	call "!VISUAL_STUDIO_VC!\vcvarsall.bat" !__ARCH!
	
	rem Place the linker and compiler of Visual Studio infront of any other binaries when searching
	rem SET PATH=!PATH!;!CYGWIN_DIR!\bin;!CYGWIN_DIR!\usr\bin;
	
	call :printConfiguration
	call :buildtype !__ARCH! !__LINK! !__BUILD!
	
ENDLOCAL
goto :eof


rem ========================================================================================================

:: call :build <x86|x64> <static|shared> <debug|release>
:buildtype
SET __ARCH=%~1
SET __LINK=%~2
SET __BUILD=%~3

SET CYGWIN=nodosfilewarning

if /i "!__ARCH!" == "x86" (
	SET BITS=32
	SET BIT_STR=
) else (
	SET BITS=64
	SET BIT_STR=64
)

IF NOT EXIST "!PROJECT_BUILD_DIR!" (
	mkdir "!PROJECT_BUILD_DIR!"
)


SET RUNTIME_SUFFIX=
if /i "!__LINK!" == "shared" (
	SET RUNTIME_SUFFIX=MD
)

if /i "!__LINK!" == "static" (
	SET RUNTIME_SUFFIX=MT
)

SET LIBSUFFIX=
if /i "!__BUILD!" == "debug" (
	SET LIBSUFFIX=d
)

SET RUNTIME_FULL_SUFFIX=!RUNTIME_SUFFIX!!LIBSUFFIX!

SET DLL_STR=
if /i "!__LINK!" == "shared" (
	SET DLL_STR=dll
)
	
SET INSTALL_DIR=!PROJECT_INSTALL_DIR!\!BUILD_PROJECT!-!__ARCH!-!__LINK!-!__BUILD!-vs!VS_VERSION!


SET B_CMD=perl !PROJECT_SRC_DIR!\Configure
SET COMMON_OPTIONS=enable-static-engine --prefix=!INSTALL_DIR! --openssldir=./ssl
SET MODE=VC-WIN


if /i "!__LINK!" == "shared" (
	SET COMMON_OPTIONS=!COMMON_OPTIONS! shared
)

if /i "!__LINK!" == "static" (
	SET COMMON_OPTIONS=!COMMON_OPTIONS! no-shared -static
)


if /i "!__BUILD!" == "debug" (
	SET MODE=!__BUILD!-!MODE!
)

if /i "!__ARCH!" == "x86" (
	SET MODE=!MODE!!BITS!
	SET COMMON_OPTIONS=!COMMON_OPTIONS! no-asm
) else (
	SET MODE=!MODE!!BITS!A
	SET COMMON_OPTIONS=!COMMON_OPTIONS! no-asm
)

SET BUILD_DIR=!PROJECT_BUILD_DIR!\!BUILD_PROJECT!-!__ARCH!-!__LINK!-!__BUILD!-vs!VS_VERSION!

IF NOT EXIST "!BUILD_DIR!" (
	mkdir "!BUILD_DIR!"
)

SET CONFIG_LOG_FILE=!BUILD_DIR!\!BUILD_PROJECT!-!__ARCH!-!__LINK!-!__BUILD!-vs!VS_VERSION!.config.log
SET BUILD_LOG_FILE=!BUILD_DIR!\!BUILD_PROJECT!-!__ARCH!-!__LINK!-!__BUILD!-vs!VS_VERSION!.build.log
SET TEST_LOG_FILE=!BUILD_DIR!\!BUILD_PROJECT!-!__ARCH!-!__LINK!-!__BUILD!-vs!VS_VERSION!.test.log
SET INSTALL_LOG_FILE=!BUILD_DIR!\!BUILD_PROJECT!-!__ARCH!-!__LINK!-!__BUILD!-vs!VS_VERSION!.install.log

ECHO. > !CONFIG_LOG_FILE!

SET B_CMD=!B_CMD! !MODE! !COMMON_OPTIONS! 

echo Commands: !B_CMD!

timeout /t 10

rem pushd !PROJECT_SRC_DIR!
pushd !BUILD_DIR!
echo Configured with: !B_CMD! > !CONFIG_LOG_FILE! 2>&1
!B_CMD! >> !CONFIG_LOG_FILE! 2>&1

SET MK_CMD=nmake

ECHO. > !BUILD_LOG_FILE!

!MK_CMD! > !BUILD_LOG_FILE! 2>&1
rem !MK_CMD! list-tests > !TEST_LOG_FILE! 2>&1
!MK_CMD! test >> !TEST_LOG_FILE! 2>&1

IF NOT EXIST "!INSTALL_DIR!" (
	mkdir "!INSTALL_DIR!"
)
 
rem !MK_CMD! DESTDIR=!INSTALL_DIR! install >> !INSTALL_LOG_FILE! 2>&1
!MK_CMD! install_sw >> !INSTALL_LOG_FILE! 2>&1

rem Install the OpenSSL configuration dir (./ssl)
!MK_CMD! install_ssldirs >> !INSTALL_LOG_FILE! 2>&1

rem Install the OpenSSL documentation dir (./html)
!MK_CMD! install_html_docs >> !INSTALL_LOG_FILE! 2>&1


IF NOT EXIST "!INSTALL_DIR!\logs" (
	mkdir "!INSTALL_DIR!\logs"
)

xcopy /Q /Y !CONFIG_LOG_FILE! !INSTALL_DIR!\logs\ >> !INSTALL_LOG_FILE! 2>&1
xcopy /Q /Y !BUILD_LOG_FILE! !INSTALL_DIR!\logs\ >> !INSTALL_LOG_FILE! 2>&1
xcopy /Q /Y !TEST_LOG_FILE! !INSTALL_DIR!\logs\ >> !INSTALL_LOG_FILE! 2>&1
xcopy /Q /Y !INSTALL_LOG_FILE! !INSTALL_DIR!\logs\ >> !INSTALL_LOG_FILE! 2>&1

popd

goto :eof

rem ========================================================================================================

:toLower str -- converts uppercase character to lowercase
::           -- str [in,out] - valref of string variable to be converted
:$created 20060101 :$changed 20080219 :$categories StringManipulation
:$source http://www.dostips.com
if not defined %~1 EXIT /b
for %%a in ("A=a" "B=b" "C=c" "D=d" "E=e" "F=f" "G=g" "H=h" "I=i"
            "J=j" "K=k" "L=l" "M=m" "N=n" "O=o" "P=p" "Q=q" "R=r"
            "S=s" "T=t" "U=u" "V=v" "W=w" "X=x" "Y=y" "Z=z" "Ä=ä"
            "Ö=ö" "Ü=ü") do (
    call set %~1=%%%~1:%%~a%%
)
EXIT /b

rem ========================================================================================================

:: %1 an error message
:exitB
echo:
echo Error: %1
echo:
echo Contact stathis@npcglib.org
@exit /B 0

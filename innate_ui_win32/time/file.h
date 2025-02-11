#pragma once


typedef unsigned int (WINAPI* GetFinalPathNameByHandleDef)(
	HANDLE hFile,
	LPWSTR lpszFilePath,
	unsigned int cchFilePath,
	unsigned int dwFlags	);



#ifdef __cplusplus


bool GetDrive(const char * lpDeviceFileName, string & fsFileName, bool bDriveLetterOnly );


#endif


int_bool StopAndUninstallDrv( HANDLE hDrvHandle );

HANDLE ExtractAndInstallDrv();

int ftruncate(int file, filesize len);




//CLASS_DECL_ACME int_bool ensure_file_size_handle(HANDLE h, unsigned long long iSize);
//CLASS_DECL_ACME int_bool get_filetime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime);

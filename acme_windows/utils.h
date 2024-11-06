#pragma once





CLASS_DECL_ACME int_bool IsWow64();


int_bool EnableTokenPrivilege(LPCTSTR pszPrivilege);


#define IOCTL_LISTDRV_BUFFERED_IO		\
        CTL_CODE(FILE_DEVICE_UNKNOWN,	\
        0x802,							\
        METHOD_BUFFERED,	            \
        FILE_READ_DATA | FILE_WRITE_DATA)

#define VISTA_FILETYPE  25
#define XP_FILETYPE 28

typedef struct _HANDLE_INFO
{	
	
   USHORT tcDeviceName[260];
	USHORT tcFileName[260];
   ULONG uType;

} HANDLE_INFO;

typedef struct _ADDRESS_INFO
{
   PVOID pAddress;
} ADDRESS_INFO;


#ifndef WINDOWS_DESKTOP
typedef int NTSTATUS;
#endif


typedef struct _SYSTEM_HANDLE
{
   
   unsigned int       dwProcessId;
   unsigned char		      bObjectType;
   unsigned char		      bFlags;
   unsigned short		      wValue;
   PVOID          pAddress;
   unsigned int       GrantedAccess;

}SYSTEM_HANDLE;




// 
// typedef enum OF_FILE_INFO_BY_HANDLE_CLASS
// {
// 	OF_FileNameInfo  = 2,
// 	OF_FileStreamInfo = 7
// };
// 
// struct OF_FILE_NAME_INFO
// {
// 	unsigned int  FileNameLength;
// 	WCHAR FileName[MAX_PATH];
// };
// 
// struct OF_FILE_STREAM_INFO
// {  
// 	unsigned int NextEntryOffset;
// 	unsigned int StreamNameLength;
// 	LARGE_INTEGER StreamSize;
// 	LARGE_INTEGER StreamAllocationSize; 
// 	WCHAR StreamName[MAX_PATH];
// };
// 
// 
// typedef bool (WINAPI *PGetFileInformationByHandleEx)(
// 	HANDLE hFile,
// 	OF_FILE_INFO_BY_HANDLE_CLASS FileInformationClass,
// 	LPVOID pFileInformation,

// 	unsigned int dwBufferSize);





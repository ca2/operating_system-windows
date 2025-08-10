#pragma once


/**
* @ ProcessEnvReader.cpp - Implementation File for CProcessEnvReader class
* @ Author - Sarath C
**/

#pragma once

#include <tlhelp32.h>
#include <Winternl.h>

// macro do safe cleanp wtih specified function with matter
inline void SAFE_ICON_CLEANUP(HICON hIcon)
{
   if(hIcon)
      DestroyIcon(hIcon);
}

// macro do safe cleanp wtih specified function with matter
inline void SAFE_ARRAY_CLEANUP(void* pData)
{
   if(pData)
      free(pData);
}

/**
* Structure to hold the environment string block and it's size
**/
struct _ENVSTRING_t
{
   const ::wide_character * pData;
   int nSize;

   _ENVSTRING_t() // Ctor of structure
   {
      pData = 0; nSize = 0;
   }

   ~_ENVSTRING_t() // Ctor of structure
   {
      Clear();
   }
   void Clear() // dtor of structure
   {
      if(pData)
      {
         delete[] pData;
         pData = 0;
      }
      nSize = 0;
   }
};

// enumeration to specify the destinaton of copying while export data
enum COPY_DEST_e { DEST_CLIPBRD,DEST_FILE };

// arrays and other definitions used to process strings
typedef array<PROCESSENTRY32> ProcessInfoArray;
typedef ::pair<string,string> EnvVariableValuePair;
typedef array<EnvVariableValuePair> EnvVarValArray;

/**
* Class provides interfaces to read process information and other misc services
**/
class CLASS_DECL_ACME CProcessEnvReader
{
public:
   // Wrapper to call NtQueryInformationProcess using Run-time dynamic linking
   static NTSTATUS QueryInformationProcesss(IN HANDLE ProcessHandle,
      IN PROCESSINFOCLASS ProcessInformationClass,
      OUT PVOID ProcessInformation,
      IN ULONG ProcessInformationLength,
      OUT PULONG ReturnLength OPTIONAL);

   /* Process helper functions */
   static BOOL ReadEnvironmentBlock(HANDLE hProcess,_ENVSTRING_t& stEnvData);
   static HANDLE OpenProcessToRead(unsigned int dwPID);
   static void ReleaseHandle(HANDLE hHandle);
   static BOOL HasReadAccess(HANDLE hProcess,void* pAddress,int& nSize);
   static void EnumProcessInfo(ProcessInfoArray& arrProcessInfo);
   static string GetProcessNameFromHandle(HANDLE hProcess);
   static string GetProcessNameFromID(unsigned int dwPID);

   /* GDI helper functions */
   static void LoadIconFromProcess(HANDLE hProcess,HICON& hIconSmall,HICON& hIconLarge);

   /* String helper functions */
   static void ConvertUnicodeToMBCS(const ::wide_character * pStringToConvert,int nLen,string& csMBCSStr);

   static void ParseEnvironmentStrings(const ::wide_character * pStringToConvert,int nLen,string_array_base& EnvStrArr);

   static void SeparateVariablesAndValues(const string_array_base& EnvStrArray,EnvVarValArray& varValArr);

   /* Export functions */
   //   static void ExportEnvStrings(const string_array_base& csArrEnvStr,COPY_DEST_e Dest,HWND hClipboardOwner);
   static void UpdateProcessMiscInfo(HANDLE hProcess,int nItemSelected);
};




#include "framework.h"
#include "process.h"
#include "acme/exception/exception.h"
#include "acme/prototype/prototype/payload.h"


#include "acme/_operating_system.h"


#include <ShellApi.h>
#include <Wtsapi32.h>
#include <Userenv.h>
#include <PSapi.h>


//typedef struct _PROCESS_BASIC_INFORMATION64
//{
//   unsigned long long  Reserved1;
//   unsigned long long  PebBaseAddress;
//   unsigned long long  Reserved2[2];
//   unsigned long long  UniqueProcessId;
//   unsigned long long  Reserved3;
//} PROCESS_BASIC_INFORMATION64;

//typedef NTSTATUS(NTAPI *_NtQueryInformationProcess)(HANDLE ProcessHandle, unsigned int ProcessInformationClass, PVOID ProcessInformation, unsigned int ProcessInformationLength, PDWORD ReturnLength);
//
//PPEB GetPebAddress(HANDLE handleProcess);
//
//CLASS_DECL_ACME string get_command_line(HANDLE handleProcess)
//{
//
//   PPEB ppeb = GetPebAddress(handleProcess);
//
//   PRTL_USER_PROCESS_PARAMETERS pparam1 = nullptr;
//
//   if (!ReadProcessMemory(handleProcess, (PCHAR)&ppeb->ProcessParameters, &pparam1, sizeof(PRTL_USER_PROCESS_PARAMETERS), nullptr) || pparam1 == nullptr)
//   {
//      ::output_debug_string("Could not read the address of ProcessParameters!\n");
//      return "";
//   }
//
//
//   _UNICODE_STRING ustrCommandLine;
//
//   if (!ReadProcessMemory(handleProcess, (PCHAR)&pparam1->CommandLine, &ustrCommandLine, sizeof(ustrCommandLine), nullptr))
//   {
//      ::output_debug_string("Could not read CommandLine!\n");
//      return "";
//   }
//
//   /* allocate memory to hold the command line */
//   WCHAR * commandLineContents = (WCHAR *)::heap::management::memory(::heap::e_memory_main)->allocate(ustrCommandLine.Length + sizeof(WCHAR));
//   /* read the command line */
//   if (!ReadProcessMemory(handleProcess, ustrCommandLine.Buffer, commandLineContents, ustrCommandLine.Length, nullptr))
//   {
//      ::output_debug_string("Could not read the command line string!\n");
//      return "";
//   }
//   commandLineContents[ustrCommandLine.Length / sizeof(WCHAR)] = L'\0';
//   string str = unicode_to_utf8(commandLineContents);
//   memory_free_debug(commandLineContents, 0);
//   return str;
//}






//string get_last_error_message(unsigned int NTStatusMessage);
//
//PPEB GetPebAddress(HANDLE handleProcess)
//{
//   _NtQueryInformationProcess NtQueryInformationProcess = (_NtQueryInformationProcess)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtQueryInformationProcess");
//   PROCESS_BASIC_INFORMATION pbi;
//   memory_set(&pbi, 0, sizeof(pbi));
//   DWORD dwInLen = sizeof(pbi);
//   DWORD dwOutLen = 0xffffffff;
//   unsigned int dwStatus = NtQueryInformationProcess(handleProcess, ProcessBasicInformation, &pbi, dwInLen, &dwOutLen);
//   string strError = get_last_error_message(dwStatus);
//   if ((dwStatus & 3) == 3)
//   {
//      return nullptr;
//   }
//   return pbi.PebBaseAddress;
//}


//string get_last_error_message(unsigned int NTStatusMessage)
//{
//
//   return get_last_error_message(NTStatusMessage);
//
//}




namespace acme
{



} // namespace acme




#include "framework.h"
//#include "acme/operating_system.h"
//
//
//#include <io.h>
//#include <fcntl.h>
//
//
//
//
//int ansi_open(const scoped_string & str,int i)
//{
//   return _wopen(utf8_to_unicode(psz),i);
//}
//
//void ansi_get_errno(int * perrno)
//{
//   *perrno = errno;
//}
//
//
//FILE * ansi_fopen(const scoped_string & str,const scoped_string & strMode)
//{
//   return _wfopen(utf8_to_unicode(psz),utf8_to_unicode(pszMode));
//}
//
//
//
//int ansi_file_flag(int iFlag)
//{
//
//   int i = 0;
//
//   if(iFlag & ::file::e_open_binary)
//   {
//
//      i |= _O_BINARY;
//
//   }
//
//   if(iFlag & ::file::e_open_read)
//   {
//
//      if(iFlag & ::file::e_open_write)
//      {
//
//         i |= _O_RDWR;
//
//      }
//      else
//      {
//
//         i |= _O_RDONLY;
//
//      }
//
//   }
//   else if(iFlag & ::file::e_open_write)
//   {
//
//      i |= _O_WRONLY;
//
//   }
//
//   return i;
//
//}
//
//void ansi_unlink(const scoped_string & str)
//{
//
//   _unlink(psz);
//
//}
//
//
//
//
//
//
//
//



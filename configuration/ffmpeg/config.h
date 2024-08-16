#pragma once


/* #define FF_API_AVIO_WRITE_NONCONST 1 */

#ifdef DEBIAN_LINUX
//#error "debian check"
#define AVIO_FILE_WRITE_TYPE uint8_t
#else
//#error "non debian check"
#define AVIO_FILE_WRITE_TYPE const uint8_t
#endif

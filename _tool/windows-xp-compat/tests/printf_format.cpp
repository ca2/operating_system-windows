#include "acme/operating_system/windows/printf_format.h"
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cwchar>
#include <limits>
#include <string>

static void check(bool value)
{
   if (!value) { std::fputs("printf compatibility regression\n", stderr); std::exit(1); }
}

static std::string narrow(const char *format, ...)
{
   va_list args, count;
   va_start(args, format);
   va_copy(count, args);
   int length = _vscprintf(CA2_PRINTF_FORMAT(format), count);
   va_end(count);
   check(length >= 0);
   std::string buffer(length + 1, '\0');
   check(vsprintf_s(&buffer[0], buffer.size(), CA2_PRINTF_FORMAT(format), args) == length);
   va_end(args);
   buffer.resize(length);
   return buffer;
}

static std::wstring wide(const wchar_t *format, ...)
{
   va_list args, count;
   va_start(args, format);
   va_copy(count, args);
   int length = _vscwprintf(CA2_PRINTF_FORMAT(format), count);
   va_end(count);
   check(length >= 0);
   std::wstring buffer(length + 1, L'\0');
   check(_vsnwprintf(&buffer[0], buffer.size(), CA2_PRINTF_FORMAT(format), args) == length);
   va_end(args);
   buffer.resize(length);
   return buffer;
}

int main()
{
#if defined(__MINGW32__) && !defined(__REACTOS__)
   // This toolchain targets MSVCRT even on a new host. The native build here
   // checks passthrough; exercise the modern CRT formatting tests with MSVC.
   check(std::strcmp(CA2_PRINTF_FORMAT("%lld %zu"), "%lld %zu") == 0);
   std::puts("non-XP format passthrough passed");
   return 0;
#endif
#if defined(__REACTOS__)
   check(ca2_xp::printf_format("%%lld %08llX %*.*lld %jd %zu %td %I64d %ls %") ==
      (sizeof(void *) == 4 ? "%%lld %08I64X %*.*I64d %I64d %u %d %I64d %ls %" :
                             "%%lld %08I64X %*.*I64d %I64d %I64u %I64d %I64d %ls %"));
   check(ca2_xp::printf_format(L"%% %lld %s %S %ls") == L"%% %I64d %s %S %ls");
   check(ca2_xp::printf_format("%") == "%");
   check(ca2_xp::printf_format("%ll") == "%ll");
#endif
   // Reproduce the weather exception: a negative i64 followed by a string.
   check(narrow("status=(%lld) error=%s", -2147479646LL, "badPath") ==
      "status=(-2147479646) error=badPath");
   check(narrow("%lld %llu %016llX %s", (std::numeric_limits<long long>::min)(),
      (std::numeric_limits<unsigned long long>::max)(), 0x123456789abcdef0ULL, "tail") ==
      "-9223372036854775808 18446744073709551615 123456789ABCDEF0 tail");
   check(narrow("%zu %td %jd %s", std::size_t(123), std::ptrdiff_t(-7), std::intmax_t(-8), "tail") ==
      "123 -7 -8 tail");
   check(narrow("%%lld %*.*lld %s", 8, 4, 42LL, "tail") == "%lld     0042 tail");
   check(wide(L"%lld %zu %td %s %S", -2147479646LL, std::size_t(123), std::ptrdiff_t(-7),
      L"wide", "narrow") == L"-2147479646 123 -7 wide narrow");
   std::puts("printf compatibility tests passed");
}

#include <cstdio>
#include <cstring>
#include "../../../../../port/ffmpeg-xp-compat.h"

static int fail(const char *message)
{
    std::fprintf(stderr, "%s\n", message);
    return 1;
}

int main()
{
    char output[16]{};
    const wchar_t valid[] = {L'A', 0xd83d, 0xde00, 0};
    const char expected[] = {'A', '\xf0', '\x9f', '\x98', '\x80', 0};
    if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, valid, -1,
        output, sizeof(output), nullptr, nullptr) != 6
        || std::memcmp(output, expected, sizeof(expected)))
        return fail("Valid surrogate pair was not preserved");
    if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, valid, 3,
        nullptr, 0, nullptr, nullptr) != 5)
        return fail("Length query failed");
    const wchar_t invalid[][3] = {{0xd800, 0, 0}, {0xdc00, 0, 0}, {0xd800, L'A', 0}};
    for (const auto &text : invalid)
    {
        SetLastError(0);
        if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, text, -1,
            output, sizeof(output), nullptr, nullptr) != 0
            || GetLastError() != ERROR_NO_UNICODE_TRANSLATION)
            return fail("Invalid UTF-16 was accepted");
    }
    SetLastError(0);
    if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, valid, 2,
        output, sizeof(output), nullptr, nullptr) != 0
        || GetLastError() != ERROR_NO_UNICODE_TRANSLATION)
        return fail("Truncated surrogate pair was accepted");
    if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, valid, -1,
        output, 1, nullptr, nullptr) != 0 || GetLastError() != ERROR_INSUFFICIENT_BUFFER)
        return fail("Buffer error was not preserved");
    std::puts("FFmpeg XP UTF-8 adapter: PASS");
    return 0;
}

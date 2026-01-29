// detect_arch.c
// Prints: arm64 | x64 | x86 | unknown

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

int main(void)
{
    SYSTEM_INFO si;
    ZeroMemory(&si, sizeof(si));

    // IMPORTANT: this returns the *native* system architecture
    GetNativeSystemInfo(&si);

    switch (si.wProcessorArchitecture)
    {
    case PROCESSOR_ARCHITECTURE_ARM64:
        puts("arm64");
        break;

    case PROCESSOR_ARCHITECTURE_AMD64:
        puts("x64");
        break;

    case PROCESSOR_ARCHITECTURE_INTEL:
        puts("x86");
        break;

    default:
        puts("unknown");
        break;
    }

    return 0;
}

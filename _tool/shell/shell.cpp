#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <filesystem>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

static bool is_file(const fs::path& path)
{
    std::error_code error;
    return fs::is_regular_file(path, error);
}

static fs::path find_project_root()
{
    wchar_t filename[32768];
    const DWORD length = GetModuleFileNameW(nullptr, filename, ARRAYSIZE(filename));
    if (!length || length == ARRAYSIZE(filename))
        return {};

    auto directory = fs::path(filename).parent_path();
    while (directory != directory.root_path())
    {
        if (is_file(directory / L"tool" / L"shell"))
            return directory;
        directory = directory.parent_path();
    }
    return {};
}

static fs::path find_git_bash()
{
    constexpr wchar_t key[] = L"SOFTWARE\\GitForWindows";
    constexpr DWORD registry_views[] = {0, RRF_SUBKEY_WOW6464KEY, RRF_SUBKEY_WOW6432KEY};
    wchar_t installation[32768];
    for (const auto hive : {HKEY_CURRENT_USER, HKEY_LOCAL_MACHINE})
    {
        for (const DWORD view : registry_views)
        {
            DWORD size = sizeof(installation);
            if (RegGetValueW(hive, key, L"InstallPath", RRF_RT_REG_SZ | view,
                             nullptr, installation, &size) == ERROR_SUCCESS)
            {
                const auto executable = fs::path(installation) / L"git-bash.exe";
                if (executable.is_absolute() && is_file(executable))
                    return executable;
            }
        }
    }

    for (const auto* variable : {L"ProgramW6432", L"ProgramFiles", L"ProgramFiles(x86)", L"LOCALAPPDATA"})
    {
        const DWORD length = GetEnvironmentVariableW(variable, installation, ARRAYSIZE(installation));
        if (!length || length >= ARRAYSIZE(installation))
            continue;
        fs::path directory(installation);
        if (std::wstring_view(variable) == L"LOCALAPPDATA")
            directory /= L"Programs";
        const auto executable = directory / L"Git" / L"git-bash.exe";
        if (executable.is_absolute() && is_file(executable))
            return executable;
    }
    return {};
}

static int report_error(const wchar_t* message)
{
    MessageBoxW(nullptr, message, L"ca2 Git Bash", MB_OK | MB_ICONERROR);
    return 1;
}

int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    const auto root = find_project_root();
    if (root.empty())
        return report_error(L"Could not find tool/shell. Run shell.exe from the windows-simple checkout.");

    if (!is_file(root / L"operating_system" / L"operating_system-windows" / L"tool" / L"shell"))
        return report_error(L"The Windows tool submodule is missing. Run git submodule update --init --recursive.");

    const auto git_bash = find_git_bash();
    if (git_bash.empty())
        return report_error(L"Could not find git-bash.exe. Install Git for Windows and try again.");

    // Git for Windows forwards the command to Bash in its normal terminal window.
    auto command = L"\"" + git_bash.native() + L"\" --no-cd -c \"exec bash ./tool/shell\"";
    STARTUPINFOW startup{};
    startup.cb = sizeof(startup);
    startup.dwFlags = STARTF_USESHOWWINDOW;
    startup.wShowWindow = SW_SHOWNORMAL;
    PROCESS_INFORMATION process{};
    if (!CreateProcessW(git_bash.c_str(), command.data(), nullptr, nullptr, FALSE, 0,
                        nullptr, root.c_str(), &startup, &process))
    {
        const auto message = L"Could not start Git Bash. Windows error " + std::to_wstring(GetLastError()) + L".";
        return report_error(message.c_str());
    }
    CloseHandle(process.hThread);
    CloseHandle(process.hProcess);
    return 0;
}

#include <windows.h>
#include <process.h>

#include <filesystem>
#include <iostream>
#include <stdexcept>

namespace filesystem = std::filesystem;

namespace
{

class temporary_directory
{
public:
   temporary_directory()
   {
      const auto parent = filesystem::temp_directory_path();
      wchar_t name[MAX_PATH];
      if (!GetTempFileNameW(parent.c_str(), L"ipr", 0, name))
      {
         throw std::runtime_error("Could not reserve a temporary path");
      }

      m_path = name;
      if (!DeleteFileW(name) || !filesystem::create_directory(m_path))
      {
         throw std::runtime_error("Could not create the temporary directory");
      }
   }

   ~temporary_directory()
   {
      std::error_code error;
      filesystem::remove_all(m_path, error);
   }

   const filesystem::path & path() const { return m_path; }

private:
   filesystem::path m_path;
};

filesystem::path project_root()
{
   wchar_t executable[32768];
   const auto length = GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
   if (!length || length == ARRAYSIZE(executable))
   {
      throw std::runtime_error("Could not determine the executable's location");
   }

   const auto directory = filesystem::path(executable).parent_path();
   const auto root = directory.parent_path();
   if (directory.filename() != L"operating_system" || !filesystem::exists(root / L".git"))
   {
      throw std::runtime_error("Place initialize_project_root.exe in the checkout's operating_system directory");
   }

   return root;
}

}

int main()
{
   try
   {
      const auto root = project_root();
      temporary_directory download;
      filesystem::current_path(download.path());

      const auto clone_result = _wspawnlp(_P_WAIT, L"git.exe", L"git.exe", L"clone", L"--depth=1",
         L"--no-checkout", L"--no-recurse-submodules", L"https://github.com/ca2/windows-simple.git",
         L".", static_cast<const wchar_t *>(nullptr));
      const auto checkout_result = clone_result == 0
         ? _wspawnlp(_P_WAIT, L"git.exe", L"git.exe", L"-c", L"core.autocrlf=false", L"checkout",
            L"HEAD", L"--", L"tool/shell", L"shell.exe", static_cast<const wchar_t *>(nullptr))
         : clone_result;
      filesystem::current_path(root);
      if (checkout_result != 0)
      {
         throw std::runtime_error("Could not retrieve the shell files from windows-simple. Check Git for Windows and network access");
      }

      const auto source_script = download.path() / L"tool/shell";
      const auto source_executable = download.path() / L"shell.exe";
      if (!filesystem::is_regular_file(source_script) || !filesystem::is_regular_file(source_executable))
      {
         throw std::runtime_error("The windows-simple checkout did not contain both shell files");
      }

      filesystem::create_directories(root / L"tool");
      filesystem::copy_file(source_script, root / L"tool/shell", filesystem::copy_options::overwrite_existing);
      filesystem::copy_file(source_executable, root / L"shell.exe", filesystem::copy_options::overwrite_existing);
      std::cout << "Copied tool/shell and shell.exe from windows-simple.\n";
      return 0;
   }
   catch (const std::exception & exception)
   {
      std::cerr << "initialize_project_root: " << exception.what() << '\n';
      return 1;
   }
}

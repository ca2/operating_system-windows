#include <cassert>
#include <fstream>
#include <iterator>
#include <string>


namespace
{


   std::string read_file(const char * pszPath)
   {

      std::ifstream stream(pszPath, std::ios::binary);

      return {
         std::istreambuf_iterator<char>(stream),
         std::istreambuf_iterator<char>()};

   }


} // namespace


int main()
{

   const auto header = read_file("operating_system-windows/write_text_win32/font_face_resolver.h");
   const auto source = read_file("operating_system-windows/write_text_win32/font_face_resolver.cpp");
   const auto providerHeader = read_file("operating_system-windows/write_text_win32/write_text.h");
   const auto providerSource = read_file("operating_system-windows/write_text_win32/write_text.cpp");
   const auto project = read_file("operating_system-windows/write_text_win32/write_text_win32.vcxproj");
   const auto cmake = read_file("operating_system-windows/write_text_win32/CMakeLists.txt");

   assert(header.find("class CLASS_DECL_WRITE_TEXT_WIN32 font_face_resolver") != std::string::npos);
   assert(header.find("resolve_substitute_family") != std::string::npos);
   assert(header.find("bool resolve(") != std::string::npos);
   assert(source.find("FontSubstitutes") != std::string::npos);
   assert(source.find("DWriteCreateFactory") != std::string::npos);
   assert(source.find("FindFamilyName") != std::string::npos);
   assert(source.find("GetFirstMatchingFont") != std::string::npos);
   assert(source.find("IDWriteLocalFontFileLoader") != std::string::npos);
   assert(source.find("GetFilePathFromKey") != std::string::npos);
   assert(source.find("GetIndex()") != std::string::npos);
   assert(source.find("FindFamilyName(L\"Arial\"") == std::string::npos);
   assert(providerHeader.find("resolve_font_face(") != std::string::npos);
   assert(providerHeader.find("handle_font_enumeration(") != std::string::npos);
   assert(providerHeader.find("m_mapFontFaceSource") != std::string::npos);
   assert(providerSource.find("resolve_substitute_family") != std::string::npos);
   assert(providerSource.find("::write_text::write_text::resolve_font_face") != std::string::npos);
   assert(providerSource.find("m_mapFontFaceSource.clear()") != std::string::npos);
   assert(project.find("Dwrite.lib") != std::string::npos);
   assert(cmake.find("Dwrite") != std::string::npos);

   return 0;

}

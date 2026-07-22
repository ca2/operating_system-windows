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


   std::string section(
      const std::string & source,
      const std::string & beginMarker,
      const std::string & endMarker)
   {

      const auto begin = source.find(beginMarker);
      const auto end = source.find(endMarker, begin);

      assert(begin != std::string::npos);
      assert(end != std::string::npos);
      assert(begin < end);

      return source.substr(begin, end - begin);

   }


} // namespace


int main()
{

   const auto source = read_file("operating_system-windows/write_text_win32/font_enumeration.cpp");
   const auto enumerate = section(
      source,
      "void font_enumeration::on_enumerate_fonts()",
      "::i32 CALLBACK font_enumeration::OLDFONTENUMPROCW(");

   const auto rasterCapability = enumerate.find("write_text_supports_raster_fonts()");
   const auto disableRaster = enumerate.find("m_bRaster = false", rasterCapability);
   const auto legacyCapability = enumerate.find("write_text_supports_legacy_gdi_fonts()", disableRaster);
   const auto disableOther = enumerate.find("m_bOther = false", legacyCapability);
   const auto enumFonts = enumerate.find("EnumFontFamiliesW", disableOther);

   assert(rasterCapability != std::string::npos);
   assert(disableRaster != std::string::npos);
   assert(legacyCapability != std::string::npos);
   assert(disableOther != std::string::npos);
   assert(enumFonts != std::string::npos);
   assert(rasterCapability < disableRaster);
   assert(disableRaster < legacyCapability);
   assert(legacyCapability < disableOther);
   assert(disableOther < enumFonts);

   return 0;

}

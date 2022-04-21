#include "framework.h"


CLASS_DECL_DRAW2D_GDIPLUS void initialize_gdiplus();
CLASS_DECL_DRAW2D_GDIPLUS void terminate_gdiplus();


namespace draw2d_gdiplus
{


   draw2d::draw2d()
   {
      
      initialize_gdiplus();


   }


   draw2d::~draw2d()
   {

      m_mapPrivateFont.clear();

      terminate_gdiplus();

   }


   void draw2d::initialize(::object * pobject)
   {

      //auto estatus = 
      
      ::draw2d::draw2d::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}
   
      //estatus = 
      
      initialize_gdiplus();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;
   
   }


   string draw2d::write_text_get_default_library_name()
   {

      return "win32";

   }


   draw2d::private_font * draw2d::get_file_private_font(::acme::context * pcontext, const ::file::path & path)
   {

      auto & pfont = m_mapPrivateFont[path];

      if (::is_set(pfont))
      {

         return pfont;

      }

      __construct_new(pfont);

      pfont->m_pcollection = new Gdiplus::PrivateFontCollection();

      auto pmemory = m_psystem->m_paurasystem->draw2d()->write_text()->get_file_memory(pcontext, path);

      if (pmemory->has_data())
      {

         pfont->m_pcollection->AddMemoryFont(pmemory->get_data(), (INT)pmemory->get_size());

         auto & fontCollection = *pfont->m_pcollection;

         auto iFamilyCount = fontCollection.GetFamilyCount();

         pfont->m_pfamily.create_array(iFamilyCount);

         pfont->m_iFamilyCount = 0;

         fontCollection.GetFamilies(iFamilyCount, pfont->m_pfamily, &pfont->m_iFamilyCount);

      }

      return pfont;

   }



} // namespace draw2d_gdiplus




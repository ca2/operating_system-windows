#include "framework.h"
#include "draw2d.h"
#include "acme/primitive/primitive/memory.h"


CLASS_DECL_DRAW2D_GDIPLUS void initialize_gdiplus();
CLASS_DECL_DRAW2D_GDIPLUS void terminate_gdiplus();


namespace draw2d_gdiplus
{


   draw2d::private_font::private_font()
   {


   }


   draw2d::private_font::~private_font()
   {



   }


   draw2d::draw2d()
   {
      
      initialize_gdiplus();


   }


   draw2d::~draw2d()
   {

      m_mapPrivateFont.clear();

      terminate_gdiplus();

   }


   void draw2d::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      ::draw2d::draw2d::initialize(pparticle);

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


   string draw2d::write_text_get_default_implementation_name()
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

      auto pmemory = acmesystem()->m_paurasystem->draw2d()->write_text()->get_file_memory(pcontext, path);

      if (pmemory->has_data())
      {

         pfont->m_pcollection->AddMemoryFont(pmemory->data(), (INT)pmemory->size());

         auto & fontCollection = *pfont->m_pcollection;

         auto iFamilyCount = fontCollection.GetFamilyCount();

         pfont->m_familya.set_size(iFamilyCount);

         fontCollection.GetFamilies(iFamilyCount, pfont->m_familya.data(), &pfont->m_iFamilyCount);

         pfont->m_familya.set_size(iFamilyCount);

         for (int iFamily = 0; iFamily < iFamilyCount; iFamily++)
         {

            if (pfont->m_familya[iFamily].GetLastStatus() != Gdiplus::Ok)
            {

               warning("font family nok");

            }

         }

      }

      return pfont;

   }



} // namespace draw2d_gdiplus




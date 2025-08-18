#include "framework.h"


namespace draw2d_gdi
{


   object::object()
   {

      m_hgdiobj = nullptr;

   }

   object::~object()
   {

      synchronous_lock ml(&draw2d_gdi_mutex());

      for(int i = 0; i < m_ptraGraphics.get_size(); i++)
      {

         try
         {

            m_ptraGraphics[i]->m_ptraObject.erase(this);

         }
         catch(...)
         {

         }

      }

      if(m_hgdiobj != nullptr)
      {

         for(int i = 0; i < m_ptraGraphics.get_size(); i++)
         {

            try
            {

               if(::GetCurrentObject(m_ptraGraphics[i]->get_handle1(), ::GetObjectType(m_hgdiobj)) == m_hgdiobj)
               {

                  GDI_GRAPHICS(m_ptraGraphics[i])->set_original_object(::GetObjectType(m_hgdiobj));

               }

            }
            catch(...)
            {

            }

         }

         bool bOk = ::DeleteObject(m_hgdiobj) != false;

      }

   }


   int object::get_object(int nCount, LPVOID lpObject) const
   {

      return ::GetObjectW(m_hgdiobj, nCount, lpObject);

   }

   bool object::CreateStockObject(int nIndex)
   {

      return (m_hgdiobj = ::GetStockObject(nIndex)) != nullptr;

   }

   bool object::UnrealizeObject()
   {

      ASSERT(get_handle() != nullptr);

      return ::UnrealizeObject(get_handle()) != false;

   }

   UINT object::GetObjectType() const
   {

      return (UINT)::GetObjectType(get_handle());

   }


   ::pointer<::draw2d_gdi::object>graphics_object_allocator(::aura::application * papp, HANDLE h)
   {

      switch(::GetObjectType(h))
      {
      case OBJ_BITMAP:
         return øallocate bitmap(papp);
      case OBJ_REGION:
         return øallocate region(papp);
      case OBJ_PEN:
         return øallocate pen(papp);
      case OBJ_BRUSH:
         return øallocate brush(papp);
      case OBJ_PAL:
         return øallocate palette(papp);
      case OBJ_FONT:
         return øallocate font(papp);
      }

      return nullptr;

   }

   bool object::Attach(HGDIOBJ hObject)
   {

      if (hObject == nullptr)
      {

         return false;

      }

      if(m_hgdiobj != nullptr)
      {

         destroy();

      }

      m_hgdiobj = hObject;

      return true;

   }


   HGDIOBJ object::Detach()
   {

      HGDIOBJ hgdiobj = m_hgdiobj;

      m_hgdiobj = nullptr;

      return hgdiobj;

   }


   bool object::destroy()
   {

      synchronous_lock ml(&draw2d_gdi_mutex());

      for(int i = 0; i < m_ptraGraphics.get_size(); i++)
      {

         try
         {

            ::draw2d_gdi::graphics * pgraphics = m_ptraGraphics[i];

            pgraphics->m_ptraObject.erase(this);

         }
         catch(...)
         {

         }

      }

      if(m_hgdiobj == nullptr)
      {

         m_ptraGraphics.erase_all();

         return true;

      }

      for(int i = 0; i < m_ptraGraphics.get_size(); i++)
      {

         try
         {

            if(::GetCurrentObject(m_ptraGraphics[i]->get_handle1(), ::GetObjectType(m_hgdiobj)) == m_hgdiobj)
            {

               m_ptraGraphics[i]->set_original_object(::GetObjectType(m_hgdiobj));

            }

         }
         catch(...)
         {

         }

      }

      m_ptraGraphics.erase_all();

      bool bOk = ::DeleteObject(m_hgdiobj) != false;

      m_hgdiobj = nullptr;

      return bOk;

   }


   void object::dump(dump_context & dumpcontext) const
   {
      ::object::dump(dumpcontext);

      dumpcontext << "get_handle() = " << get_handle();
      dumpcontext << "\n";
   }

   void object::assert_ok() const
   {
      ::object::assert_ok();
      /*      ASSERT(get_handle() == nullptr ||
               (::windows_definition::Data.bWin95 || ::GetObjectType(get_handle()) != 0));*/
   }

   void * object::detach_os_data()
   {
      return Detach();
   }

   void * object::get_handle() const
   {

      return get_os_data();

   }

   object::operator HGDIOBJ() const
   {

      return this == nullptr ? nullptr : (HGDIOBJ) get_os_data();

   }


   HGDIOBJ object::get_os_data() const
   {

      if(this == nullptr)
         return nullptr;

      defer_update();

      return m_hgdiobj;

   }

   void object::update()
   {

      if(m_hgdiobj != nullptr)
      {

         destroy();

         m_hgdiobj = nullptr;

      }

   }




}  // namespace draw2d_gdi





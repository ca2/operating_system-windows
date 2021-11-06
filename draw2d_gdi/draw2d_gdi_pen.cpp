#include "framework.h"


namespace draw2d_gdi
{


   pen::pen(::object * pobject) :
      ::draw2d::pen(pobject)
   {

   }


   pen::~pen()
   {

   }


   pen::operator HPEN() const
   {

      return (HPEN)(this == nullptr ? nullptr : get_handle());

   }


   bool pen::CreatePen(int nPenStyle, int nWidth, ::color::color crColor)
   {

      return Attach(::CreatePen(nPenStyle, nWidth, crColor));

   }


   bool pen::CreatePenIndirect(LPLOGPEN lpLogPen)
   {

      return Attach(::CreatePenIndirect(lpLogPen));

   }


   bool pen::CreatePen(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount, const u32* lpStyle)
   {

      return Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount, (DWORD *) lpStyle));

   }


   int pen::GetExtLogPen(EXTLOGPEN* pLogPen)
   {

      ASSERT(get_handle() != nullptr);

      return get_object(sizeof(EXTLOGPEN), pLogPen);

   }


   int pen::GetLogPen(LOGPEN* pLogPen)
   {

      if(get_handle() == nullptr)
         return 0;

      return get_object(sizeof(LOGPEN), pLogPen);

   }


   void pen::construct(int nPenStyle, int nWidth, ::color::color crColor)
   {

      if (!Attach(::CreatePen(nPenStyle, nWidth, crColor)))
         throw resource_exception();

   }

   void pen::construct(int nPenStyle, int nWidth, const LOGBRUSH* pLogBrush, int nStyleCount, const u32* lpStyle)
   {

      if (!Attach(::ExtCreatePen(nPenStyle, nWidth, pLogBrush, nStyleCount, (DWORD *) lpStyle)))
         throw resource_exception();

   }



   void pen::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

      if (get_handle() == nullptr)
         return;

      /* if (!afxData.bWin95 && ::GetObjectType(get_handle()) != OBJ_PEN)
       {
          // not a valid object
          dumpcontext << "has ILLEGAL HPEN!";
          return;
       }*/

      LOGPEN lp;
      VERIFY(get_object(sizeof(lp), &lp));
      dumpcontext << "lgpn.lopnStyle = " << lp.lopnStyle;
      dumpcontext << "\nlgpn.lopnWidth.x (width) = " << lp.lopnWidth.x;
      dumpcontext << "\nlgpn.lopnColor = " << (void *)(DWORD_PTR)lp.lopnColor;

      dumpcontext << "\n";
   }


   bool pen::create()
   {

      ::draw2d_gdi::object::create();

      if(m_bProcess)
      {

         CreatePen(PS_SOLID, (i32) m_dWidth, rgb(255, 255, 255));

      }
      else if(m_epen == type_solid)
      {

         CreatePen(PS_SOLID, (i32) m_dWidth, m_color.get_rgb());

      }

      return true;

   }


} // namespace draw2d_gdi




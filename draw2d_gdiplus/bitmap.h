#pragma once


#include "aura/graphics/draw2d/bitmap.h"
#include "acme/primitive/primitive/memory.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS bitmap :
      virtual public ::draw2d::bitmap
   {
   public:


      //__creatable_from_base(bitmap, ::draw2d::bitmap);


      ::Gdiplus::Bitmap *  m_pbitmap;
      memory               m_mem;


      bitmap();
      ~bitmap() override;

//#ifdef DEBUG
//
//      void dump(dump_context & dumpcontext) const override;
//
//#endif

      void destroy() override;

      bool LoadBitmap(const ::string & pszResourceName);

      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_

      bool CreateBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight, UINT nPlanes, UINT nBitcount, const void * pBits, i32 stride);

      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP pBitmap);

      void CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      void CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      virtual void host_bitmap(::draw2d::graphics * pgraphics, const pixmap* ppximap) override;
      virtual void create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, void **ppvBits, int * stride) override;
      virtual void CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, u32 flInit, const void *pjBits, UINT iUsage) override;


      i32 GetBitmap(BITMAP* pBitMap);


      u32 SetBitmapBits(u32 dwCount, const void * pBits);

      u32 GetBitmapBits(u32 dwCount, LPVOID pBits) const;

      ::size_i32 SetBitmapDimension(i32 nWidth, i32 nHeight);
      ::size_i32 GetBitmapDimension() const;


      virtual void attach(void * posdata);
      virtual void * detach();

      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

   };


} // namespace draw2d_gdiplus




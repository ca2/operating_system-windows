#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS bitmap :
      virtual public ::draw2d::bitmap
   {
   public:


      ::Gdiplus::Bitmap *  m_pbitmap;
      memory               m_mem;


      bitmap();
      virtual ~bitmap();

#ifdef DEBUG

      virtual void dump(dump_context & dumpcontext) const;

#endif

      virtual void destroy() override;

      bool LoadBitmap(const char * pszResourceName);

      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_

      bool CreateBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight, UINT nPlanes, UINT nBitcount, const void * pBits, i32 stride);

      bool CreateBitmapIndirect(::draw2d::graphics * pgraphics, LPBITMAP pBitmap);

      bool CreateCompatibleBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      bool CreateDiscardableBitmap(::draw2d::graphics * pgraphics, i32 nWidth, i32 nHeight);
      virtual bool host_bitmap(::draw2d::graphics * pgraphics, const pixmap* ppximap) override;
      virtual bool create_bitmap(::draw2d::graphics * pgraphics, const ::size_i32 & size, void **ppvBits, int * stride) override;
      virtual bool CreateDIBitmap(::draw2d::graphics * pgraphics, int cx, int cy, u32 flInit, const void *pjBits, UINT iUsage) override;


      i32 GetBitmap(BITMAP* pBitMap);


      u32 SetBitmapBits(u32 dwCount, const void * pBits);

      u32 GetBitmapBits(u32 dwCount, LPVOID pBits) const;

      ::size_i32 SetBitmapDimension(i32 nWidth, i32 nHeight);
      ::size_i32 GetBitmapDimension() const;


      virtual bool attach(void * posdata);
      virtual void * detach();

      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

   };


} // namespace draw2d_gdiplus




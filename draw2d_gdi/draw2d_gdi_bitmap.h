#pragma once


namespace draw2d_gdi
{


   class CLASS_DECL_DRAW2D_GDI bitmap :
      virtual public ::draw2d_gdi::object,
      virtual public ::draw2d::bitmap
   {
   public:


      bitmap(::object * pobject);
      virtual ~bitmap();


      operator HBITMAP() const;
      int GetBitmap(BITMAP* pBitMap);


      bool LoadBitmap(const char * lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
      bool CreateBitmap(::draw2d::graphics_pointer & pgraphics, i32 nWidth, i32 nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits, i32 stride);
      bool CreateBitmapIndirect(LPBITMAP lpBitmap);
      bool CreateCompatibleBitmap(::draw2d::graphics_pointer & pgraphics, int nWidth, int nHeight);
      bool CreateDiscardableBitmap(::draw2d::graphics_pointer & pgraphics, int nWidth, int nHeight);
      bool CreateDIBSection(::draw2d::graphics_pointer & pgraphics, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, i32 * stride, HANDLE hSection, u32 offset);
      bool CreateDIBitmap(::draw2d::graphics_pointer & pgraphics, const BITMAPINFOHEADER *pbmih, u32 flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);


      u32 SetBitmapBits(u32 dwCount, const void * lpBits);
      u32 GetBitmapBits(u32 dwCount, LPVOID lpBits) const;
      ::size_i32 SetBitmapDimension(int nWidth, int nHeight);
      ::size_i32 GetBitmapDimension() const;

      virtual void dump(dump_context & dumpcontext) const;


      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

   };


} // namespace draw2d_gdi





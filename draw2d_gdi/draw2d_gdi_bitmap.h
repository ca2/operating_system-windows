#pragma once


namespace draw2d_gdi
{


   class CLASS_DECL_DRAW2D_GDI bitmap :
      virtual public ::draw2d_gdi::object,
      virtual public ::draw2d::bitmap
   {
   public:


      bitmap(::particle * pparticle);
      virtual ~bitmap();


      operator HBITMAP() const;
      int GetBitmap(BITMAP* pBitMap);


      bool LoadBitmap(const ::string & lpszResourceName);
      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_
      bool CreateBitmap(::draw2d::graphics_pointer & pgraphics, int nWidth, int nHeight, UINT nPlanes, UINT nBitcount, const void * lpBits, int stride);
      bool CreateBitmapIndirect(LPBITMAP lpBitmap);
      bool CreateCompatibleBitmap(::draw2d::graphics_pointer & pgraphics, int nWidth, int nHeight);
      bool CreateDiscardableBitmap(::draw2d::graphics_pointer & pgraphics, int nWidth, int nHeight);
      bool CreateDIBSection(::draw2d::graphics_pointer & pgraphics, const BITMAPINFO * lpbmi, UINT usage, void **ppvBits, int * stride, HANDLE hSection, unsigned int offset);
      bool CreateDIBitmap(::draw2d::graphics_pointer & pgraphics, const BITMAPINFOHEADER *pbmih, unsigned int flInit, const void *pjBits, const BITMAPINFO *pbmi, UINT iUsage);


      unsigned int SetBitmapBits(unsigned int dwCount, const void * lpBits);
      unsigned int GetBitmapBits(unsigned int dwCount, LPVOID lpBits) const;
      ::size_i32 SetBitmapDimension(int nWidth, int nHeight);
      ::size_i32 GetBitmapDimension() const;

      void dump(dump_context & dumpcontext) const override;


      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);

   };


} // namespace draw2d_gdi





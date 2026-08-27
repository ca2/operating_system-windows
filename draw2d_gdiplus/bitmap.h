#pragma once


#include "aura/graphics/draw2d/bitmap.h"
#include "acme/prototype/prototype/memory.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS bitmap :
      virtual public ::draw2d::bitmap
   {
   public:


      //__creatable_from_base(bitmap, ::draw2d::bitmap);


      ::Gdiplus::Bitmap *  m_pgdiplusbitmap;
      memory               m_mem;
      //::image32_t *         m_pimage32Host;


      bitmap();
      bitmap(bitmap && bitmap);
      ~bitmap() override;

//#ifdef DEBUG
//
//      void dump(dump_context & dumpcontext) const override;
//
//#endif

      void destroy() override;

      bool LoadBitmap(const ::scoped_string & scopedstrResourceName);

      bool LoadBitmap(UINT nIDResource);
      bool LoadOEMBitmap(UINT nIDBitmap); // for OBM_/OCR_/OIC_


      void update_bitmap_as_image_render_target(
         ::image::image * pimage,
         ::acme::user::interaction * pacmeuserinteractionAffinity = nullptr,
         ::draw2d::graphics * pdraw2dgraphics = nullptr) override;
      void preserve_image(const ::i32_size& size, ::image::image* pimage) override;
      bool CreateBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 nWidth, ::i32 nHeight, UINT nPlanes, UINT nBitcount, const void * pBits, ::i32 stride);

      bool CreateBitmapIndirect(::draw2d::graphics * pdraw2dgraphics, LPBITMAP pBitmap);

      void CreateCompatibleBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 nWidth, ::i32 nHeight);
      void CreateDiscardableBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 nWidth, ::i32 nHeight);
      //virtual bool host_bitmap(::draw2d::graphics * pdraw2dgraphics, pixmap_t* ppximap) override;
      void create_bitmap(::draw2d::graphics * pdraw2dgraphics, const ::i32_size & size, ::pixmap * ppixmapOwned) override;
      virtual void CreateDIBitmap(::draw2d::graphics * pdraw2dgraphics, ::i32 cx, ::i32 cy, ::u32 flInit, const void *pjBits, UINT iUsage) override;


      void read_pixels(const ::i32_size & size, const ::i32_point & point, ::image32_t * pimage32, ::i32 iScan) override;
      bool is_cpu_backed_by(const ::pixmap_t * ppixmap) const override;
      void write_pixels(const ::i32_size & size, const ::i32_point & point, const ::image32_t * pimage32, ::i32 iScan) override;



      ::i32 GetBitmap(BITMAP* pBitMap);


      ::u32 SetBitmapBits(::u32 dwCount, const void * pBits);

      ::u32 GetBitmapBits(::u32 dwCount, LPVOID pBits) const;

      ::i32_size SetBitmapDimension(::i32 nWidth, ::i32 nHeight);
      ::i32_size GetBitmapDimension() const;

      ::i32_size size() const override;
      void set_size(const ::i32_size & size, bool bPreserve = true) override;


      virtual void attach(void * posdata);
      virtual void * detach();

      virtual HBITMAP _GetHBITMAP();
      virtual void _ReleaseHBITMAP(HBITMAP hbitmap);


      ::string _001_os_bitmap_diagnostics() override;


   };


} // namespace draw2d_gdiplus




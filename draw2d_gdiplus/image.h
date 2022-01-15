#pragma once


#include "aura/graphics/draw2d/image.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS image :
      virtual public ::image
   {
   public:


      HBITMAP                    m_hbitmap;
      ::size_i64                 m_sizeWnd;
      BITMAPINFO                 m_bitmapinfo;


      image();
      ~image() override;


      void draw2d_gdiplus_image_common_construct();

      virtual ::draw2d::graphics * _get_graphics() const;
      virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();

      
      //using ::image::stretch;
      //virtual bool stretch(::image * pimage) override;


      void dc_select(bool bSelect = true);

      virtual void on_exif_orientation();


      virtual bool _load_thumbnail(const ::string & psz);


      virtual void _map(bool) override;
      virtual void _unmap() override;

      virtual void create_ex(const ::size_i32 & size, ::color32_t * pcolorref, int iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false);
      //void create(const ::size_i32 & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      //void initialize(const ::size_i32 & size, ::color32_t * pcolorref, int iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG) override;
      virtual bool host(const ::pixmap * pixmap) override;
      virtual bool on_host_read_pixels(const ::pixmap* pixmap) override;
      using ::image::create;
      virtual void create(::draw2d::graphics * pgraphics) override;
      void destroy() override;


      //cvirtual bool stretch(::draw2d::graphics * pgraphics) override;
      //virtual bool draw(const ::image * pimage) override;
      virtual void _draw_raw(const ::rectangle_i32 & rectangleTarget, ::image * pimageSrc, const ::point_i32 & pointSrc) override;


      virtual void SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


   };


} // namespace draw2d_gdiplus




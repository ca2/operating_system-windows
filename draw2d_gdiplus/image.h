#pragma once


#include "aura/graphics/image/image.h"


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS image :
      virtual public ::image::image
   {
   public:


      //__creatable_from_base(image, ::image);


      HBITMAP                    m_hbitmap;
      ::i64_size                 m_sizeWnd;
      BITMAPINFO                 m_bitmapinfo;


      image();
      ~image() override;


      void draw2d_gdiplus_image_common_construct();

      virtual ::draw2d::graphics * _get_graphics() const;
      virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();

      
      //using ::image::stretch;
      //virtual bool stretch(::image::image * pimage) override;


      void dc_select(bool bSelect = true);

      virtual void on_exif_orientation();


      virtual bool _load_thumbnail(const ::scoped_string & scopedstr);


      virtual void _map(bool) override;
      virtual void _unmap() override;

      virtual void create_ex(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false);
      //void create(const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false) override;
      //void initialize(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG) override;
      virtual bool host(::pixmap * pixmap, ::windowing::window * pwindow) override;
      bool on_host_read_pixels(::pixmap* pixmap) const override;
      using ::image::image::create;
      virtual void create(::draw2d::graphics * pgraphics) override;
      void destroy() override;


      //cvirtual bool stretch(::draw2d::graphics * pgraphics) override;
      //virtual bool draw(const ::image::image * pimage) override;
      virtual void _draw_raw(const ::i32_rectangle & rectangleTarget, ::image::image * pimageSrc, const ::i32_point & pointSrc) override;


      virtual void SetIconMask(::image::icon * picon, ::i32 cx, ::i32 cy) override;


   };


} // namespace draw2d_gdiplus




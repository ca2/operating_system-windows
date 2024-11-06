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
      ::size_i64                 m_sizeWnd;
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


      virtual bool _load_thumbnail(const ::string & psz);


      virtual void _map(bool) override;
      virtual void _unmap() override;

      virtual void create_ex(const ::size_i32 & size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, int iGoodStride = -1, bool bPreserve = false);
      //void create(const ::size_i32 & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      //void initialize(const ::size_i32 & size, ::image32_t * pimage32, int iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG) override;
      virtual bool host(::pixmap * pixmap) override;
      bool on_host_read_pixels(::pixmap* pixmap) const override;
      using ::image::image::create;
      virtual void create(::draw2d::graphics * pgraphics) override;
      void destroy() override;


      //cvirtual bool stretch(::draw2d::graphics * pgraphics) override;
      //virtual bool draw(const ::image::image * pimage) override;
      virtual void _draw_raw(const ::rectangle_i32 & rectangleTarget, ::image::image * pimageSrc, const ::point_i32 & pointSrc) override;


      virtual void SetIconMask(::image::icon * picon, int cx, int cy) override;


   };


} // namespace draw2d_gdiplus




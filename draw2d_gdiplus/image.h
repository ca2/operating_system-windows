#pragma once


#include "aura/graphics/image/image.h"
#include "aura/graphics/image/image_pixmap_lease.h"


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
      image(image&& image);
      ~image() override;


      void draw2d_gdiplus_image_common_construct();

      //virtual ::draw2d::graphics * _get_graphics() const;
      //virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();

      
      //using ::image::stretch;
      //virtual bool stretch(::image::image * pimage) override;


      //void dc_select(bool bSelect = true);

      //virtual void on_exif_orientation();


      virtual bool _load_thumbnail(const ::scoped_string & scopedstr);


      void update_bitmap_as_render_target(
         ::acme::user::interaction * pacmeuserinteractionAffinity = nullptr, ::draw2d::graphics * pdraw2dgraphics = nullptr) override;

      void create_from_data(const ::pixmap_t & pixmap, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_FLAG, bool bPreserve = false) override;
      //void create(const ::i32_size & size, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, ::i32 iGoodStride = -1, bool bPreserve = false) override;
      //void initialize(const ::i32_size & size, ::image32_t * pimage32, ::i32 iScan, ::enum_flag eflagCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG) override;
      //void update_as_gpu_render_target(const ::i32_size & sizeRaw, ::user::interaction * puserinteraction, ::draw2d::graphics * pdraw2dgraphics, ::enum_flag eflagCreate, ::i32 iGoodStride, bool bPreserve, bool bTopDraw2d) override;
      void update_as_render_target(const ::i32_size & sizeRaw, ::user::interaction * puserinteraction, ::draw2d::graphics * pdraw2dgraphics, ::enum_flag eflagCreate, ::i32 iGoodStride, bool bPreserve, bool bTopDraw2d) override;
      //bool host(::windowing::window_buffer * pwindowbuffer, ::windowing::window * pwindow, const ::i32_size & sizeRaw) override;
      //bool on_host_read_pixels(::pixmap_t* pixmap) const override;
      //using ::image::image::create;
      void create_from_graphics(::draw2d::graphics * pdraw2dgraphics) override;
      void preserve(const ::i32_size& size, ::enum_flag eflagCreate) override;
      void clear_node_data() override;


      //cvirtual bool stretch(::draw2d::graphics * pdraw2dgraphics) override;
      //virtual bool draw(const ::image::image * pimage) override;
      void _draw_raw(const ::i32_rectangle & rectangleTarget, ::image::image * pimageSrc, const ::i32_point & pointSrc) override;


      void set_image_icon(::image::icon * picon, ::i32 cx, ::i32 cy) override;


      protected:

         ::image_pixmap_lease _map(::image::enum_map emap, const ::i32_rectangle & rectangle) override;
         void _unmap(::image_pixmap_lease * pimagepixmaplease) override;

   };


} // namespace draw2d_gdiplus




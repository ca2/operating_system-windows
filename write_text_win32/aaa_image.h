#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS image :
      virtual public ::image
   {
   public:


      HBITMAP                    m_hbitmap;
      ::long_long_size                   m_sizeWnd;
      BITMAPINFO                 m_bitmapinfo;


      image();
      virtual ~image();


      void draw2d_gdiplus_image_common_construct();

      virtual ::draw2d::graphics * _get_graphics() const;
      virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();

      
      //using ::image::stretch;
      //virtual bool stretch(::image::image * pimage) override;


      bool dc_select(bool bSelect = true);

      virtual bool on_exif_orientation();


      virtual bool _load_thumbnail(const ::string & psz);


      virtual bool map(bool) override;
      virtual bool _unmap() override;


      virtual void create(const ::int_size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      virtual bool host(const ::pixmap * pixmap) override;
      virtual bool on_host_read_pixels(const ::pixmap* pixmap) override;
      virtual void create(::draw2d::graphics * pgraphics) override;
      virtual bool destroy() override;


      //cvirtual bool stretch(::draw2d::graphics * pgraphics) override;
      //virtual bool draw(const ::image::image * pimage) override;
      virtual bool _draw_raw(const ::int_rectangle & rectangleTarget, ::image::image * pimageSrc, const ::int_point & pointSrc) override;


      virtual void SetIconMask(::image::icon * picon, int cx, int cy) override;


   };


} // namespace draw2d_gdiplus




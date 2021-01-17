#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS image :
      virtual public ::image
   {
   public:


      HBITMAP                    m_hbitmap;
      ::size64                   m_sizeWnd;
      BITMAPINFO                 m_bitmapinfo;


      image();
      virtual ~image();


      void draw2d_gdiplus_image_common_construct();

      virtual ::draw2d::graphics * _get_graphics() const;
      virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();

      //void stretch_image(::image * pimage);

      bool dc_select(bool bSelect = true);

      virtual bool on_exif_orientation();


      virtual bool _load_thumbnail(const char * psz);


      virtual bool map(bool) override;
      virtual bool _unmap() override;


      virtual ::e_status create(const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      virtual bool host(const ::pixmap * pixmap) override;
      virtual bool on_host_read_pixels(const ::pixmap* pixmap) override;
      virtual ::e_status create(::draw2d::graphics * pgraphics) override;
      virtual bool destroy() override;


      virtual bool stretch(::draw2d::graphics * pgraphics) override;
      //virtual bool draw(const ::image * pimage) override;
      virtual bool draw(const ::rect & rectDst, ::image * pimageSrc, const ::point & pointSrc) override;


      virtual ::e_status SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


   };


} // namespace draw2d_gdiplus




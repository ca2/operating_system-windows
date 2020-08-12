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


      virtual bool _map(bool) override;
      virtual bool _unmap() override;


      virtual ::estatus create(const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      //virtual ::estatus create(i32 iWidth, i32 iHeight, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1, bool bPreserve = false) override;
      virtual bool host(const ::pixmap * pixmap) override;
      virtual bool on_host_read_pixels(const ::pixmap* pixmap) override;
      virtual ::estatus create(::draw2d::graphics * pgraphics) override;
      virtual bool destroy() override;



      bool from(::draw2d::graphics * pgraphics);
      bool from(const ::point & pointDest, ::draw2d::graphics * pgraphics, const ::point & point, const ::size & size);
      virtual bool from(const ::point & pointDest, ::image * pimageSrc, const ::point & point, const ::size & size) override;

      bool to(::draw2d::graphics * pgraphics, const ::point & point, const ::size & size, const ::point & pointSrc);

      virtual ::estatus SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


   };


} // namespace draw2d_gdiplus




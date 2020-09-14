#pragma once


namespace draw2d_gdi
{


   class CLASS_DECL_DRAW2D_GDI image_impl :
      virtual public ::image_impl
   {
   public:


      BITMAPINFO              m_info;
      ::draw2d::bitmap_pointer     m_pbitmap;
      ::draw2d::graphics_pointer   m_spgraphics;
      HBITMAP                 m_hbitmapOriginal;
      bool                    m_bMapped;



      image_impl(::layered * pobjectContext);
      virtual ~image_impl();


      virtual bool _map(bool bApplyAlphaTransform = true) override;
      virtual bool _unmap()  override;


      virtual ::draw2d::graphics * _get_graphics() const;
      virtual ::draw2d::bitmap_pointer get_bitmap() const;
      virtual ::draw2d::bitmap_pointer detach_bitmap();


      //virtual COLORREF * get_data();


      bool stretch_image(::image * pimage);


      bool dc_select(bool bSelect = true);





      virtual bool create(const ::size & size, ::eobject eobjectCreate = DEFAULT_CREATE_IMAGE_OBJECT_FLAG, int iGoodStride = -1) override;
      virtual bool create(::draw2d::graphics_pointer & pgraphics) override;
      virtual bool destroy() override;



      bool from(::draw2d::graphics_pointer & pgraphics);
      bool from(const ::point & pointDest, ::draw2d::graphics_pointer & pgraphics, const ::point & point, const ::size & sz) override;

      bool to(::draw2d::graphics_pointer & pgraphics, const ::point & point, const ::size & size, const ::point & pointSrc) override;

      //virtual bool update_window(::aura::draw_interface * pwnd,::message::message * pmessage,bool bTransferBuffer = true);
      //virtual bool print_window(::aura::draw_interface * pwnd,::message::message * pmessage);

      virtual bool SetIconMask(::draw2d::icon * picon, i32 cx, i32 cy) override;


      virtual bool process_blend(COLORREF clr, i32 x, i32 y, ::draw2d::e_alpha_mode ealphamode, ::image * pimageSrc);
      virtual bool process_blend(::image * pimage, i32 x, i32 y, ::draw2d::e_alpha_mode ealphamode, ::image * pimageSrc);
      virtual bool process_blend(::draw2d::brush * pbrush, i32 x, i32 y, ::draw2d::e_alpha_mode ealphamode, ::image * pimageSrc);
      virtual bool process_initialize(::draw2d::brush * pbrush, bool bReset = true);
      virtual bool process_blend(::draw2d::pen * ppen, i32 x, i32 y, ::draw2d::e_alpha_mode ealphamode, ::image * pimage);
      virtual bool process_initialize(::draw2d::pen * ppen, bool bReset = true);

      virtual COLORREF make_colorref(i32 a, i32 rect, i32 g, i32 b);

   };


} // namespace draw2d_gdi




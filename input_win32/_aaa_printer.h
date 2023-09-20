#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS printer :
      virtual public ::draw2d::printer
   {
   public:


      class CLASS_DECL_DRAW2D_GDIPLUS document_properties :
         virtual public ::object
      {
      public:


         DEVMODE * m_pdevmode;
         HDC            m_hdc;


         document_properties();
         virtual ~document_properties();


         virtual bool initialize(::draw2d::printer * pprinter, DEVMODE * pdevmode = nullptr);
         virtual bool close();
         virtual ::draw2d::graphics * create_graphics() override;

      };


      wstring                 m_wstrName;
      HANDLE                  m_hPrinter;
      document_properties     m_documentproperties;


      printer();
      virtual ~printer();


      virtual bool open(const ::string & pszDeviceName);
      virtual ::draw2d::graphics_pointer create_graphics() override;
      virtual bool is_opened();
      virtual bool close();



   };


} // namespace draw2d_gdiplus



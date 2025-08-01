#include "framework.h"


namespace draw2d_gdi
{


   bitmap::bitmap(::particle * pparticle):
      ::draw2d::bitmap(pobject)
   {

   }


   bitmap::~bitmap()
   {

   }


   bitmap::operator HBITMAP() const
   {

      return (HBITMAP)(this == nullptr ? nullptr : get_handle());

   }


   bool bitmap::CreateBitmap(::draw2d::graphics_pointer & pgraphics,int nWidth,int nHeight,UINT nPlanes,UINT nBitcount,const void * lpBits,int stride)
   {

      return Attach(::CreateBitmap(nWidth,nHeight,nPlanes,nBitcount,lpBits));

   }


   bool bitmap::CreateBitmapIndirect(LPBITMAP lpBitmap)
   {

      return Attach(::CreateBitmapIndirect(lpBitmap));

   }

   bool bitmap::CreateDIBSection(::draw2d::graphics_pointer & pgraphics,const BITMAPINFO * lpbmi,UINT usage,void **ppvBits,int * stride,HANDLE hSection,unsigned int offset)
   {


      if(!Attach(::CreateDIBSection(pgraphics == nullptr ? nullptr : GDI_HDC(pgraphics),lpbmi,usage,ppvBits,hSection,offset)))
         return false;

      if(stride != nullptr)
      {

         int scan = abs((long)lpbmi->bmiHeader.biSizeImage) / abs((long)lpbmi->bmiHeader.biHeight);

         *stride = scan;

      }

      return true;

   }


   bool bitmap::CreateDIBitmap(::draw2d::graphics_pointer & pgraphics,const BITMAPINFOHEADER *pbmih,unsigned int flInit,const void *pjBits,const BITMAPINFO *pbmi,UINT iUsage)
   {

      return Attach(::CreateDIBitmap(GDI_HDC(pgraphics),pbmih,flInit,pjBits,pbmi,iUsage));

   }


   unsigned int bitmap::SetBitmapBits(unsigned int dwCount,const void * lpBits)
   {

      return ::SetBitmapBits((HBITMAP)get_handle(),dwCount,lpBits);

   }


   unsigned int bitmap::GetBitmapBits(unsigned int dwCount,LPVOID lpBits) const
   {

      return ::GetBitmapBits((HBITMAP)get_handle(),dwCount,lpBits);

   }


   bool bitmap::LoadBitmap(const ::scoped_string & scopedstrResourceName)
   {

      //      return Attach(::LoadBitmap(::windows_definition::FindResourceHandle(lpszResourceName, RT_BITMAP), lpszResourceName));
      return false;

   }


   ::int_size bitmap::SetBitmapDimension(int nWidth,int nHeight)
   {

      ::int_size size;

      VERIFY(::SetBitmapDimensionEx((HBITMAP)get_handle(),nWidth,nHeight,&size));

      return size;

   }


   ::int_size bitmap::GetBitmapDimension() const
   {

      ::int_size size;

      VERIFY(::GetBitmapDimensionEx((HBITMAP)get_handle(),&size));

      return size;

   }


   bool bitmap::LoadBitmap(UINT nIDResource)
   {

      //      return Attach(::LoadBitmap(::windows_definition::FindResourceHandle(MAKEINTRESOURCE(nIDResource), RT_BITMAP), MAKEINTRESOURCE(nIDResource)));
      return false;

   }


   bool bitmap::LoadOEMBitmap(UINT nIDBitmap)
   {

      return Attach(::LoadBitmap(nullptr,MAKEINTRESOURCE(nIDBitmap)));

   }


   bool bitmap::CreateCompatibleBitmap(::draw2d::graphics_pointer & pgraphics,int nWidth,int nHeight)
   {

      return Attach(::CreateCompatibleBitmap((dynamic_cast<::draw2d_gdi::graphics *>(pgraphics))->get_handle1(),nWidth,nHeight));

   }


   bool bitmap::CreateDiscardableBitmap(::draw2d::graphics_pointer & pgraphics,int nWidth,int nHeight)
   {

      return Attach(::CreateDiscardableBitmap((dynamic_cast<::draw2d_gdi::graphics *>(pgraphics))->get_handle1(),nWidth,nHeight));

   }


   int bitmap::GetBitmap(BITMAP* pBitMap)
   {

      return get_object(sizeof(BITMAP),pBitMap);

   }


   void bitmap::dump(dump_context & dumpcontext) const
   {
      ::draw2d::object::dump(dumpcontext);

      if(get_handle() == nullptr)
         return;

      /*if (!::windows_definition::Data.bWin95 && ::GetObjectType(get_handle()) != OBJ_BITMAP)
      {
      // not a valid object
      dumpcontext << "has ILLEGAL HBITMAP!";
      return;
      }*/

      BITMAP bm;
      VERIFY(get_object(sizeof(bm),&bm));
      dumpcontext << "bm.bmType = " << bm.bmType;
      dumpcontext << "\nbm.bmHeight = " << bm.bmHeight;
      dumpcontext << "\nbm.bmWidth = " << bm.bmWidth;
      dumpcontext << "\nbm.bmWidthBytes = " << bm.bmWidthBytes;
      dumpcontext << "\nbm.bmPlanes = " << bm.bmPlanes;
      dumpcontext << "\nbm.bmBitsPixel = " << bm.bmBitsPixel;

      dumpcontext << "\n";
   }




   HBITMAP bitmap::_GetHBITMAP()
   {

      return operator HBITMAP ();

   }


   void bitmap::_ReleaseHBITMAP(HBITMAP hbitmap)
   {

      // Do nothing, _GetHBITMAP does not create additional bitmap for the GetHBITMAP/ReleaseHBITMAP protocol,
      // so does not delete underlying original HBITMAP handle
      __UNREFERENCED_PARAMETER(hbitmap);

   }




} // namespace draw2d_gdi






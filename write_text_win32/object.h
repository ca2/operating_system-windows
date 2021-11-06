#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS object :
      virtual public ::draw2d::object
   {
      public:


         object();
         virtual ~object();


         virtual void * get_os_data() const;


         bool delete_object();


         i32 get_object(i32 nCount, LPVOID pObject) const;

         UINT GetObjectType() const;
         bool CreateStockObject(i32 nIndex);
         bool UnrealizeObject();
         bool operator==(const ::draw2d::object& obj) const;
         bool operator!=(const ::draw2d::object& obj) const;

#ifdef DEBUG
         void assert_valid() const override;
         void dump(dump_context & dumpcontext) const override;
#endif

   };


} // namespace aura




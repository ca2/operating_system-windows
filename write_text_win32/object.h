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


         int get_object(int nCount, LPVOID pObject) const;

         UINT GetObjectType() const;
         bool CreateStockObject(int nIndex);
         bool UnrealizeObject();
         bool operator==(const ::draw2d::object& obj) const;
         bool operator!=(const ::draw2d::object& obj) const;

#ifdef DEBUG
         void assert_ok() const override;
         void dump(dump_context & dumpcontext) const override;
#endif

   };


} // namespace aura




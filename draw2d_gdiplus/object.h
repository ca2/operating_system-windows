#pragma once


namespace draw2d_gdiplus
{


   class CLASS_DECL_DRAW2D_GDIPLUS object :
      virtual public ::draw2d::object
   {
      public:


         object();
         virtual ~object();

#ifdef DEBUG
         virtual void assert_valid() const override;
         virtual void dump(dump_context & dumpcontext) const override;
#endif

   };


} // namespace aura




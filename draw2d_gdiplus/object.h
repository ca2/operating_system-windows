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
         void assert_valid() const override;
         void dump(dump_context & dumpcontext) const override;
#endif

   };


} // namespace aura




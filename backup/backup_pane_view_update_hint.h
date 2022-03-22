#pragma once


namespace backup
{

   enum enum_impact
   {
      impact_none,
      impact_backup,
      impact_options,
   };


   class CLASS_DECL_CA2_BACKUP ::update :
      public ::object  
   {
   public:
      enum enum_type
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowView,
      };
      // DECLARE_DYNAMIC(::update)
   public:
      void set_type(enum_type enum_type);
      bool is_type_of(enum_type enum_type);

      ::update();
      virtual ~::update();

      enum_impact m_eview;
   protected:
      enum_type m_etype;

   };


} // namespace backup




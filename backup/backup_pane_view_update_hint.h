#pragma once


namespace backup
{

   enum e_impact
   {
      impact_none,
      impact_backup,
      impact_options,
   };


   class CLASS_DECL_CA2_BACKUP ::update :
      public ::object  
   {
   public:
      enum e_type
      {
         TypeGetView,
         TypeSetView,
         TypeOnShowView,
      };
      // DECLARE_DYNAMIC(::update)
   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      ::update();
      virtual ~::update();

      e_impact m_eview;
   protected:
      e_type m_etype;

   };


} // namespace backup




#pragma once


namespace production
{

enum EPaneView
{
   impact_none,
   CONTEXT_MENU_IMPACT,
   PaneViewProduction,
   impact_three_action_launch,
   impact_configuration,
};


class CLASS_DECL_CA2_PRODUCTION ::update :
   public ::object  
{
public:
   enum enum_type
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnShowView,
   };
   // DECLARE_DYNAMIC(::update)
public:
	void set_type(enum_type enum_type);
	bool is_type_of(enum_type enum_type);

	::update();
	virtual ~::update();

   EPaneView m_eview;
protected:
   enum_type m_etype;

};

} // namespace production

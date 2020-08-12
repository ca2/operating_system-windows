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
   enum e_type
   {
      TypeGetView,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnShowView,
   };
   // DECLARE_DYNAMIC(::update)
public:
	void set_type(e_type e_type);
	bool is_type_of(e_type e_type);

	::update();
	virtual ~::update();

   EPaneView m_eview;
protected:
   e_type m_etype;

};

} // namespace production

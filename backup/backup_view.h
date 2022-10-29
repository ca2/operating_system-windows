#pragma once


namespace backup
{


   class CLASS_DECL_CA2_BACKUP impact :
      virtual public production::impact
   {
   public:
	   
      
      impact(::particle * pparticle);
      virtual ~impact();


      virtual ::production::production * create_production();


   };


} // namespace backup




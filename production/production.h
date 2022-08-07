#pragma once


#include "sphere/sphere/sphere.h"


#ifdef _CA2_FONTOPUS_PRODUCTION_DLL
    #define CLASS_DECL_CA2_PRODUCTION  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_CA2_PRODUCTION  CLASS_DECL_IMPORT
#endif


namespace production
{

   class application;

} // namespace production


#undef APP_TYPE
#define APP_TYPE ::production::application


//#include "hi5_facebook.h"

#include "production_production.h"


#include "production_frame.h"
#include "production_form_callback.h"
#include "production_pane_impact.h"

#include "production_document.h"

#include "production_impact.h"


#include "production_application.h"





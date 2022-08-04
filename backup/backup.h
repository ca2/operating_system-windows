#pragma once


#include "platform/production/production.h"


#ifdef _CA2_FONTOPUS_BACKUP_DLL
    #define CLASS_DECL_CA2_BACKUP  CLASS_DECL_EXPORT
#else
    #define CLASS_DECL_CA2_BACKUP  CLASS_DECL_IMPORT
#endif


#include "backup_backup.h"


#include "backup_frame.h"
#include "backup_document.h"
#include "backup_impact.h"
#include "backup_form_callback.h"


#include "backup_pane_impact.h"


#include "backup_application.h"




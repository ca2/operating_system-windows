// Created by camilo on 2023-01-15 16:18 <3ThomasBorregaardSørensen!!
#pragma once


#include "apex/platform/integration_context.h"


namespace apex_windows
{


   namespace integration
   {


      class CLASS_DECL_APEX_WINDOWS context :
         virtual public ::integration::context
      {
      public:


         ::string          m_strVs;
         ::string          m_strContext;
         ::string          m_strVCVersion;
         ::string          m_strTime;
         ::string          m_strSdk1;
         ::string          m_strPlat1;
         ::string          m_strPlat2;
         ::string          m_strVsTools;
         ::string          m_strStagePlatform;
         ::string          m_strLibPlatform;

         ::file::path      m_pathProjectDir;


         context();
         ~context() override;


         void prepare() override;

         void prepare_compile_and_link_environment() override;


         virtual void prepare1(const ::scoped_string & scopedstrSource, const ::string & scopedstrTarget);


         ::string prepare_path(const ::file::path & path) override;


      };


   } // namespace integration


} // namespace apex_windows




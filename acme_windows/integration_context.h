// Created by camilo on 2023-01-15 16:18 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/platform/integration_context.h"


namespace acme_windows
{


   namespace integration
   {


      class CLASS_DECL_ACME_WINDOWS context :
         virtual public ::integration::context
      {
      public:


         ::string          m_strVs;
         ::string          m_strContext;
         ::string          m_strVCVersion;
         ::string          m_strTime;
         //::string          m_strSdk1; // payload("sdk1")
         ::string          m_strPlat1;
         ::string          m_strPlat2;
         //::string          m_strVsTools; // payload("vstools")
         ::string          m_strStagePlatform;
         ::string          m_strLibPlatform;

         ::file::path      m_pathProjectDir;
         //::string_array    m_straLog;


         context();
         ~context() override;


         void prepare() override;

         void prepare_compile_and_link_environment() override;


         virtual void prepare1(const ::scoped_string & scopedstrSource, const ::string & scopedstrTarget);


         ::string prepare_path(const ::file::path & path) override;

         void prepare_compilation_script(::string& str) override;

         void prepare_linking_script(::string& str) override;
     
         virtual ::file::path base_integration_folder();

         virtual ::file::path host_integration_folder();


      };


   } // namespace integration


} // namespace acme_windows




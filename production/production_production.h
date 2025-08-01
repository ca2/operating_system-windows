#pragma once


namespace production
{

   class impact;


   class CLASS_DECL_CA2_PRODUCTION production : 
      virtual public ::thread 
   {
   public:

      enum e_version
      {
         version_backup,
         version_basis,
         version_stage,
      };


      class release :
         virtual public thread
      {
      public:
         

         production *   m_pproduction;
         string         m_strRelease;
         string         m_strServer;


         release(production * pproduction, const ::string & pszRelease, const ::string & pszServer);

         virtual bool init_thread() override;

         virtual void     run() override;

         virtual void     raw_run();

      };


      class compress_thread :
         virtual public thread
      {
      public:
         compress_thread(production * pproduction, manual_reset_happening * peventFinished);

         manual_reset_happening * m_pevFinished;
         production *   m_pproduction;
         unsigned int                m_dwThreadAffinityMask;
         virtual void     run() override;
      };

      string_array                 m_straMirror;
      string_array                 m_straMirrorStatus;
      ::mutex                   m_mutexStatus;
      string_array                 m_straStatus;
      bool                    m_bLoop;
      int                     m_iLoop;
      int                     m_iLoopCount;
      string                  m_strSubversionRevision;
      string_array                 m_straCompress;
      ::mutex                   m_mutexCompress;
      string                  m_strBuildTook;
      string                  m_strSpc;
      string                  m_strSignTool;
      string                  m_strSignPass;
      bool                    m_bReleased;
      string                  m_strStartTime;
      string                  m_strStdPostColor;
      string                  m_strBackPostColor;
      string                  m_strEmpPostColor;
      string                  m_strConfiguration;
      string                  m_strStatusEmail;
      int                 m_iGlobalRetry;
      string                  m_strTry;
      string                  m_strDownloadSite;

      string                  m_strTwitterConsumerKey;
      string                  m_strTwitterConsumerSecret;

      ::mutex                   m_mutexRelease;
      string_array                 m_straRelease;
      int                 m_iRelease;

      e_version               m_eversion;

      ::earth::time        m_timeStart;
      ::earth::time        m_timeEnd;

      string_array                 m_straStageDirAcceptedFileExtensions;

      int                     m_iStep;
                              
      ::pointer<::user::impact>               m_pimpact;
      bool                    m_bFinished;
      tick m_tickStart;
      tick m_tickEnd;
      string_array                 m_straCC;
      string_array                 m_straBB;
      string                  m_strBuild;
      string                  m_strFormatBuild;
      bool                    m_bEndProduction;
                              
      string                  m_strTag;
      ::file::path            m_strTagPath;
                              
      string                  m_strStatus;
      ::file::path            m_strBase;
      ::file::listing         m_straRoot;
      character_count                 m_iBaseLen;
      ::file::listing         m_straFiles;



      string_array                 m_straManifest;
      string_array                 m_straSignature;
      ::file::listing         m_straPath;


      bool                    m_bClean;
      bool                    m_bBuild;
                              
                              
      ::file::path            m_pathVrel;
      ::file::path            m_strCCAuth;
      ::file::path            m_strCCVrel;
      string                  m_strCCVrelNew;
      string                  m_strIndexMd5;

      bool                    m_bEndStatus;
      manual_reset_happening      m_happeningFinish;


      production(::particle * pparticle);
      virtual ~production();



      void start_production(e_version eversion);
      void start_loop(e_version eversion, int iLoopCount);
      void step();

      void defer_quit();

      void add_status(const ::string & psz);
      void change_status(const ::string & psz);

      string version_to_international_datetime(const ::string & psz);


      virtual void     run() override;


      virtual void     produce();

      bool get_file_list(const ::string & pszBase, const ::string & pszDir, ::file::listing & stra, bool bFileSet = false);
      // bool ftp_put_dir(CFtpConnection & ftpconn, const ::string & pszBase, const ::string & pszDir, int iMode);

      virtual void compress();
      virtual bool compress_next();

      virtual void generate_appmatter_spa();
      virtual void generate_appmatter_spa(const ::file::path & pathRoot);
      virtual void generate_appmatter_spa_folder(const ::file::path & pathRoot,const ::file::path & pathRelative);
      virtual void generate_appmatter_spa_locale(const ::file::path & pathRoot,const ::file::path & pathRelative);
      virtual void generate_appmatter_spa_style(const ::file::path & pathRoot,const ::file::path & pathRelative);
      virtual void generate_appmatter_spa(const ::file::path & pathRoot,const ::file::path & pathRelative);

      virtual void release_production();
      virtual bool release_npca2(const ::string & pszPlatform);
      virtual bool release_iexca2(const ::string & pszPlatform);
      virtual bool release_crxca2(const ::string & pszPlatform);

      virtual void add_path(const ::file::path & pathDir, const ::file::path & pathRelative);

      bool sync_source(const ::string & psz, const ::string & pszRevision);
      bool commit_for_new_build_and_new_release();
      bool commit_source(const ::string & psz);


      virtual bool twitter_auth();
      virtual string twitter_twit(const ::string & pszMessage);

      virtual bool facebook_auth();
      virtual string facebook_status(const ::string & pszMessage);

      void compress(const ::file::path & lpszRelative);

      void OnUpdateRelease();

      string xpi_digest(memory & mem);

      void xpi_sign_dir(const ::string & pszPlatform, const ::file::path & pathDir);
      void xpi_section(const ::string & pszManifest, const ::string & pszSignature);

      bool create_xpi(const ::string & pszPlatform, bool bSigned = true);
      bool create_unsigned_xpi(const ::string & pszPlatform);
      bool create_signed_xpi(const ::string & pszPlatform);

      void build(const ::string & psz);

      virtual void update_rc_file_version(const ::string & pszUrl);

      virtual string stage_platform(string strPlatform);

   };


} // namespace production



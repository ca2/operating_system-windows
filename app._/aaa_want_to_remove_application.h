#pragma once


namespace appfy
{

    class application :
        public ::console_application
    {
    public:




        application();
        ~application() override;
      
      __DECLARE_APPLICATION_RELEASE_TIME();



        virtual void on_request(::create* pcreate) override;

        void appfy();

        virtual void term_instance() override;

    };


} // namespace appfy




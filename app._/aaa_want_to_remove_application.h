#pragma once


namespace appfy
{

    class application :
        public ::console_application
    {
    public:




        application();
        ~application() override;


        virtual void on_request(::create* pcreate) override;

        void appfy();

        virtual void term_instance() override;

    };


} // namespace appfy




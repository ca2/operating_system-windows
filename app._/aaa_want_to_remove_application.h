#pragma once


namespace appfy
{

    class application :
        public ::console_application
    {
    public:




        application();
        virtual ~application();


        virtual void on_request(::create* pcreate) override;

        void appfy();

        virtual void term_instance() override;

    };


} // namespace appfy




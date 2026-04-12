#pragma once



class CLASS_DECL_ACME nano_timer
{
public:


   HANDLE      m_hTimer;

   nano_timer();
   ~nano_timer();


   void wait(unsigned long long uWait);


   void close_timer();


};

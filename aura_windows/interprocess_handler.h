// created by Camilo 2021-01-31 05:26 BRT <3CamiloSasukeThomasBorregaardSoerensen
#pragma once


namespace windows
{


   class CLASS_DECL_APEX interprocess_handler :
      virtual public ::inteprocess::handler
   {
   public:


      interprocess_handler();
      virtual ~interprocess_handler();


      bool create(const ::string & pszChannel);
      bool destroy();


      virtual void * on_interprocess_receive(rx * prx, const ::string & pszMessage);
      virtual void * on_interprocess_receive(rx * prx, int message, void * pdata, memsize len);
      virtual void * on_interprocess_post(rx * prx, huge_integer a, huge_integer b);


      virtual bool on_idle();


      lresult message_queue_proc(UINT message, wparam wparam, lparam lparam);

   };


} // namespace windows








































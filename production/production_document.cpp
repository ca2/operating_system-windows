#include "framework.h"
#include "aura/update.h"


namespace production
{


   document::document(::particle * pparticle):
      ::object(pobject),
      ::user::document(pobject),
      ::data::data_container_base(pobject),
      ::user::document(pobject)
   {
   }

   bool document::on_new_document()
   {

      if (!::user::document::on_new_document())
         return false;


      update_all_impacts(nullptr, 0);


      return true;
   }

   document::~document()
   {
   }



#ifdef DEBUG
   void document::assert_ok() const
   {
      ::user::document::assert_ok();
   }

   void document::dump(dump_context & dumpcontext) const
   {
      ::user::document::dump(dumpcontext);
   }
#endif //DEBUG

   void document::data_on_after_change(::message::message * pmessage)
   {


      __UNREFERENCED_PARAMETER(pmessage);


   }

   bool document::on_open_document(const var & payloadFile)
   {

      string str = file().as_string(payloadFile);

      //  m_document.load(str);

      update_all_impacts(id_open_document);

      return true;


   }


} // namespace production




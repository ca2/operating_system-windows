#include "aura/app/acid.inl"


::aura::application * get_acid_app(::object * pobject)
{

   ::install::application * pinstallapp = new ::install::application();

   pinstallapp->m_bAdmin = true;

   return pinstallapp;

}
#include "aura/app/acid.inl"


::aura::application * get_acid_app(::particle * pparticle)
{

   ::install::application * pinstallapp = ___new ::install::application();

   pinstallapp->m_bAdmin = true;

   return pinstallapp;

}

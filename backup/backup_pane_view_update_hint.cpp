#include "framework.h"

namespace backup
{

::update::update()
{

}

::update::~::update()
{

}

bool ::update::is_type_of(e_type e_type)
{
   return m_etype == e_type;
}

void ::update::set_type(e_type e_type)
{
   m_etype = e_type;
}

} // namespace backup
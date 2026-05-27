// Created by camilo on 2021-01-21 05:10 PM <3ThomasBorregaardSorensen
#include "framework.h"
#include "acme/operating_system.h"
#include "::micro::child.h"
#include "micro::window.h"


void ::micro::child::set_focus()
{

   m_pwindow->m_pchildFocus = this;

}










window_opengl::window_opengl(::matter * pobject) :
   matter(pobject),
   window_graphics(pobject)
{

}


window_opengl::~window_opengl()
{

}


void window_opengl::on_create_window(::acme::windowing::window * pacmewindowingwindow)
{

}




void window_opengl::create_window_graphics(long long cxParam, long long cyParam, int iStrideParam)
{

   destroy_window_graphics();

   m_cx = cxParam;

   m_cy = cyParam;

   m_iScan = 0;

}


void window_opengl::destroy_window_graphics()
{

   window_graphics::destroy_window_graphics();

}


::draw2d::graphics * window_opengl::on_begin_draw()
{
 
   if (m_spgraphics.is_null())
   {

      m_spgraphics.create(this);

   }

   if(m_spgraphics->get_os_data() == nullptr)
   {

      bool bOk = m_spgraphics->CreateWindowDC(m_pimpl->m_pacmewindowingwindow);

      if (!bOk)
      {

         throw ::exception(::exception("failed to reference"););

      }

   }

   m_spgraphics->on_begin_draw(m_pimpl->m_pacmewindowingwindow, m_pimpl->m_rectangleParentClient.size());

   return m_spgraphics;

}


void window_opengl::update_window()
{

   m_spgraphics->on_end_draw(m_pimpl->m_pacmewindowingwindow);

}





void interaction_impl::CalcWindowRect(::int_rectangle * pClientRect, unsigned int nAdjustType)
{

   unsigned int dwExStyle = GetExStyle();

   if (nAdjustType == 0)
   {

      dwExStyle &= ~WS_EX_CLIENTEDGE;

   }

   ::AdjustWindowRectEx(pClientRect, GetStyle(), false, dwExStyle);

}

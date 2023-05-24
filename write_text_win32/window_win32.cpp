

void interaction_impl::CalcWindowRect(::rectangle_i32 * pClientRect, ::u32 nAdjustType)
{

   u32 dwExStyle = GetExStyle();

   if (nAdjustType == 0)
   {

      dwExStyle &= ~WS_EX_CLIENTEDGE;

   }

   ::AdjustWindowRectEx(pClientRect, GetStyle(), false, dwExStyle);

}

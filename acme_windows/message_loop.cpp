#include "framework.h"
#include "acme/_operating_system.h"


void _c_simple_message_loop()
{

   MSG msg;

	while(::GetMessage(&msg, nullptr, 0, 0xffffffffu))
	{
		
		TranslateMessage(&msg);

		DispatchMessage(&msg);

	}

}




#pragma once


namespace windows
{


	class CLASS_DECL_ACME print_task :
	   virtual public ::user::print_task
	{
	public:


	   print_task(::pointer<base_application>papp);
	   virtual ~print_task();


	   virtual int run();

	};


} // namespace windows





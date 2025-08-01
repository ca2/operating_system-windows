#pragma once


int installer_start(const ::scoped_string & scopedstrVersion, const ::scoped_string & scopedstrId);


namespace npca2
{

   class host;

   enum enum_check
   {
      check_before_auth,
      check_before_start,
   };


   class plugin :
      virtual public ::hotplugin::plugin
   {
   public:



      plugin();
      virtual ~plugin();



      virtual bool hist(const ::scoped_string & scopedstrUrl);
      virtual void run_start_install(const ::scoped_string & scopedstrRun);


      virtual void start_ca2();


      //int starter_start(const ::scoped_string & scopedstrId);

      virtual bool initialize();

      //virtual void on_bare_paint(HDC hdc, LPCRECT lprect);
      virtual void on_paint(HDC hdcWindow, LPCRECT lprect);

      virtual void on_prepare_memory();

      virtual UINT_PTR message_handler(UINT_PTR emessage, wparam wparam, lparam lparam);


   };

   ATOM MyRegisterClass(HINSTANCE hInstance);

} // namespace npca2

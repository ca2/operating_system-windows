#pragma once


int installer_start(const ::string & pszVersion, const ::string & pszId);


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



      virtual bool hist(const ::string & pszUrl);
      virtual void run_start_install(const ::string & pszRun);


      virtual void start_ca2();


      //int starter_start(const ::string & pszId);

      virtual bool initialize();

      //virtual void on_bare_paint(HDC hdc, LPCRECT lprect);
      virtual void on_paint(HDC hdcWindow, LPCRECT lprect);

      virtual void on_prepare_memory();

      virtual UINT_PTR message_handler(UINT_PTR emessage, wparam wparam, lparam lparam);


   };

   ATOM MyRegisterClass(HINSTANCE hInstance);

} // namespace npca2

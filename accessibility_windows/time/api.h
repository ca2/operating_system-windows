#pragma once


namespace windows
{


   class CLASS_DECL_ACME api_base
   {
   public:


      static FARPROC get_address(const scoped_string & strModule, const_char_pointer pszName);

   };



   template < typename PFN >
   class api :
      public api_base
   {
   public:


      inline static PFN get_address(const scoped_string & strModule, const_char_pointer pszName)
      {

         return (PFN) api_base::get_address(pszModule, pszName);
         
      }


   };


} // namespace windows




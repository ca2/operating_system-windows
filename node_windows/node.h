//
// Created by camilo on 21/01/2021. <33TBS!!
//

//
// Created by camilo on 21/01/2021. <3-<3ThomasBS!!
//
#pragma once


namespace node_windows
{



   class node :
      virtual public ::aura::node
   {
   public:


      node();

      virtual ~node();


      string get_user_name();


      virtual bool _os_calc_app_dark_mode() override;

      virtual bool _os_calc_system_dark_mode() override;


   };


} // namespace node_windows




#pragma once


#include "berg/user/user/impact.h"


//namespace multimedia
//{


   namespace audio_mixer
   {


      class audio_mixer;
      class control;
      class destination;
      class source;


   } // namespace audio_mixer


   namespace audio_mixer_user_base
   {


      class document;
      class control_data;


      class CLASS_DECL_AUDIO_MIXER_USERBASE control_impact :
         public ::user::impact
      {
      public:


         enum Timers
         {

            UpdateTimer = 1

         };


         enum UpdateEvents
         {
            UpdateEventTimer = 1,
            UpdateEventUpdated = 2
         };

         enum UpdateStates
         {
            UpdateStateTiming = 1,
            UpdateStateUpdating = 2
         };

         ::pointer<control_data>      m_pdata;
         color32_t                     m_colorForeground;
         color32_t                     m_colorBackground;
         ::draw2d::brush_pointer       m_pbrushBackground;
         unsigned int                           m_uiUpdateTimer;
         unsigned int                           m_uiUpdateState;
         //::thread_pointer              m_pthreadContextMenu;
         //unsigned int                           m_dwThreadIdContextMenu;
         bool                          m_bInitialized;
         unsigned int                           m_uiNextSliderID;
         unsigned int                           m_dwUpdateTime;
         string                        m_strSearch;

         static const int              cnListCount;

         
         pointer_array < ::audio_mixer::control >     m_controla;
         atom_map_base < ::pointer<::user::still >>               m_labelmap;


         control_impact();
         ~control_impact() override;


         // void assert_ok() const override;
         // void dump(dump_context & dumpcontext) const override;

         
         virtual void create_control_data();


         control_data * get_data();


         ::audio_mixer::destination * get_destination();
         ::audio_mixer::audio_mixer * get_mixer();
         document * get_document();





         void LayoutLine(int iSource, ::audio_mixer::source * pSource, int iStartX, int iStartY, int * iEndX, int *iEndY);
         void set_title();
         void on_layout(::draw2d::graphics_pointer & pgraphics) override;
         bool create_control(::audio_mixer::control * pControl);
         bool CreateMuteControl(::audio_mixer::control * pControl);
         bool CreateVolumeControl(::audio_mixer::control * pControl);
         void delete_contents();
         bool CreateControls(::audio_mixer::source *pSource);
         bool CreateControls();
         //      enum_impact GetCurrentImpactIndex();



         void install_message_routing(::channel * pchannel) override;

         virtual void pre_translate_message(::message::message * pmessage) override;
         virtual void OnInitialUpdate();
         virtual bool pre_create_window(::user::system * pusersystem) override;
         void handle(::topic * ptopic, ::handler_context * phandlercontext) override;
         virtual void OnDraw(::image::image * pimage);
         //virtual bool OnNotify(::user::message * pusermessage) override;
         //virtual bool OnCommand(::user::message * pusermessage) override;
         DECLARE_MESSAGE_HANDLER(_001OnColumnclickList);
         DECLARE_MESSAGE_HANDLER(on_message_size);
         DECLARE_MESSAGE_HANDLER(on_message_destroy);
         DECLARE_MESSAGE_HANDLER(_001OnGetdispinfoList);
         DECLARE_MESSAGE_HANDLER(_001OnDblclkList);
         DECLARE_MESSAGE_HANDLER(_001OnButtonReserve);
         DECLARE_MESSAGE_HANDLER(on_message_create);
         DECLARE_MESSAGE_HANDLER(_001OnUpdateImpactUpdate);
         DECLARE_MESSAGE_HANDLER(on_message_scroll_y);
         DECLARE_MESSAGE_HANDLER(_001OnCtlColor);
         DECLARE_MESSAGE_HANDLER(on_message_scroll_x);

         //void _OnUpdate(::pointer<::user::impact>pimpact, LPARAM lhint, ::object * pupdate);

      };


   } // namespace audio_mixer_user_base


//} // namespace multimedia
//
//
//
//
//

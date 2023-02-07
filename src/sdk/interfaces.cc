#include "interfaces.hh"

namespace interfaces {
    void init() {
        m_client            = memory::get_interface<i_base_client_dll>(_("./csgo/bin/linux64/client_client.so"), _("VClient"));
        m_engine            = memory::get_interface<i_engine_client>(_("./bin/linux64/engine_client.so"), _("VEngineClient"));
        m_entity_list       = memory::get_interface<i_client_entity_list>(_("./csgo/bin/linux64/client_client.so"), _("VClientEntityList"));
        m_model_render      = memory::get_interface<i_model_render>(_("./bin/linux64/engine_client.so"), _("VEngineModel"));
        m_material_system   = memory::get_interface<i_material_system>(_("./bin/linux64/materialsystem_client.so"), _("VMaterialSystem"));
        m_trace_system      = memory::get_interface<i_engine_trace>(_("./bin/linux64/engine_client.so"), _("EngineTraceClient"));
        m_cvar_system       = memory::get_interface<i_cvar_system>(_("./bin/linux64/materialsystem_client.so"), _("VEngineCvar"));
        m_model_info        = memory::get_interface<i_model_info>(_("./bin/linux64/engine_client.so"), _("VModelInfoClient"));
        m_sound             = memory::get_interface<i_engine_sound>(_("./bin/linux64/engine_client.so"), _("IEngineSoundClient"));
        m_surface           = memory::get_interface<i_surface>(_("./bin/linux64/vguimatsurface_client.so"), _("VGUI_Surface"));
        m_localize          = memory::get_interface<i_localize>(_("./bin/linux64/localize_client.so"), _("Localize_"));
        m_event_manager     = memory::get_interface<i_game_event_manager>(_("./bin/linux64/engine_client.so"), _("GAMEEVENTSMANAGER002"), true);
        m_prediction        = memory::get_interface<i_prediction>(_("./csgo/bin/linux64/client_client.so"), _("VClientPrediction001"), true);
        m_game_movement     = memory::get_interface<i_game_movement>(_("./csgo/bin/linux64/client_client.so"), _("GameMovement"));
        m_studio_render     = memory::get_interface<i_studio_render>(_("./bin/linux64/studiorender_client.so"), _("VStudioRender"));
        m_game_types        = memory::get_interface<i_game_types>(_("./csgo/bin/linux64/matchmaking_client.so"), _("VENGINE_GAMETYPES_VERSION002"), true);

        m_client_mode = memory::get_vfunc(m_client, 10).self_offset(11).self_rel32().cast<i_client_mode* (*)()>()();
        m_global_vars = memory::get_vfunc(m_client, 11).self_offset(13).self_rel32(0x3).self_deref().cast<i_global_vars*>();

        m_client_state = memory::get_vfunc(m_engine, 12).self_offset(9).self_rel32().cast<i_client_state* (*)(int)>()(-1);

        m_move_helper       = SIG("/client_client.so", "? 48 89 3D ? ? ? ? C3").self_offset(0x1).self_rel32(0x3).self_deref().cast<i_move_helper*>();
        m_game_rules        = SIG("/client_client.so", "48 8D 05 AA 50 93 01 48 8B").self_rel32(0x3).cast<i_game_rules**>();
        m_player_resource   = SIG("/client_client.so", "48 8B 05 C1 88 B1 01 55 48 89 E5").self_rel32(0x3).cast<i_cs_player_resource**>();
    }

    i_base_client_dll*      m_client = nullptr;
    i_global_vars*          m_global_vars = nullptr;
    i_engine_client*        m_engine = nullptr;
    i_client_entity_list*   m_entity_list = nullptr;
    i_client_mode*          m_client_mode = nullptr;
    i_model_render*         m_model_render = nullptr;
    i_material_system*      m_material_system = nullptr;
    i_engine_trace*         m_trace_system = nullptr;
    i_cvar_system*          m_cvar_system = nullptr;
    i_model_info*           m_model_info = nullptr;
    i_engine_sound*         m_sound = nullptr;
    i_surface*              m_surface = nullptr;
    i_localize*             m_localize = nullptr;
    i_game_event_manager*   m_event_manager = nullptr;
    i_move_helper*          m_move_helper = nullptr;
    i_prediction*           m_prediction = nullptr;
    i_game_movement*        m_game_movement = nullptr;
    i_studio_render*        m_studio_render = nullptr;
    i_game_rules**          m_game_rules = nullptr;
    i_client_state*         m_client_state = nullptr;
    i_game_types*           m_game_types = nullptr;
    i_cs_player_resource**  m_player_resource = nullptr;
}
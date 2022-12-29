#pragma once

#include "sdk.hh"

namespace interfaces {
    void init();

    extern i_base_client_dll*    m_client;
    extern i_global_vars*        m_global_vars;
    extern i_engine_client*      m_engine;
    extern i_client_entity_list* m_entity_list;
    extern i_client_mode*        m_client_mode;
    extern i_model_render*       m_model_render;
    extern i_material_system*    m_material_system;
    extern i_engine_trace*       m_trace_system;
    extern i_cvar_system*        m_cvar_system;
    extern i_model_info*         m_model_info;
    extern i_engine_sound*       m_sound;
    extern i_surface*            m_surface;
    extern i_localize*           m_localize;
    extern i_game_event_manager* m_event_manager;
    extern i_move_helper*        m_move_helper;
    extern i_prediction*         m_prediction;
    extern i_game_movement*      m_game_movement;
    extern i_studio_render*      m_studio_render;
}
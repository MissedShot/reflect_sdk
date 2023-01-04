#include "../hooks.hh"

bool hooks::client_mode::create_move::hook(void* ptr, float frame_time, c_user_cmd* cmd) {
    original(ptr, frame_time, cmd);

    if (!cmd->m_command_number)
        return false;

    globals::m_cmd = cmd;

    globals::m_local = reinterpret_cast<c_cs_player*>(interfaces::m_entity_list->get_client_entity(interfaces::m_engine->get_local_player()));
    if (!globals::m_local)
        return false;

    movement->jump_related();

    engine_prediction->process();
    {
        /* aimbot, etc. here */
    }
    engine_prediction->restore();

    cmd->m_view_angles.sanitize();

    return false;
}
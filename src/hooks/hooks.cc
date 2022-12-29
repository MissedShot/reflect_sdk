#include "hooks.hh"

namespace hooks {
    void init() {
        sdl::hook();

        client_mode::create_move::original = (decltype(&client_mode::create_move::hook))vmt_hook::hook(interfaces::m_client_mode, (void*)client_mode::create_move::hook, 25);

        client::frame_stage_notify::original = (decltype(&client::frame_stage_notify::hook))vmt_hook::hook(interfaces::m_client, (void*)client::frame_stage_notify::hook, 37);

        model_render::draw_model::original = (decltype(&model_render::draw_model::hook))vmt_hook::hook(interfaces::m_model_render, (void*)model_render::draw_model::hook, 21);

        surface::paint::original = (decltype(&surface::paint::hook))vmt_hook::hook(interfaces::m_surface, (void*)surface::paint::hook, 15);
    }

    void undo() {
        sdl::unhook();
    }
}
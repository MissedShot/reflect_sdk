#include "hooks.hh"

namespace hooks {
    void init() {
        sdl::hook();

        // client mode.
        {
            client_mode::create_move::original = reinterpret_cast<decltype(&client_mode::create_move::hook)>(vmt_hook::hook(interfaces::m_client_mode, reinterpret_cast<void*>(client_mode::create_move::hook), 25));
        }

        // client.
        {
            client::frame_stage_notify::original = reinterpret_cast<decltype(&client::frame_stage_notify::hook)>(vmt_hook::hook(interfaces::m_client, reinterpret_cast<void*>(client::frame_stage_notify::hook), 37));
        }

        // model render.
        {
            model_render::draw_model::original = reinterpret_cast<decltype(&model_render::draw_model::hook)>(vmt_hook::hook(interfaces::m_model_render, reinterpret_cast<void*>(model_render::draw_model::hook), 21));
        }

        // surface.
        {
            surface::paint::original = reinterpret_cast<decltype(&surface::paint::hook)>(vmt_hook::hook(interfaces::m_surface, reinterpret_cast<void*>(surface::paint::hook), 15));
        }
    }

    // TODO; hehe
    void undo() {
        sdl::unhook();
    }
}
#include "../hooks.hh"

void hooks::surface::paint::hook(void* ptr, int mode) {
    original(ptr, mode);

    if (interfaces::m_engine->is_in_game())
        globals::m_matrix = interfaces::m_engine->world_to_screen_matrix();
}
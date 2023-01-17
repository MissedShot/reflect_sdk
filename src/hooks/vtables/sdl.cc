#include "../hooks.hh"
#include "../../menu/menu.hh"

int hooks::sdl::poll_event(SDL_Event* event) {
    const int ret = poll_event_original(event);

    if (render::m_initialized && ret && ImGui_ImplSDL2_ProcessEvent(event) && menu->m_open)
        event->type = SDL_FIRSTEVENT;

    return ret;
}

void hooks::sdl::swap_window(SDL_Window* window) {
    render::init(window);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window);

    ImGuiIO& io = ImGui::GetIO();
    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    io.DisplaySize = ImVec2(static_cast<float>(w), static_cast<float>(h));

    ImGui::NewFrame();
    {
        io.MouseDrawCursor = menu->m_open;
        
        menu->think();

        render::add_to_draw_list();
    }

    if (ImGui::IsKeyPressed(ImGuiKey_Insert, false))
        menu->m_open = !menu->m_open;

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    swap_window_original(window);
}

void hooks::sdl::hook() {
    const auto sdl = dlopen(_("libSDL2-2.0.so.0"), RTLD_LAZY | RTLD_NOLOAD);

    swap_window_address = memory::address_t(dlsym(sdl, _("SDL_GL_SwapWindow"))).self_offset(2).self_rel32(0x0);
    if (!swap_window_address)
        return;

    swap_window_original                                                  = *swap_window_address.cast<decltype(swap_window_original)*>();
    *reinterpret_cast<decltype(swap_window)**>(swap_window_address.m_ptr) = swap_window;

    poll_event_address = memory::address_t(dlsym(sdl, _("SDL_PollEvent"))).self_offset(2).self_rel32(0x0);
    if (!poll_event_address)
        return;

    poll_event_original                                                 = *poll_event_address.cast<decltype(poll_event_original)*>();
    *reinterpret_cast<decltype(poll_event)**>(poll_event_address.m_ptr) = poll_event;

    dlclose(sdl);
}

void hooks::sdl::unhook() {
    if (!swap_window_address || !poll_event_address)
        return;

    *swap_window_address.cast<decltype(swap_window_original)*>() = swap_window_original;
    *poll_event_address.cast<decltype(poll_event_original)*>()   = poll_event_original;
}
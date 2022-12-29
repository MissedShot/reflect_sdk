#pragma once
#include "../globals.hh"
#include "../features/features.hh"

namespace hooks {
    void init();
    void undo();

    namespace client {
        namespace frame_stage_notify {
            void hook(void* ptr, e_client_frame_stage stage);
            inline decltype(&hook) original{};
        }
    }

    namespace client_mode {
        namespace create_move {
            bool hook(void* ptr, float frame_time, c_user_cmd* cmd);
            inline decltype(&hook) original{};
        }
    }

    namespace model_render {
        namespace draw_model {
            void hook(void* ptr, void* ecx, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones);
            inline decltype(&hook) original{};
        }
    }

    namespace surface {
        namespace paint {
            void hook(void* ptr, int mode);
            inline decltype(&hook) original{};
        }
    }

    namespace sdl {
        void hook();
        void unhook();

        int  poll_event(SDL_Event* event);
        void swap_window(SDL_Window* window);

        inline std::add_pointer_t<void(SDL_Window*)> swap_window_original{};
        inline std::add_pointer_t<int(SDL_Event*)> poll_event_original{};
        
        inline memory::address_t swap_window_address;
        inline memory::address_t poll_event_address;
    }
}
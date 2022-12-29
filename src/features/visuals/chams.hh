#pragma once

#include "../../globals.hh"

class c_chams: public c_singleton<c_chams> {
private:
    enum e_material_type {
        MATERIAL_TYPE_REGULAR,
        MATERIAL_TYPE_FLAT
    };

public:
    bool on_draw_model(void* ptr, void* ecx, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones);

private:
    ALWAYS_INLINE void override_material(int type, const col_t& clr, bool ignorez) {
        i_material* material = nullptr;

        switch (type) {
        case MATERIAL_TYPE_REGULAR: material = interfaces::m_material_system->find_material(_("debug/debugambientcube"), 0); break;
        case MATERIAL_TYPE_FLAT:	material = interfaces::m_material_system->find_material(_("debug/debugdrawflat"), 0); break;
        }

        material->set_flag(MATERIAL_VAR_IGNOREZ, ignorez);

        material->alpha_modulate(clr.a() / 255.f);
        material->color_modulate(clr.r() / 255.f, clr.g() / 255.f, clr.b() / 255.f);

        if (const auto $envmaptint = material->find_var(_("$envmaptint"), nullptr, false))
            $envmaptint->set_value(vec3_t(clr.r() / 255.f, clr.g() / 255.f, clr.b() / 255.f));

        interfaces::m_studio_render->forced_material_override(material);
    }
};

#define chams c_chams::instance()
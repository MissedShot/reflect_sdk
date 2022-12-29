#pragma once

class i_studio_render {
public:
    char        pad0[600];
    i_material* m_material_override;
    char        pad1[24];
    int		    m_override_type;

public:
    VFUNC(forced_material_override(i_material* mat = nullptr), 33, void(*)(void*, i_material*, int, int), mat, 0, 0)

    ALWAYS_INLINE bool is_forced_material_override() {
        if (!m_material_override)
            return m_override_type == OVERRIDE_DEPTH_WRITE || m_override_type == OVERRIDE_SSAO_DEPTH_WRITE;

        return std::string_view(m_material_override->get_name()).starts_with(_("dev/glow"));
    }
};
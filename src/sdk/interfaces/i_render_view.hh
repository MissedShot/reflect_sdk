#pragma once

class i_render_view {
public:
    VFUNC(set_blend(float value), 4, void(*)(void*, float), value)
    VFUNC(set_clr(float* value), 6, void(*)(void*, float*), value)
};

class i_view_render {
public:
    char         pad0[8];
    view_setup_t m_view;
};
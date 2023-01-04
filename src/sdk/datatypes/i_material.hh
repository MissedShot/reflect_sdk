#pragma once

class i_material {
public:
	VFUNC(get_name(), 0, const char* (*)(void*))
	VFUNC(get_texture_group_name(), 1, const char* (*)(void*))
	VFUNC(find_var(const char* name, bool* found, bool complain = true), 11, i_material_var*(*)(void*, const char*, bool*, bool), name, found, complain)
	VFUNC(alpha_modulate(float alpha), 27, void(*)(void*, float), alpha)
	VFUNC(color_modulate(float red, float green, float blue), 28, void(*)(void*, float, float, float), red, green, blue)
	VFUNC(set_flag(int flag, bool value), 29, void(*)(void*, int, bool), flag, value)
	VFUNC(is_error_material(), 42, bool(*)(void*))
};
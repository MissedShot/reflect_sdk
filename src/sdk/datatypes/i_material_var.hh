#pragma once

class i_material_var {
public:
	VFUNC(set_value(float value), 4, void(*)(void*, float), value)
	VFUNC(set_value(int value), 5, void(*)(void*, int), value)
	VFUNC(set_value(char const* value), 6, void(*)(void*, char const* ), value)
	VFUNC(set_value(const vec3_t& value), 11, void(*)(void*, float, float, float), value.x, value.y, value.z)
};
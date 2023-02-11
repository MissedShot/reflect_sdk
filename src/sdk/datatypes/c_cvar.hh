#pragma once

using change_callback0_t = void(*)();
using change_callback1_t = void(*)(void*, const char*, float);

class c_cvar {
public:
	VFUNC(set_value(const char* value), 17, void(*)(void*, const char*), value)
	VFUNC(set_value(float value), 18, void(*)(void*, float), value)
	VFUNC(set_value(int value), 19, void(*)(void*, int), value)

	// https://github.com/perilouswithadollarsign/cstrike15_src/blob/master/public/tier1/convar.h#L61-L81
	// maybe replace with VFUNC.
	ALWAYS_INLINE float get_float() {
		const int xored = *reinterpret_cast<int*>(&m_float_value);
		int dexored = static_cast<int>(xored ^ reinterpret_cast<uintptr_t>(this));

		return *reinterpret_cast<float*>(&dexored);
	}

	ALWAYS_INLINE int get_int() {
		const int xored = *reinterpret_cast<int*>(&m_int_value);
		int dexored = static_cast<int>(xored ^ reinterpret_cast<uintptr_t>(this));

		return *reinterpret_cast<int*>(&dexored);
	}

	ALWAYS_INLINE bool get_bool() { return get_int(); }

	char								pad0[8];
	c_cvar* 							m_next;
	bool								m_registered;
	char* 								m_name;
	char* 								m_help_string;
	bit_flag_t<uint32_t>				m_flags;
	change_callback0_t					m_callback;
	c_cvar* 							m_parent;
	char* 								m_default_value;
	char* 								m_string;
	int									m_string_length;
	float								m_float_value;
	int									m_int_value;
	bool								m_has_min;
	float								m_min_value;
	bool								m_has_max;
	float								m_max_value;
	c_utl_vector<change_callback1_t>	m_callbacks;
};
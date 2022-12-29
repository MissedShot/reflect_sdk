#pragma once

class i_cvar_system {
public:
	VFUNC(find_var(const char* name), 15, c_cvar*(*)(void*, const char*), name)
	template <typename... A>
	VFUNC(console_print(const col_t& clr, const char* txt, A... args), 25, void(*)(void*, const col_t&, const char*, ...), clr, txt, args...)
};

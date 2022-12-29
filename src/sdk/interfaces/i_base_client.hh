#pragma once

class i_base_client_dll {
public:
	VFUNC(get_all_classes(), 8, client_class_t*(*)(void*))
	VFUNC(write_user_cmd_delta_to_buffer(int slot, void* buf, int from, int to, bool is_new_cmd), 24, bool(*)(void*, int, void*, int, int, bool), slot, buf, from, to, is_new_cmd)
	VFUNC(dispatch_user_message(int type, int a, int b, void* data), 38, bool(*)(void*, int, int, int, void*), type, a, b, data)
};
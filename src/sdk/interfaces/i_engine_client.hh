#pragma once

class i_engine_client {
public:
	VFUNC(get_screen_size(int& width, int& height), 5, void(*)(void*, int& width, int& height), width, height)
	VFUNC(get_player_info(int index, player_info_t* info), 8, void(*)(void*, int, player_info_t*), index, info)
	VFUNC(get_player_for_user_id(int id), 9, int(*)(void*, int), id)
	VFUNC(get_local_player(), 12, int(*)(void*))
	VFUNC(get_last_time_stamp(), 14, float(*)(void*))
	VFUNC(get_view_angles(qangle_t& view_angles), 18, void(*)(void*, qangle_t&), view_angles)
	VFUNC(set_view_angles(qangle_t& view_angles), 19, void(*)(void*, qangle_t&), view_angles)
	VFUNC(get_max_clients(), 20, bool(*)(void*))
	VFUNC(is_in_game(), 26, bool(*)(void*))
	VFUNC(is_connected(), 27, bool(*)(void*))
	VFUNC(is_drawing_loading_image(), 28, bool(*)(void*))
	VFUNC(world_to_screen_matrix(), 37, const v_matrix&(*)(void*))
	VFUNC(get_bsp_tree_query(), 43, uintptr_t*(*)(void*))
	VFUNC(get_level_name(), 52, const char*(*)(void*))
	VFUNC(get_level_name_short(), 53, const char* (*)(void*))
	VFUNC(fire_events(), 59, void(*)(void*))
	VFUNC(get_net_channel_info(), 78, void* (*)(void*))
	VFUNC(is_playing_demo(), 82, bool(*)(void*))
	VFUNC(is_recording_demo(), 83, bool(*)(void*))
	VFUNC(is_playing_time_demo(), 84, bool(*)(void*))
	VFUNC(is_paused(), 90, bool(*)(void*))
	VFUNC(is_taking_screenshot(), 92, bool(*)(void*))
	VFUNC(is_hltv(), 93, bool(*)(void*))
	VFUNC(get_engine_build_number(), 104, uintptr_t*(*)(void*))
	VFUNC(client_cmd(const char* cmd), 108, void(*)(void*, const char*), cmd)
	VFUNC(client_cmd_unrestricted(const char* cmd, bool unk = false), 114, void(*)(void*, const char*, bool), cmd, unk)
	VFUNC(is_voice_recording(), 224, bool(*)(void*))
};
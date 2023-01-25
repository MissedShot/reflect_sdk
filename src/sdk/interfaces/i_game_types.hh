#pragma once

class i_game_types {
public:
    VFUNC(get_cur_game_type(), 9, int(*)(void*))
    VFUNC(get_cur_game_mode(), 10, int(*)(void*))
    VFUNC(get_cur_map_name(), 11, const char* (*)(void*))
    VFUNC(get_cur_game_type_name_id(), 12, const char* (*)(void*))
    VFUNC(get_cur_game_mode_name_id(), 13, const char* (*)(void*))
};
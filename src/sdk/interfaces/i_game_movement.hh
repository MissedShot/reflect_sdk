#pragma once

class c_base_player;

class i_game_movement {
public:
    VFUNC(process_movement(c_base_player* player, move_data_t* move_data), 2, void(*)(void*, c_base_player*, move_data_t*), player, move_data)
    VFUNC(reset(), 3, void(*)(void*))
    VFUNC(start_track_prediction_errors(c_base_player* player), 4, void(*)(void*, c_base_player*), player)
    VFUNC(finish_track_prediction_errors(c_base_player* player), 5, void(*)(void*, c_base_player*), player)
};
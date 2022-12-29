#pragma once

class i_engine_trace {
public:
	VFUNC(get_point_contents(const vec3_t& pos, bit_flag_t<int> mask = MASK_ALL, i_handle_entity** entity = 0), 0, int(*)(void*, const vec3_t&, bit_flag_t<int>, i_handle_entity**), pos, mask, entity)
	VFUNC(get_point_contents_world_only(const vec3_t& pos, bit_flag_t<int> mask = MASK_ALL), 1, int(*)(void*, const vec3_t&, bit_flag_t<int>), pos, mask)
	VFUNC(get_point_contents_collideable(void* collideable, const vec3_t& pos), 2, int(*)(void*, void*, const vec3_t&), collideable, pos)
	VFUNC(clip_ray_to_entity(const ray_t& ray, bit_flag_t<uint32_t> mask, i_handle_entity* entity, c_game_trace* trace), 3, void(*)(void*, const ray_t&, bit_flag_t<uint32_t>, i_handle_entity*, c_game_trace*), ray, mask, entity, trace)
	VFUNC(clip_ray_to_collideable(const ray_t& ray, bit_flag_t<uint32_t> mask, void* collideable, c_game_trace* trace), 4, void(*)(void*, const ray_t&, bit_flag_t<uint32_t>, void*, c_game_trace*), ray, mask, collideable, trace)
	VFUNC(trace_ray(const ray_t& ray, bit_flag_t<uint32_t> mask, i_trace_filter* filter, c_game_trace* trace), 5, void(*)(void*, const ray_t&, bit_flag_t<uint32_t>, i_trace_filter*, c_game_trace*), ray, mask, filter, trace)
};
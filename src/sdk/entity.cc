#include "entity.hh"
#include "../globals.hh"

player_info_t c_cs_player::get_info() {
	auto ret = player_info_t();

	interfaces::m_engine->get_player_info(get_index(), &ret);

	return ret;
}

vec3_t c_cs_player::get_bone_pos(int bone) {
	matrix3x4_t bone_matrix[128]{};

	if (!setup_bones(bone_matrix, 128, BONE_FLAG_USED_BY_ANYTHING, 0.f))
		return {};

	return bone_matrix[bone].origin();
}

bool c_cs_player::is_enemy(c_cs_player* from) {
	if (this == from)
		return false;

	if (interfaces::m_game_types->get_cur_game_type() == GAME_TYPE_FREEFORALL)
		return get_survival_team() != from->get_survival_team();

	static const auto mp_teammates_are_enemies = interfaces::m_cvar_system->find_var(_("mp_teammates_are_enemies"));
	if (mp_teammates_are_enemies->get_int())
		return true;

	return get_team() != from->get_team();
}

bool c_cs_player::is_visible(c_cs_player* from, const vec3_t pos, const bool smoke) {
	c_game_trace tr{};
	c_trace_filter filter(from);

	const vec3_t eye_pos = from->get_eye_pos();

	static const auto is_line_goes_through_smoke = SIG("/client_client.so", "55 48 89 E5 41 56 41 55 41 54 53 48 83 EC 30 8B 05 CB 71 E2").cast<bool(*)(vec3_t, vec3_t)>();
	if (smoke && is_line_goes_through_smoke(eye_pos, pos))
		return false;

	interfaces::m_trace_system->trace_ray(ray_t(eye_pos, pos), MASK_SHOT | CONTENTS_GRATE, &filter, &tr);

	return tr.m_hit_entity == this || tr.is_visible();
}

c_base_combat_weapon* c_base_combat_character::get_active_weapon() {
	const auto handle = get_active_weapon_handle();
	if (!handle.is_valid())
		return nullptr;

	return reinterpret_cast<c_base_combat_weapon*>(handle.get());
}

std::wstring c_base_combat_weapon::get_name() {
	const auto weapon_data = get_cs_weapon_data();
	if (!weapon_data)
		return L"";

	return interfaces::m_localize->find_safe(weapon_data->m_name);
}
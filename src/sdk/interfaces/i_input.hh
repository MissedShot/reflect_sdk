#pragma once

class c_user_cmd {
public:
	virtual	~c_user_cmd() = default;

	int						m_command_number;
	int						m_tick_count;
	qangle_t				m_view_angles;
	vec3_t					m_aim_direction;
	vec3_t					m_move;
	bit_flag_t<uint32_t>	m_buttons;
	char					m_impulse;
	int						m_weapon_select;
	int						m_weapon_sub_type;
	int						m_random_seed;
	short					m_mouse_dx;
	short					m_mouse_dy;
	bool					m_predicted;
	char					pad0[24];
};
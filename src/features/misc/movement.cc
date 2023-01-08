#include "../features.hh"

void c_movement::jump_related() {
	if (!g_settings.m_misc.m_bhop)
		return;

	if (!globals::m_local->is_alive())
		return;

	if (globals::m_local->get_move_type() == MOVE_TYPE_LADDER || globals::m_local->get_move_type() == MOVE_TYPE_NOCLIP)
		return;

	if (!m_jumped_last_tick && m_should_fake_jump) {
		m_should_fake_jump = false;
		globals::m_cmd->m_buttons.add(IN_JUMP);
	}

	else if (globals::m_cmd->m_buttons.has(IN_JUMP)) {
		if (globals::m_local->get_flags().has(FL_ONGROUND)) {
			m_jumped_last_tick = true;
			m_should_fake_jump = true;
		}

		else {
			globals::m_cmd->m_buttons.remove(IN_JUMP);
			m_jumped_last_tick = false;
		}
	}

	else {
		m_jumped_last_tick = false;
		m_should_fake_jump = false;
	}
}
#pragma once

#include "../../globals.hh"

class c_movement : public c_singleton<c_movement> {
public:
    void jump_related();

private:
	bool m_jumped_last_tick{};
	bool m_should_fake_jump{};
};

#define movement c_movement::instance()
#pragma once

#include "../globals.hh"
#include "../utils/config/config.hh"

class c_menu: public c_singleton<c_menu> {
public:
	void think();

public:
	bool        m_open{};
	ImGuiStyle  m_style{};
};

#define menu c_menu::instance()
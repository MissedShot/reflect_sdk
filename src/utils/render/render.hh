#pragma once
#include "deps/tinyformat.hh"

class c_base_entity;

enum e_font_flags {
	FONT_NONE,
	FONT_CENTERED_X  = 1 << 0,
	FONT_CENTERED_Y  = 1 << 1,
	FONT_CENTERED 	 = FONT_CENTERED_X | FONT_CENTERED_Y,
	FONT_LEFT 		 = 1 << 2,
	FONT_RIGHT 		 = 1 << 3,
	FONT_DROP_SHADOW = 1 << 4,
	FONT_OUTLINE 	 = 1 << 5
};

namespace render {
	class c_lock {
	public:
		c_lock() noexcept: m_lock{ m_mutex } {}
		
	private:
		std::scoped_lock<std::mutex> m_lock;
		static inline std::mutex m_mutex;
	};

	void init(SDL_Window* window);

	void add_to_draw_list();

	vec2_t get_text_size(std::string_view txt, ImFont* font);

	void text(std::string_view txt, vec2_t pos, const col_t& clr, ImFont* font, bit_flag_t<uint8_t> flags = FONT_NONE);

	void line(const vec2_t& from, const vec2_t& to, const col_t& clr);

	void rect(const vec2_t& pos, const vec2_t& size, const col_t& clr, float rounding = 0.f);

	void rect_outlined(const vec2_t& pos, const vec2_t& size, const col_t& clr, const col_t& clr2);

	void rect_filled(const vec2_t& pos, const vec2_t& size, const col_t& clr, float rounding = 0.f);

	void rect_filled_multi_clr(const vec2_t& pos, const vec2_t& size, const col_t& clr_upr_left, const col_t& clr_upr_right, const col_t& clr_bot_left, const col_t& clr_bot_right);

	void polygon(const std::vector<vec2_t>& points, const col_t& clr);

	void polygon_filled(const std::vector<vec2_t>& points, const col_t& clr);

	bool get_entity_bbox(c_base_entity* ent, vec2_t& pos, vec2_t& size);

	extern vec2_t m_screen_size;

	extern ImDrawList* m_draw_list;

	extern bool m_initialized;
}

namespace fonts {
	extern ImFont* m_liberation14;
}

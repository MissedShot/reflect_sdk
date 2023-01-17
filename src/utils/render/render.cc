#include "../utils.hh"
#include "../../sdk/interfaces.hh"
#include "../../features/features.hh"

#include "deps/liberation.hh"

namespace render {
	void init(SDL_Window* window) {
		if (m_initialized)
			return;

		ImGui::CreateContext();

		ImGui_ImplSDL2_InitForOpenGL(window, nullptr);
		ImGui_ImplOpenGL3_Init();

		ImGuiIO& io = ImGui::GetIO();
		io.Fonts->AddFontFromMemoryCompressedTTF(LiberationSans_compressed_data, LiberationSans_compressed_size, 14.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

		fonts::m_liberation14 = io.Fonts->AddFontFromMemoryCompressedTTF(LiberationSans_compressed_data, LiberationSans_compressed_size, 14.0f, nullptr, io.Fonts->GetGlyphRangesCyrillic());

		m_initialized = true;
	}
	
	vec2_t get_text_size(std::string_view txt, ImFont* font) {
		if (!font || txt.empty() || !font->IsLoaded())
			return vec2_t();

		const auto size = font->CalcTextSizeA(font->FontSize, std::numeric_limits<float>::max(), 0.f, txt.data());

		return vec2_t(IM_FLOOR(size.x + 0.95f), size.y);
	}

	void text(std::string_view txt, vec2_t pos, const col_t& clr, ImFont* font, bit_flag_t<uint8_t> flags) {
		if (!font || txt.empty() || clr.a() <= 0 || !font->IsLoaded())
			return;

		const auto centered_x   = flags.has(FONT_CENTERED_X);
		const auto centered_y   = flags.has(FONT_CENTERED_Y);
		const auto right 		= flags.has(FONT_RIGHT);
		const auto left 		= flags.has(FONT_LEFT);

		if (centered_x || centered_y || right || left) {
			const vec2_t text_size = get_text_size(txt, font);

			if (centered_x)
				pos.x -= text_size.x / 2.f;

			if (centered_y)
				pos.y -= text_size.y / 2.f;

			if (right)
				pos.x -= text_size.x;

			if (left)
				pos.y -= text_size.y;
		}

		m_draw_list->PushTextureID(font->ContainerAtlas->TexID);

		m_draw_list->AddText(font, font->FontSize, *reinterpret_cast<ImVec2*>(&pos), clr.hex(), txt.data());

		m_draw_list->PopTextureID();
	}

	void line(const vec2_t& from, const vec2_t& to, const col_t& clr) {
		m_draw_list->AddLine(*reinterpret_cast<const ImVec2*>(&from), *reinterpret_cast<const ImVec2*>(&to), clr.hex());
	}

	void rect(const vec2_t& pos, const vec2_t& size, const col_t& clr, float rounding) {
		m_draw_list->AddRect(*reinterpret_cast<const ImVec2*>(&pos), ImVec2(pos.x + size.x, pos.y + size.y), clr.hex(), rounding);
	}

	void rect_outlined(const vec2_t& pos, const vec2_t& size, const col_t& clr, const col_t& clr2) {
		rect(pos, size, clr);
		rect(vec2_t(pos.x + 1.f, pos.y + 1.f), vec2_t(size.x - 2.f, size.y - 2.f), clr2);
		rect(vec2_t(pos.x - 1.f, pos.y - 1.f), vec2_t(size.x + 2.f, size.y + 2.f), clr2);
	}

	void rect_filled(const vec2_t& pos, const vec2_t& size, const col_t& clr, float rounding) {
		m_draw_list->AddRectFilled(*reinterpret_cast<const ImVec2*>(&pos), ImVec2(pos.x + size.x, pos.y + size.y), clr.hex(), rounding);
	}

	void rect_filled_multi_clr(const vec2_t& pos, const vec2_t& size, const col_t& clr_upr_left, const col_t& clr_upr_right, const col_t& clr_bot_left, const col_t& clr_bot_right) {
		m_draw_list->AddRectFilledMultiColor(*reinterpret_cast<const ImVec2*>(&pos), ImVec2(pos.x + size.x, pos.y + size.y), clr_upr_left.hex(), clr_upr_right.hex(), clr_bot_right.hex(), clr_bot_left.hex());
	}

	void add_to_draw_list() {
		m_draw_list = ImGui::GetBackgroundDrawList();

		ImGuiIO& io = ImGui::GetIO();

		m_screen_size.x = io.DisplaySize.x;
		m_screen_size.y = io.DisplaySize.y;

		c_lock lock;

		/* render stuff here
		only render, store data for render must be in another place
		FRAME_RENDER_START in FrameStageNotify hook for example

		TODO; find a workaround with ImGui::DrawList override
		and add an example esp
		*/
	}

	void polygon(const std::vector<vec2_t>& points, const col_t& clr) {
		if (clr.a() <= 0)
			return;

		m_draw_list->_Path.reserve(m_draw_list->_Path.Size + points.size() + 1);

		for (auto& point : points)
			m_draw_list->_Path.push_back(*reinterpret_cast<const ImVec2*>(&point));

		m_draw_list->PathStroke(clr.hex(), true, 1.f);
	}

	void polygon_filled(const std::vector<vec2_t>& points, const col_t& clr) {
		if (clr.a() <= 0)
			return;

		m_draw_list->_Path.reserve(m_draw_list->_Path.Size + points.size() + 1);

		for (auto& point : points)
			m_draw_list->_Path.push_back(*reinterpret_cast<const ImVec2*>(&point));

		m_draw_list->PathFillConvex(clr.hex());
	}

	bool get_entity_bbox(c_base_entity* ent, vec2_t& pos, vec2_t& size) {
		static const auto compute_hitbox_surrounding_box = SIG("/client_client.so", "E9 ? ? ? ? 0F 1F 80 00 00 00 00 5B 31 C0 41 5C 5D C3 90 55").self_rel32().cast<bool(*)(void*, vec3_t*, vec3_t*)>();

		vec3_t mins{}, maxs{};
		compute_hitbox_surrounding_box(ent, &mins, &maxs);

		vec3_t origin = ent->get_origin();
		mins = vec3_t(origin.x, origin.y, mins.z);
		maxs = vec3_t(origin.x, origin.y, maxs.z + 8.f);

		vec2_t bottom{}, top{};
		if (!mins.to_screen(bottom) || !maxs.to_screen(top))
			return false;

		if (!bottom.is_valid() || !top.is_valid())
			return false;

		size.y = bottom.y - top.y;
		size.x = size.y / 2.f;
		pos.x  = bottom.x - (size.x / 2.f);
		pos.y  = bottom.y - size.y;

		return true;
	}

	vec2_t m_screen_size{};

	ImDrawList* m_draw_list{};

	bool m_initialized{};
}

namespace fonts {
	ImFont* m_liberation14 = nullptr;
}

#include "menu.hh"
#include "../features/features.hh"

void ColorEditColor(const char* label, col_t* color, ImGuiColorEditFlags flags = 0) {
	float col[4] = {
		static_cast<float>((*color).r()) / 255.f,
		static_cast<float>((*color).g()) / 255.f,
		static_cast<float>((*color).b()) / 255.f,
		static_cast<float>((*color).a()) / 255.f
	};

	ImGui::ColorEdit4(label, col, flags);

	color->set(col[0] * 255, col[1] * 255, col[2] * 255, col[3] * 255);
}

void c_menu::think() {
	if (!m_open)
		return;

	ImGui::SetNextWindowPos(ImGui::GetIO().DisplaySize / 2.f, ImGuiCond_Once, ImVec2(.5f, .5f));
	ImGui::SetNextWindowSize(ImVec2(600.f, 400.f), ImGuiCond_Once);

	if (ImGui::Begin(_("reflect sdk [linux]"), 0, ImGuiWindowFlags_NoCollapse)) {
		ImGui::Checkbox(_("Chams player"), &g_settings.m_visuals.m_chams.m_player);
		ImGui::Checkbox(_("Chams XQZ"), &g_settings.m_visuals.m_chams.m_invisible);
		
		ImGui::Combo(_("Chams material##ChamsPlayer"), &g_settings.m_visuals.m_chams.m_material, _("Regular\0Flat\0\0"));
		
		ColorEditColor(_("Visible"), &g_settings.m_colors.m_chams.m_visible);
		ColorEditColor(_("Invisible"), &g_settings.m_colors.m_chams.m_invisible);
		
		ImGui::Checkbox(_("Bhop"), &g_settings.m_misc.m_bhop);

		if (ImGui::Button(_("save")))
			config::save(_("Default"));

		if (ImGui::Button(_("load")))
			config::load(_("Default"));

		ImGui::End();
	}
}
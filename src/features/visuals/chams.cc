#include "chams.hh"
#include "../../hooks/hooks.hh"

bool c_chams::on_draw_model(void* ptr, void* ecx, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones) {
	if (!globals::m_local || !info.m_renderable)
		return true;

	const bool is_player = strstr(info.m_model->m_name, _("models/player"));

	if (is_player) {
		const auto player = reinterpret_cast<c_cs_player*>(interfaces::m_entity_list->get_client_entity(info.m_index));
		if (!player)
			return true;

		if (player->is_enemy(globals::m_local)) {
			if (player->is_alive() && g_settings.m_visuals.m_chams.m_player) {
				
				if (g_settings.m_visuals.m_chams.m_invisible) {
					override_material(g_settings.m_visuals.m_chams.m_material, g_settings.m_colors.m_chams.m_invisible, true);

					hooks::model_render::draw_model::original(ptr, ecx, state, info, bones);
				}

				override_material(g_settings.m_visuals.m_chams.m_material, g_settings.m_colors.m_chams.m_visible, false);

				return true;
			}
		}	
	}
	
	return true;
}
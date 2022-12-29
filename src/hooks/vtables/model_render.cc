#include "../hooks.hh"

void hooks::model_render::draw_model::hook(void* ptr, void* ecx, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones) {
	if (interfaces::m_studio_render->is_forced_material_override())
		return original(ptr, ecx, state, info, bones);

	if (chams->on_draw_model(ptr, ecx, state, info, bones))
		original(ptr, ecx, state, info, bones);

	interfaces::m_studio_render->forced_material_override();
}
#pragma once

struct model_t {
	char			pad0[8];
	char			m_name[260];
	int				m_load_flags;
	int				m_server_count;
	int				m_type;
	int				m_flags;
	vec3_t			m_mins;
	vec3_t			m_maxs;
	float			m_radius;
	void*	        m_key_values;
	char			pad1[24];
};

struct model_render_info_t {
	vec3_t					m_origin;
	qangle_t				m_angles;
	char					pad[4];
	i_client_renderable* 	m_renderable;
	const model_t*			m_model;
	const matrix3x4_t*		m_model_to_world;
	const matrix3x4_t*		m_lighting_offset;
	const vec3_t*			m_lighting_origin;
	bit_flag_t<int>			m_flags;
	int						m_index;
	int						m_skin;
	int						m_body;
	int						m_hitboxset;
	uint16_t				m_instance;
};

struct renderable_info_t {
	i_client_renderable* 	 m_renderable;
	i_client_alpha_property* m_alpha_property;
	int						 m_enum_count;
	int						 m_render_frame;
	unsigned short			 m_first_shadow;
	unsigned short			 m_leaf_list;
	short					 m_area;
	bit_flag_t<int>			 m_flags;
	bit_flag_t<int>			 m_flags2;
	vec3_t					 m_bloated_abs_mins;
	vec3_t					 m_bloated_abs_maxs;
	vec3_t					 m_abs_mins;
	vec3_t					 m_abs_maxs;
	char 					 pad0[0x4];
};

struct studiohwdata_t;

struct draw_model_state_t {
	studiohdr_t* 			m_studio_hdr;
	studiohwdata_t*			m_studio_hw_data;
	i_client_renderable* 	m_renderable;
	const matrix3x4_t*		m_bones;
};

class i_model_render {
public:
	VFUNC(forced_material_override(i_material* material = nullptr, e_override_type type = OVERRIDE_NORMAL), 1, void(*)(void*, i_material*, e_override_type, int), material, type, 0)
	VFUNC(is_forced_material_override(), 2, bool(*)(void*))
	VFUNC(draw_model_execute(void* context, const draw_model_state_t& state, const model_render_info_t& info, matrix3x4_t* bones), 21, void(*)(void*, void*, const draw_model_state_t&, const model_render_info_t&, matrix3x4_t*), context, state, info, bones)
};
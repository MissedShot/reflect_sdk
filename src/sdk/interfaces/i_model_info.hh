#pragma once

class studiohdr_t {
public:
	int						m_id;
	int						m_version;
	long					m_checksum;
	char					m_name[64];
	int						m_length;
	vec3_t					m_eye_pos;
	vec3_t					m_illum_pos;
	vec3_t					m_hull_min;
	vec3_t					m_hull_max;
	vec3_t					m_obb_min;
	vec3_t					m_obb_max;
	bit_flag_t<uint32_t>	m_flags;
	int						m_bones_count;
	int						m_bone_index;
	int						m_bone_controllers_count;
	int						m_bone_controller_index;
	int						m_hitbox_sets_count;
	int						m_hitbox_set_index;
	int						m_local_anim_count;
	int						m_local_anim_index;
	int						m_local_seq_count;
	int						m_local_seq_index;
	int						m_activity_list_version;
	int						m_events_indexed;
	int						m_textures_count;
	int						m_texture_index;
	int						m_cd_textures_count;
	int						m_cd_texture_index;
	int						m_skin_ref_count;
	int						m_skin_families_count;
	int						m_skin_index;
	int						m_body_parts_count;
	int						m_body_part_index;
	int						m_local_attachments_count;
	int						m_local_attachment_index;
	int						m_local_nodes_count;
	int						m_local_node_index;
	int						m_local_node_name_index;
	int						m_flex_desc_count;
	int						m_flex_desc_index;
	int						m_flex_controllers_count;
	int						m_flex_controller_index;
	int						m_flex_rules_count;
	int						m_flex_rule_index;
	int						m_ik_chains_count;
	int						m_ik_chain_index;
	int						m_mouths_count;
	int						m_mouth_index;
	int						m_local_pose_parameters_count;
	int						m_local_pose_param_index;
	int						m_surface_prop_index;
	int						m_key_value_index;
	int						m_key_value_size;
	int						m_local_ik_auto_play_locks_count;
	int						m_local_ik_auto_play_lock_index;
	float					m_mass;
	int						m_contents;
	int						m_include_models_count;
	int						m_include_model_index;
	mutable void* 			m_virtual_model;
	int						m_anim_block_name_index;
	int						m_anim_blocks_count;
	int						m_anim_block_index;
	mutable void* 			m_anim_block_model;
	int						m_bone_table_by_name_index;
	void* 					m_vertex_base;
	void* 					m_index_base;
	uint8_t					m_const_directional_light_dot;
	uint8_t					m_root_lod;
	uint8_t					m_allowed_root_lods_count;
	char                    pad0[5];
	int						m_flex_controller_ui_count;
	int						m_flex_controller_ui_index;
	float					m_vert_anim_fixed_point_scale;
	mutable int				m_surface_prop_lookup;
	int						m_studio_hdr_index;
	char                    pad1[4];
};

class i_model_info {
public:
	VFUNC(get_model(int index), 2, model_t* (*)(void*, int), index)
	VFUNC(get_model_index(const char* name), 3, int(*)(void*, const char*), name)
	VFUNC(get_model_name(const model_t* model), 4, const char* (*)(void*, const model_t*), model)
	VFUNC(get_studio_model(const model_t* model), 31, studiohdr_t* (*)(void*, const model_t*), model)
};
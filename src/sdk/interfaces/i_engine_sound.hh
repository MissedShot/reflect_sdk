#pragma once

struct sound_info_t {
	int		m_guid;
	void*	m_filename_handle;
	int		m_sound_source;
	int		m_channel;
	int		m_speaker_entity;
	float	m_volume;
	float	m_last_spatialized_volume;
	float	m_radius;
	int		m_pitch;
	vec3_t* m_origin;
	vec3_t* m_direction;
	bool	m_update_positions;
	bool	m_is_sentence;
	bool	m_dry;
	bool	m_speaker;
	bool	m_special;
	bool	m_from_server;
};

class i_engine_sound {
public:
	VFUNC(emit_sound(const char* sample, float volume, int pitch = PITCH_NORM, int flags = 0, float time = 0.f), 6, void(*)(void*, const char*, float, int, int, float), sample, volume, pitch, flags, time)
	VFUNC(get_active_sounds(sound_info_t& list), 20, void(*)(void*, sound_info_t&), list)
};
#pragma once

struct vec3_t;
struct qangle_t;
namespace math {
	constexpr auto m_pi = 3.14159265358979323846f;
	constexpr auto m_rad_pi = 180.f / m_pi;
	constexpr auto m_deg_pi = m_pi / 180.f;
	constexpr auto m_round_error = std::numeric_limits<double>::round_error();

	void 	sin_cos(float rad, float& sin, float& cos);
	float 	get_fov(const qangle_t& view_angles, const vec3_t& start, const vec3_t& end);
	int 	random_int(int min, int max);
    float 	random_float(float min, float max);

	ALWAYS_INLINE float rad_to_deg(float rad) { return rad * m_rad_pi; }

	ALWAYS_INLINE float deg_to_rad(float deg) { return deg * m_deg_pi; }
}
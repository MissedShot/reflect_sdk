#include "../utils.hh"

namespace math {
	void sin_cos(float rad, float& sin, float& cos) {
		sin = std::sin(rad);
		cos = std::cos(rad);
	}

	float get_fov(const qangle_t& view_angles, const vec3_t& start, const vec3_t& end) {
		vec3_t dir = (end - start).normalized();

		return std::max(rad_to_deg(acos(view_angles.vector().dot_product(dir))), 0.f);
	}

	int random_int(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }

    float random_float(float min, float max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(min, max);
        return dis(gen);
    }
}
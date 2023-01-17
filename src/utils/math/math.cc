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
        // load vstdlib handle and validate it.
        const auto vstdlib = dlopen(_("libvstdlib_client.so"), RTLD_LAZY | RTLD_NOLOAD);
        if (!vstdlib) {
            dlclose(vstdlib);
            return 0;
        }

        // get RandomInt func from handle.
        const auto random = reinterpret_cast<int(*)(int min, int max)>(dlsym(vstdlib, _("RandomInt")));

        // close vstdlib handle.
        dlclose(vstdlib);

        // return what we get.
        return random(min, max);
    }

    float random_float(float min, float max) {
        // load vstdlib handle and validate it.
        const auto vstdlib = dlopen(_("libvstdlib_client.so"), RTLD_LAZY | RTLD_NOLOAD);
        if (!vstdlib) {
            dlclose(vstdlib);
            return 0.f;
        }

        // get RandomFloat func from handle.
        const auto random = reinterpret_cast<float(*)(float min, float max)>(dlsym(vstdlib, _("RandomFloat")));

        // close vstdlib handle.
        dlclose(vstdlib);

        // return what we get.
        return random(min, max);
    }
}
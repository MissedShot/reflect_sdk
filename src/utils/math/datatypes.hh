#pragma once

struct vec2_t {
	vec2_t() = default;
	vec2_t(float ix, float iy) {
		x = ix;
		y = iy;
	}

	float x = 0.f, y = 0.f;

	ALWAYS_INLINE vec2_t operator+(const vec2_t& value) const { return vec2_t(x + value.x, y + value.y); }

	ALWAYS_INLINE vec2_t operator-(const vec2_t& value) const { return vec2_t(x - value.x, y - value.y); }

	ALWAYS_INLINE vec2_t operator+(float value) const { return vec2_t(x + value, y + value); }

	ALWAYS_INLINE vec2_t operator-(float value) const { return vec2_t(x - value, y - value); }

	ALWAYS_INLINE vec2_t operator/(float value) const { return vec2_t(x / value, y / value); }

	ALWAYS_INLINE vec2_t operator*(float value) const { return vec2_t(x * value, y * value); }

	ALWAYS_INLINE vec2_t operator-() const { return vec2_t(-x, -y); }

	ALWAYS_INLINE vec2_t& operator-=(const vec2_t& value) {
		x -= value.x;
		y -= value.y;

		return *this;
	}

	ALWAYS_INLINE vec2_t& operator+=(const vec2_t& value) {
		x += value.x;
		y += value.y;

		return *this;
	}

	ALWAYS_INLINE vec2_t& operator/=(float value) {
		x /= value;
		y /= value;

		return *this;
	}

	ALWAYS_INLINE vec2_t& operator*=(float value) {
		x *= value;
		y *= value;

		return *this;
	}

	ALWAYS_INLINE vec2_t& normalize() {
		if (const auto l = length()) {
			x /= l;
			y /= l;
		}

		return *this;
	}

	ALWAYS_INLINE vec2_t normalized() const {
		auto ret = *this;

		return ret.normalize();
	}

	ALWAYS_INLINE bool operator==(const vec2_t& value) const { return x == value.x && y == value.y; }

	ALWAYS_INLINE bool operator!=(const vec2_t& value) const { return !(operator==(value)); }

	ALWAYS_INLINE float length_sqr() const { return x * x + y * y; }

	ALWAYS_INLINE float length() const { return std::sqrt(length_sqr()); }

	ALWAYS_INLINE float dot_product(const vec2_t& value) const { return x * value.x + y * value.y; }

	ALWAYS_INLINE float dot_product(const float* value) const { return x * value[0] + y * value[1]; }

	ALWAYS_INLINE float dist_to(const vec2_t& value) const { return (*this - value).length(); }

	ALWAYS_INLINE bool is_valid() const { return std::isfinite(x) && std::isfinite(y); }

	ALWAYS_INLINE bool empty() const { return x == 0.f && y == 0.f; }
};

struct qangle_t;
struct matrix3x4_t;

struct vec3_t {
	vec3_t() = default;
	vec3_t(float ix, float iy, float iz) {
		x = ix;
		y = iy;
		z = iz;
	}

	float x = 0.f, y = 0.f, z = 0.f;

	ALWAYS_INLINE vec3_t operator+(const vec3_t& value) const { return vec3_t(x + value.x, y + value.y, z + value.z); }

	ALWAYS_INLINE vec3_t operator-(const vec3_t& value) const { return vec3_t(x - value.x, y - value.y, z - value.z); }

	ALWAYS_INLINE vec3_t operator-(float value) const { return vec3_t(x - value, y - value, z - value); }

	ALWAYS_INLINE vec3_t operator+(float value) const { return vec3_t(x + value, y + value, z + value); }

	ALWAYS_INLINE vec3_t operator/(float value) const { return vec3_t(x / value, y / value, z / value); }

	ALWAYS_INLINE vec3_t operator*(float value) const { return vec3_t(x * value, y * value, z * value); }

	ALWAYS_INLINE vec3_t operator-() const { return vec3_t(-x, -y, -z); }

	ALWAYS_INLINE vec3_t& operator-=(const vec3_t& value) {
		x -= value.x;
		y -= value.y;
		z -= value.z;

		return *this;
	}

	ALWAYS_INLINE vec3_t& operator+=(const vec3_t& value) {
		x += value.x;
		y += value.y;
		z += value.z;

		return *this;
	}

	ALWAYS_INLINE vec3_t& operator/=(const vec3_t& value) {
		x /= value.x;
		y /= value.y;
		z /= value.z;

		return *this;
	}

	ALWAYS_INLINE vec3_t& operator*=(const vec3_t& value) {
		x *= value.x;
		y *= value.y;
		z *= value.z;

		return *this;
	}

	ALWAYS_INLINE vec3_t& operator/=(float value) {
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}

	ALWAYS_INLINE vec3_t& operator*=(float value) {
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	ALWAYS_INLINE vec3_t& normalize() {
		if (const auto l = length()) {
			x /= l;
			y /= l;
			z /= l;
		}

		return *this;
	}

	ALWAYS_INLINE vec3_t normalized() const {
		auto ret = *this;

		return ret.normalize();
	}

	ALWAYS_INLINE bool operator==(const vec3_t& value) const { return x == value.x && y == value.y && z == value.z; }

	ALWAYS_INLINE bool operator!=(const vec3_t& value) const { return !(operator==(value)); }

	ALWAYS_INLINE float& operator[](int i) { return reinterpret_cast<float*>(this)[i]; }

	ALWAYS_INLINE float operator[](int i) const { return reinterpret_cast<const float*>(this)[i]; }

	ALWAYS_INLINE float length_sqr() const { return x * x + y * y + z * z; }

	ALWAYS_INLINE float length() const { return std::sqrt(length_sqr()); }

	ALWAYS_INLINE float length_2d() const { return std::sqrt(x * x + y * y); }

	ALWAYS_INLINE float dot_product(const vec3_t& value) const { return x * value.x + y * value.y + z * value.z; }

	ALWAYS_INLINE float dot_product(const float* value) const { return x * value[0] + y * value[1] + z * value[2]; }

	ALWAYS_INLINE vec3_t cross_product(const vec3_t& value) const { return vec3_t(y * value.z - z * value.y, z * value.x - x * value.z, x * value.y - y * value.x); }

	vec3_t transform(const matrix3x4_t& value) const;

	vec3_t i_transform(const matrix3x4_t& value) const;

	vec3_t rotate(const matrix3x4_t& value) const;

	vec3_t i_rotate(const matrix3x4_t& value) const;

	qangle_t angle() const;

	qangle_t angle(const vec3_t& up) const;

	bool to_screen(vec2_t& value) const;

	ALWAYS_INLINE float dist_to(const vec3_t& value) const { return (*this - value).length(); }

	ALWAYS_INLINE float dist_to_2d(const vec3_t& value) const { return (*this - value).length_2d(); }

	ALWAYS_INLINE bool is_valid() const { return std::isfinite(x) && std::isfinite(y) && std::isfinite(z); }

	ALWAYS_INLINE bool empty() const { return x == 0.f && y == 0.f && z == 0.f; }
};

struct vec4_t : public vec3_t {
	vec4_t() = default;
	vec4_t(float ix, float iy, float iz, float iw) {
		x = ix;
		y = iy;
		z = iz;
		w = iw;
	}
	vec4_t(const vec3_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;
	}
	vec4_t(const vec2_t& value0, const vec2_t& value1) {
		x = value0.x;
		y = value0.y;
		z = value1.x;
		w = value1.y;
	}

	ALWAYS_INLINE vec4_t& operator=(const vec3_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;

		return *this;
	}

	ALWAYS_INLINE vec4_t& operator=(const vec4_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;

		return *this;
	}

	float w = 0.f;
};

struct ALIGN16 vec4a_t : public vec3_t {
	vec4a_t() = default;
	vec4a_t(float ix, float iy, float iz) {
		x = ix;
		y = iy;
		z = iz;
	}

	vec4a_t(const vec3_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
	}

	ALWAYS_INLINE vec4a_t& operator=(const vec3_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;

		return *this;
	}

	ALWAYS_INLINE vec4a_t& operator=(const vec4a_t& value) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;

		return *this;
	}

	float w = 0.f;
};

struct qangle_t {
	qangle_t() = default;
	qangle_t(float ix, float iy, float iz) {
		x = ix;
		y = iy;
		z = iz;
	}

	float x = 0.f, y = 0.f, z = 0.f;

	ALWAYS_INLINE qangle_t operator+(const qangle_t& value) const { return qangle_t(x + value.x, y + value.y, z + value.z); }

	ALWAYS_INLINE qangle_t operator-(const qangle_t& value) const { return qangle_t(x - value.x, y - value.y, z - value.z); }

	ALWAYS_INLINE qangle_t operator-(float value) const { return qangle_t(x - value, y - value, z - value); }

	ALWAYS_INLINE qangle_t operator+(float value) const { return qangle_t(x + value, y + value, z + value); }

	ALWAYS_INLINE qangle_t operator/(float value) const { return qangle_t(x / value, y / value, z / value); }

	ALWAYS_INLINE qangle_t operator*(float value) const { return qangle_t(x * value, y * value, z * value); }

	ALWAYS_INLINE qangle_t& operator-=(const qangle_t& value) {
		x -= value.x;
		y -= value.y;
		z -= value.z;

		return *this;
	}

	ALWAYS_INLINE qangle_t& operator+=(const qangle_t& value) {
		x += value.x;
		y += value.y;
		z += value.z;

		return *this;
	}

	ALWAYS_INLINE qangle_t& operator/=(float value) {
		x /= value;
		y /= value;
		z /= value;

		return *this;
	}

	ALWAYS_INLINE qangle_t& operator*=(float value) {
		x *= value;
		y *= value;
		z *= value;

		return *this;
	}

	ALWAYS_INLINE bool operator==(const qangle_t& value) const { return x == value.x && y == value.y && z == value.z; }

	ALWAYS_INLINE bool operator!=(const qangle_t& value) const { return !(operator==(value)); }

	qangle_t& sanitize();

	qangle_t& normalize() {
		x = remainderf(x, 360.f);
		y = remainderf(y, 360.f);
		z = remainderf(z, 360.f);

		return *this;
	}

	ALWAYS_INLINE qangle_t normalized() const {
		auto ret = *this;

		return ret.normalize();
	}

	matrix3x4_t matrix() const;

	vec3_t vector(vec3_t* right = nullptr, vec3_t* up = nullptr) const;

	ALWAYS_INLINE float length_sqr() const { return x * x + y * y + z * z; }

	ALWAYS_INLINE float length() const { return std::sqrt(length_sqr()); }

	ALWAYS_INLINE float length_2d() const { return std::sqrt(x * x + y * y); }

	ALWAYS_INLINE bool is_valid() const { return std::isfinite(x) && std::isfinite(y) && std::isfinite(z); }

	ALWAYS_INLINE bool empty() const { return x == 0.f && y == 0.f && z == 0.f; }
};

struct col_t {
	col_t() = default;
	col_t(int r, int g, int b) { set(r, g, b, 255); }
	col_t(int r, int g, int b, int a) { set(r, g, b, a); }
	col_t(const col_t& col, int a) { set(col.r(), col.g(), col.b(), a); }

	std::array<uint8_t, 4> m_value = {};

	ALWAYS_INLINE void set(uint8_t r, uint8_t g, uint8_t b, uint8_t a) { m_value = { r, g, b, a }; }

	ALWAYS_INLINE int r() const { return m_value.at(0u); }

	ALWAYS_INLINE int g() const { return m_value.at(1u); }

	ALWAYS_INLINE int b() const { return m_value.at(2u); }

	ALWAYS_INLINE int a() const { return m_value.at(3u); }

	ALWAYS_INLINE uint32_t hex(bool rgba = false) const {
		return rgba
			? ((r() & 0xFF) << 24) + ((g() & 0xFF) << 16) + ((b() & 0xFF) << 8) + (a() & 0xFF)
			: ((a() & 0xFF) << 24) + ((b() & 0xFF) << 16) + ((g() & 0xFF) << 8) + (r() & 0xFF);
	}

	ALWAYS_INLINE col_t alpha(int value) const { return col_t(r(), g(), b(), value); }

	ALWAYS_INLINE col_t& operator=(const col_t& value) {
		set(value.r(), value.g(), value.b(), value.a());

		return *this;
	}

	ALWAYS_INLINE col_t& operator-=(uint8_t value) {
		set(r() - value, g() - value, b() - value, a() - value);

		return *this;
	}

	ALWAYS_INLINE col_t& operator+=(uint8_t value) {
		set(r() + value, g() + value, b() + value, a() + value);

		return *this;
	}

	ALWAYS_INLINE col_t& operator/=(uint8_t value) {
		set(r() / value, g() / value, b() / value, a() / value);

		return *this;
	}

	ALWAYS_INLINE col_t& operator*=(uint8_t value) {
		set(r() * value, g() * value, b() * value, a() * value);

		return *this;
	}

	ALWAYS_INLINE col_t& operator-=(const col_t& value) {
		set(r() - value.r(), g() - value.g(), b() - value.b(), a() - value.a());

		return *this;
	}

	ALWAYS_INLINE col_t& operator+=(const col_t& value) {
		set(r() + value.r(), g() + value.g(), b() + value.b(), a() + value.a());

		return *this;
	}

	ALWAYS_INLINE col_t operator-(uint8_t value) const { return col_t(r() - value, g() - value, b() - value, a() - value); }

	ALWAYS_INLINE col_t operator+(uint8_t value) const { return col_t(r() + value, g() + value, b() + value, a() + value); }

	ALWAYS_INLINE col_t operator/(uint8_t value) const { return col_t(r() / value, g() / value, b() / value, a() / value); }

	ALWAYS_INLINE col_t operator*(uint8_t value) const { return col_t(r() * value, g() * value, b() * value, a() * value); }

	ALWAYS_INLINE col_t operator-(const col_t& value) const { return col_t(r() - value.r(), g() - value.g(), b() - value.b(), a() - value.a()); }

	ALWAYS_INLINE col_t operator+(const col_t& value) const { return col_t(r() + value.r(), g() + value.g(), b() + value.b(), a() + value.a()); }

	ALWAYS_INLINE bool operator==(const col_t& value) const { return *const_cast<col_t*>(this) == *const_cast<col_t*>(&value); }

	ALWAYS_INLINE bool operator!=(const col_t& value) const { return !(operator==(value)); }

	ALWAYS_INLINE float hue() const {
		const auto red = r() / 255.f;
		const auto green = g() / 255.f;
		const auto blue = b() / 255.f;

		const auto max = std::max<float>({ red, green, blue });
		const auto min = std::min<float>({ red, green, blue });

		if (max == min)
			return 0.f;

		const auto delta = max - min;

		auto hue = 0.f;

		if (max == red) {
			hue = (green - blue) / delta;
		}
		else if (max == green) {
			hue = 2.f + (blue - red) / delta;
		}
		else {
			hue = 4.f + (red - green) / delta;
		}

		hue *= 60.f;

		if (hue < 0.f) {
			hue += 360.f;
		}

		return hue / 360.f;
	}

	ALWAYS_INLINE float saturation() const {
		const auto red = r() / 255.f;
		const auto green = g() / 255.f;
		const auto blue = b() / 255.f;

		const auto max = std::max<float>({ red, green, blue });
		const auto min = std::min<float>({ red, green, blue });

		const auto delta = max - min;

		if (max == 0.f)
			return delta;

		return delta / max;
	}

	ALWAYS_INLINE float brightness() const { return std::max<float>({ r() / 255.f, g() / 255.f, b() / 255.f }); }

	ALWAYS_INLINE static col_t from_hsb(float hue, float saturation, float brightness) {
		const auto h = hue == 1.f ? 0 : hue * 6.f;
		const auto f = h - static_cast<int>(h);
		const auto p = brightness * (1.f - saturation);
		const auto q = brightness * (1.f - saturation * f);
		const auto t = brightness * (1.f - (saturation * (1.f - f)));

		if (h < 1.f) {
			return col_t(
				static_cast<uint8_t>(brightness * 255.f),
				static_cast<uint8_t>(t * 255.f),
				static_cast<uint8_t>(p * 255.f)
			);
		}

		if (h < 2.f) {
			return col_t(
				static_cast<uint8_t>(q * 255),
				static_cast<uint8_t>(brightness * 255),
				static_cast<uint8_t>(p * 255)
			);
		}

		if (h < 3.f) {
			return col_t(
				static_cast<uint8_t>(p * 255.f),
				static_cast<uint8_t>(brightness * 255.f),
				static_cast<uint8_t>(t * 255.f)
			);
		}

		if (h < 4.f) {
			return col_t(
				static_cast<uint8_t>(p * 255.f),
				static_cast<uint8_t>(q * 255.f),
				static_cast<uint8_t>(brightness * 255.f)
			);
		}

		if (h < 5.f) {
			return col_t(
				static_cast<uint8_t>(t * 255.f),
				static_cast<uint8_t>(p * 255.f),
				static_cast<uint8_t>(brightness * 255.f)
			);
		}

		return col_t(
			static_cast<uint8_t>(brightness * 255.f),
			static_cast<uint8_t>(p * 255.f),
			static_cast<uint8_t>(q * 255.f)
		);
	}

	struct palette_t {
		static col_t red(int alpha = 255) { return col_t(255, 0, 0, alpha); }
		static col_t green(int alpha = 255) { return col_t(0, 255, 0, alpha); }
		static col_t blue(int alpha = 255) { return col_t(0, 0, 255, alpha); }

		static col_t white(int alpha = 255) { return col_t(255, 255, 255, alpha); }
		static col_t black(int alpha = 255) { return col_t(13, 13, 13, alpha); }
		static col_t grey(int alpha = 255) { return col_t(60, 60, 60, alpha); }
		static col_t orange(int alpha = 255) { return col_t(245, 171, 53, alpha); }

		static col_t light_black(int alpha = 255) { return col_t(32, 32, 32, alpha); }
		static col_t light_grey(int alpha = 255) { return col_t(77, 77, 77, alpha); }
		static col_t light_green(int alpha = 255) { return col_t(127, 255, 0, alpha); }
		static col_t light_red(int alpha = 255) { return col_t(236, 98, 95, alpha); }
		static col_t light_blue(int alpha = 255) { return col_t(42, 87, 233, alpha); }
		static col_t light_violet(int alpha = 255) { return col_t(153, 153, 255, alpha); }
		static col_t light_purple(int alpha = 255) { return col_t(127, 73, 208, alpha); }

		static col_t dark_grey(int alpha = 255) { return col_t(44, 44, 44, alpha); }
		static col_t dark_blue(int alpha = 255) { return col_t(14, 18, 134, alpha); }

		static col_t purple(int alpha = 255) { return col_t(220, 0, 220, alpha); }
		static col_t pink(int alpha = 255) { return col_t(255, 105, 180, alpha); }
	};
};

struct matrix3x4_t {
	matrix3x4_t() = default;
	matrix3x4_t(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23) {
		m_value[0][0] = m00;
		m_value[0][1] = m01;
		m_value[0][2] = m02;
		m_value[0][3] = m03;

		m_value[1][0] = m10;
		m_value[1][1] = m11;
		m_value[1][2] = m12;
		m_value[1][3] = m13;

		m_value[2][0] = m20;
		m_value[2][1] = m21;
		m_value[2][2] = m22;
		m_value[2][3] = m23;
	}

	matrix3x4_t(const vec3_t& x_axis, const vec3_t& y_axis, const vec3_t& z_axis, const vec3_t& origin) {
		m_value[0][0] = x_axis.x;
		m_value[0][1] = y_axis.x;
		m_value[0][2] = z_axis.x;
		m_value[0][3] = origin.x;

		m_value[1][0] = x_axis.y;
		m_value[1][1] = y_axis.y;
		m_value[1][2] = z_axis.y;
		m_value[1][3] = origin.y;

		m_value[2][0] = x_axis.z;
		m_value[2][1] = y_axis.z;
		m_value[2][2] = z_axis.z;
		m_value[2][3] = origin.z;
	}

	ALWAYS_INLINE vec3_t get_column(int column) const { return vec3_t(m_value[0][column], m_value[1][column], m_value[2][column]); }

	ALWAYS_INLINE void set_column(const vec3_t& value, int column) {
		m_value[0][column] = value.x;
		m_value[1][column] = value.y;
		m_value[2][column] = value.z;
	}

	ALWAYS_INLINE void add_to_column(const vec3_t& value, int column) {
		m_value[0][column] += value.x;
		m_value[1][column] += value.y;
		m_value[2][column] += value.z;
	}

	ALWAYS_INLINE matrix3x4_t operator+(const matrix3x4_t& value) const {
		return matrix3x4_t(
			m_value[0][0] + value[0][0], m_value[0][1] + value[0][1], m_value[0][2] + value[0][2], m_value[0][3] + value[0][3],
			m_value[1][0] + value[1][0], m_value[1][1] + value[1][1], m_value[1][2] + value[1][2], m_value[1][3] + value[1][3],
			m_value[2][0] + value[2][0], m_value[2][1] + value[2][1], m_value[2][2] + value[2][2], m_value[2][3] + value[2][3]
		);
	}

	ALWAYS_INLINE matrix3x4_t operator*(const matrix3x4_t& value) const {
		return matrix3x4_t(
			m_value[0][0] * value[0][0] + m_value[0][1] * value[1][0] + m_value[0][2] * value[2][0],
			m_value[0][0] * value[0][1] + m_value[0][1] * value[1][1] + m_value[0][2] * value[2][1],
			m_value[0][0] * value[0][2] + m_value[0][1] * value[1][2] + m_value[0][2] * value[2][2],
			m_value[0][0] * value[0][3] + m_value[0][1] * value[1][3] + m_value[0][2] * value[2][3] + m_value[0][3],
			m_value[1][0] * value[0][0] + m_value[1][1] * value[1][0] + m_value[1][2] * value[2][0],
			m_value[1][0] * value[0][1] + m_value[1][1] * value[1][1] + m_value[1][2] * value[2][1],
			m_value[1][0] * value[0][2] + m_value[1][1] * value[1][2] + m_value[1][2] * value[2][2],
			m_value[1][0] * value[0][3] + m_value[1][1] * value[1][3] + m_value[1][2] * value[2][3] + m_value[1][3],
			m_value[2][0] * value[0][0] + m_value[2][1] * value[1][0] + m_value[2][2] * value[2][0],
			m_value[2][0] * value[0][1] + m_value[2][1] * value[1][1] + m_value[2][2] * value[2][1],
			m_value[2][0] * value[0][2] + m_value[2][1] * value[1][2] + m_value[2][2] * value[2][2],
			m_value[2][0] * value[0][3] + m_value[2][1] * value[1][3] + m_value[2][2] * value[2][3] + m_value[2][3]
		);
	}

	ALWAYS_INLINE matrix3x4_t operator*(float value) const {
		return matrix3x4_t(
			m_value[0][0] * value,
			m_value[0][1] * value,
			m_value[0][2] * value,
			m_value[0][3] * value,
			m_value[1][0] * value,
			m_value[1][1] * value,
			m_value[1][2] * value,
			m_value[1][3] * value,
			m_value[2][0] * value,
			m_value[2][1] * value,
			m_value[2][2] * value,
			m_value[2][3] * value
		);
	}

	ALWAYS_INLINE vec3_t operator*(const vec3_t& value) const {
		return vec3_t(
			m_value[0][0] * value.x + m_value[0][1] * value.y + m_value[0][2] * value.z + m_value[0][3],
			m_value[1][0] * value.x + m_value[1][1] * value.y + m_value[1][2] * value.z + m_value[1][3],
			m_value[2][0] * value.x + m_value[2][1] * value.y + m_value[2][2] * value.z + m_value[2][3]
		);
	}

	qangle_t angle() const;

	ALWAYS_INLINE vec4_t& operator[](int i) { return m_value.at(i); }

	ALWAYS_INLINE const vec4_t& operator[](int i) const { return m_value.at(i); }

	ALWAYS_INLINE vec3_t origin() { return { m_value[0][3], m_value[1][3], m_value[2][3] }; }

	std::array<vec4_t, 3u> m_value = {};
};

struct ALIGN16 matrix3x4a_t : public matrix3x4_t {

};

struct v_matrix {
	ALWAYS_INLINE vec4_t& operator[](int i) { return m_value.at(i); }

	ALWAYS_INLINE const vec4_t& operator[](int i) const { return m_value.at(i); }

	std::array<vec4_t, 4u> m_value = {};
};

template <typename T>
struct bit_flag_t {
	bit_flag_t() = default;
	bit_flag_t(const T& value) { m_value = value; }

	ALWAYS_INLINE bool has(const T& value) const { return m_value & value; }

	ALWAYS_INLINE void add(const T& value) { m_value |= value; }

	ALWAYS_INLINE void remove(const T& value) { m_value &= ~value; }

	ALWAYS_INLINE void clear() { m_value = {}; }

	ALWAYS_INLINE bool empty() const { return m_value == std::numeric_limits<T>::quiet_NaN(); }

	ALWAYS_INLINE operator T() const { return m_value; }

	ALWAYS_INLINE bit_flag_t<T>& operator=(const bit_flag_t<T>& value) {
		m_value = value.m_value;

		return *this;
	}

	ALWAYS_INLINE T& operator=(const T& value) {
		m_value = value;

		return m_value;
	}

	T m_value = {};
};
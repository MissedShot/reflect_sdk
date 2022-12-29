#pragma once

struct settings {
	struct {
		struct {
			bool m_player{};

			bool m_invisible{};

			int m_material{};
		} m_chams{};

	} m_visuals{};

	struct {
		bool m_bhop{};
	} m_misc{};

	struct {
		struct {
			col_t m_visible{};
			col_t m_invisible{};
		} m_chams{};

	} m_colors{};
};

extern settings g_settings;

namespace config {
	struct items_t {
	public:
		std::string m_name{};
		void* m_pointer{};
		std::string m_type{};

		items_t(std::string name, void* pointer, std::string type) {
			m_name = name;
			m_pointer = pointer;
			m_type = type;
		}
	};

	extern std::vector <items_t*> m_items;

	void init();
	void save(std::string name);
	void load(std::string name);

	void add(void* pointer, std::string name, const std::string& type);
	void setup(int* pointer, int value, const std::string& name);
	void setup(bool* pointer, bool value, const std::string& name);
	void setup(float* pointer, float value, const std::string& name);
	void setup(col_t* pointer, col_t value, const std::string& name);
	void setup(std::vector< int >* pointer, int size, const std::string& name);
	void setup(std::vector< float >* pointer, int size, const std::string& name);
	void setup(std::vector< std::string >* pointer, const std::string& name);
	void setup(std::string* pointer, const std::string& value, const std::string& name);
}
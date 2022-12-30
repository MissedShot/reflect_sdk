#include "../utils.hh"
#include "deps/base64.hh"
#include "deps/json.hh"

settings g_settings{};

namespace config {
	void init() {
		
		{
			setup(&g_settings.m_visuals.m_chams.m_player, false, _("chams.player"));
			setup(&g_settings.m_visuals.m_chams.m_invisible, false, _("chams.invisible"));
			setup(&g_settings.m_visuals.m_chams.m_material, 0, _("chams.material"));
		}

		{
			setup(&g_settings.m_misc.m_bhop, false, _("misc.bhop"));
		}

		{
			setup(&g_settings.m_colors.m_chams.m_visible, col_t(255, 255, 255), _("chams_color.visible"));
			setup(&g_settings.m_colors.m_chams.m_invisible, col_t(255, 255, 255), _("chams_color.invisible"));
		}
	}

	void save(std::string name) {
		auto path = std::filesystem::path(getenv(_("HOME")));

		path /= "config";
		path /= name;

		std::filesystem::create_directory(path.parent_path());

		nlohmann::json json;

		for (auto it : m_items) {
			nlohmann::json j;

			j[_("name")] = it->m_name;
			j[_("type")] = it->m_type;

			if (!it->m_type.compare(_("int")))
				j[_("value")] = *static_cast<int*>(it->m_pointer);

			else if (!it->m_type.compare(_("float")))
				j[_("value")] = *static_cast<float*>(it->m_pointer);

			else if (!it->m_type.compare(_("bool")))
				j[_("value")] = *static_cast<bool*>(it->m_pointer);

			else if (!it->m_type.compare(_("col_t"))) {
				auto c = *static_cast<col_t*>(it->m_pointer);

				std::vector<int> a = { c.r(), c.g(), c.b(), c.a() };
				nlohmann::json ja;

				for (auto& i : a)
					ja.push_back(i);

				j[_("value")] = ja.dump();
			}

			else if (!it->m_type.compare(_("vector<int>"))) {
				auto& ptr = *static_cast<std::vector<int>*>(it->m_pointer);
				nlohmann::json ja;

				for (auto& i : ptr)
					ja.push_back(i);

				j[_("value")] = ja.dump();
			}

			else if (!it->m_type.compare(_("vector<float>"))) {
				auto& ptr = *static_cast<std::vector<float>*>(it->m_pointer);
				nlohmann::json ja;

				for (auto& i : ptr)
					ja.push_back(i);

				j[_("value")] = ja.dump();
			}

			else if (!it->m_type.compare(_("vector<string>"))) {
				auto& ptr = *static_cast<std::vector<std::string>*>(it->m_pointer);
				nlohmann::json ja;

				for (auto& i : ptr)
					ja.push_back(i);

				j[_("value")] = ja.dump();
			}

			else if (!it->m_type.compare(_("string")))
				j[_("value")] = *static_cast<std::string*>(it->m_pointer);

			json.push_back(j);
		}

		auto str = crypto::base64_encode(json.dump(4));

		if (std::ofstream file{ path, std::ios::out | std::ios::trunc })
			file << str;
	}

	void load(std::string name) {
		static auto find_item = [](std::vector< items_t* > items, std::string name) -> items_t* {
			for (int i = 0; i < static_cast<int>(items.size()); i++)
				if (!items[i]->m_name.compare(name))
					return items[i];

			return nullptr;
		};

		auto path = std::filesystem::path(getenv(_("HOME")));

		path /= "config";
		path /= name;

		std::filesystem::create_directory(path.parent_path());

		nlohmann::json json;

		std::string str{};
		if (std::ifstream file{ path, std::ios::in })
			file >> str;
		else
			return;

		if (str.empty())
			return;

		json = nlohmann::json::parse(crypto::base64_decode(str));

		for (auto it = json.begin(); it != json.end(); ++it) {
			nlohmann::json j = *it;

			std::string name = j[_("name")];
			std::string type = j[_("type")];

			auto item = find_item(m_items, name);
			if (!item)
				continue;

			if (!type.compare(_("int")))
				*static_cast<int*>(item->m_pointer) = j[_("value")].get<int>();

			else if (!type.compare(_("float")))
				*static_cast<float*>(item->m_pointer) = j[_("value")].get<float>();

			else if (!type.compare(_("bool")))
				*static_cast<bool*>(item->m_pointer) = j[_("value")].get<bool>();

			else if (!type.compare(_("col_t"))) {
				std::vector<int> a;
				nlohmann::json ja = nlohmann::json::parse(j[_("value")].get<std::string>().c_str());

				for (nlohmann::json::iterator it = ja.begin(); it != ja.end(); ++it)
					a.push_back(*it);

				*static_cast<col_t*>(item->m_pointer) = col_t(a[0], a[1], a[2], a[3]);
			}

			else if (!type.compare(_("vector<int>"))) {
				auto ptr = static_cast<std::vector <int>*> (item->m_pointer);
				ptr->clear();

				nlohmann::json ja = nlohmann::json::parse(j[_("value")].get<std::string>().c_str());

				for (nlohmann::json::iterator it = ja.begin(); it != ja.end(); ++it)
					ptr->push_back(*it);
			}

			else if (!type.compare(_("vector<float>"))) {
				auto ptr = static_cast<std::vector <float>*> (item->m_pointer);
				ptr->clear();

				nlohmann::json ja = nlohmann::json::parse(j[_("value")].get<std::string>().c_str());

				for (nlohmann::json::iterator it = ja.begin(); it != ja.end(); ++it)
					ptr->push_back(*it);
			}

			else if (!type.compare(_("vector<string>"))) {
				auto ptr = static_cast<std::vector <std::string>*> (item->m_pointer);
				ptr->clear();

				nlohmann::json ja = nlohmann::json::parse(j[_("value")].get<std::string>().c_str());

				for (nlohmann::json::iterator it = ja.begin(); it != ja.end(); ++it)
					ptr->push_back(*it);
			}

			else if (!type.compare(_("string")))
				*static_cast<std::string*>(item->m_pointer) = j[_("value")].get<std::string>();
		}
	}

	void add(void* pointer, std::string name, const std::string& type) {
		m_items.push_back(new items_t(name, pointer, type));
	}

	void setup(int* pointer, int value, const std::string& name) {
		add(pointer, name, _("int"));
		*pointer = value;
	}

	void setup(bool* pointer, bool value, const std::string& name) {
		add(pointer, name, _("bool"));
		*pointer = value;
	}

	void setup(float* pointer, float value, const std::string& name) {
		add(pointer, name, _("float"));
		*pointer = value;
	}

	void setup(col_t* pointer, col_t value, const std::string& name) {
		add(pointer, name, _("col_t"));
		*pointer = value;
	}

	void setup(std::vector< int >* pointer, int size, const std::string& name) {
		add(pointer, name, _("vector<int>"));
		pointer->clear();
		pointer->resize(size);
	}

	void setup(std::vector< float >* pointer, int size, const std::string& name) {
		add(pointer, name, _("vector<float>"));
		pointer->clear();
		pointer->resize(size);
	}

	void setup(std::vector< std::string >* pointer, const std::string& name) {
		add(pointer, name, _("vector<string>"));
	}

	void setup(std::string* pointer, const std::string& value, const std::string& name) {
		add(pointer, name, _("string"));
		*pointer = value;
	}

	std::vector <items_t*> m_items{};
}

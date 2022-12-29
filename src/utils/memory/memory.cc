#include "../utils.hh"

namespace memory {
    struct dlinfo_t {
        std::size_t     size    = 0;
        std::uintptr_t  address = 0;
        const char*     library = nullptr;
    };

    std::vector<dlinfo_t> libraries{};

    bool get_library_info(const char* library, std::uintptr_t* address, std::size_t* size) {
        if (libraries.empty()) {
            dl_iterate_phdr([](struct dl_phdr_info* info, std::size_t, void*) {
                    dlinfo_t library_info = {};
                    library_info.library = info->dlpi_name;
                    library_info.address = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
                    library_info.size = info->dlpi_phdr[0].p_memsz;
                    libraries.push_back(library_info);
                    return 0;
                },
                nullptr);
        }

        for (const dlinfo_t& current : libraries) {
            if (!strcasestr(current.library, library))
                continue;

            if (address)
                *address = current.address;

            if (size)
                *size = current.size;

            return true;
        }

        return false;
    }

    address_t find_pattern(const char* module, const char* signature) {
        static auto pattern_to_byte = [&](const char* pattern) {
            std::vector<int> bytes{};
            char* start = const_cast<char*>(pattern);
            char* end   = const_cast<char*>(pattern) + strlen(pattern);

            for (char* current_position = start; current_position < end; ++current_position) {
                if (*current_position == '?') {
                    ++current_position;

                    if (*current_position == '?')
                        ++current_position;

                    bytes.push_back(-1);
                }

                else
                    bytes.push_back(strtoul(current_position, &current_position, 16));
            }

            return bytes;
        };

        std::uintptr_t module_ptr = 0;
        std::size_t    size_of_image = 0;

        get_library_info(module, &module_ptr, &size_of_image);

        std::vector<int> pattern_bytes  = pattern_to_byte(signature);
        std::uint8_t* scan_bytes        = reinterpret_cast<std::uint8_t*>(module_ptr);

        std::size_t pattern_size = pattern_bytes.size();
        int* pattern_data        = pattern_bytes.data();

        for (std::size_t i = 0; i < size_of_image - pattern_size; ++i) {
            bool found = true;

            for (std::size_t j = 0; j < pattern_size; ++j) {
                if (scan_bytes[i + j] != pattern_data[j] && pattern_data[j] != -1) {
                    found = false;
                    break;
                }
            }

            if (found)
                return &scan_bytes[i];
        }

        return {};
    }
}
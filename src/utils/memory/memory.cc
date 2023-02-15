#include "../utils.hh"

namespace memory {
    bool get_library_info(const char* library, std::uintptr_t* address, std::size_t* size) {
        if (m_libraries.empty()) {
            dl_iterate_phdr([](struct dl_phdr_info* info, std::size_t, void*) {
                    dlinfo_t library_info{};
                    library_info.m_library  = info->dlpi_name;
                    library_info.m_address  = info->dlpi_addr + info->dlpi_phdr[0].p_vaddr;
                    library_info.m_size     = info->dlpi_phdr[0].p_memsz;
                    
                    m_libraries.push_back(library_info);
                    
                    return 0;
                },
                nullptr);
        }

        for (const dlinfo_t& current : m_libraries) {
            if (!strcasestr(current.m_library, library))
                continue;

            if (address)
                *address = current.m_address;

            if (size)
                *size = current.m_size;

            return true;
        }

        return false;
    }

    address_t find_pattern(const char* module, const char* signature) {
        static auto pattern_to_byte = [&](const char* pattern) {
            char* start = const_cast<char*>(pattern);
            char* end   = const_cast<char*>(pattern) + strlen(pattern);

            std::vector<int> bytes{};
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

        std::uintptr_t module_ptr{};
        std::size_t size_of_image{};

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

    typedef void* (*instantiate_nterface_fn)();
    // https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/public/tier1/interface.h#L72
    class interface_reg {
    public:
        instantiate_nterface_fn m_create;
        const char* m_name;
        interface_reg* m_next;
    };

    address_t get_interface(const char* file, const char* name) {
        // map handle of shared object that contains interface.
        void* lib = dlopen(file, RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);

        // something go wrong
        // unmap and return here.
        if (!lib) {
            dlclose(lib);
            return address_t();
        }

        // https://github.com/ValveSoftware/source-sdk-2013/blob/0d8dceea4310fde5706b3ce1c70609d72a38efdf/sp/src/tier1/interface.cpp#L46
        interface_reg* interface = *reinterpret_cast<interface_reg**>(dlsym(lib, _("s_pInterfaceRegs")));

        // unmap, don't need it anymore.
        dlclose(lib);

        // loop through each interface in interfaceReg linked list
        for (interface_reg* cur = interface; cur; cur = cur->m_next) {
            if (!strstr(cur->m_name, name) || strlen(cur->m_name) != strlen(name))
                continue;

            return reinterpret_cast<address_t*>(cur->m_create());
        }

        return address_t();
    }

    std::vector<dlinfo_t> m_libraries{};
}
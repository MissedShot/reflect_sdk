#pragma once

namespace memory { 
    template <typename ptr_type = uintptr_t>
    struct address_base_t {
        ptr_type m_ptr{};

        ALWAYS_INLINE address_base_t(): m_ptr{} {}
        ALWAYS_INLINE address_base_t(ptr_type ptr) : m_ptr(ptr) {}
        ALWAYS_INLINE address_base_t(ptr_type* ptr) : m_ptr(ptr_type(ptr)) {}
        ALWAYS_INLINE address_base_t(void* ptr) : m_ptr(ptr_type(ptr)) {}
        ALWAYS_INLINE address_base_t(const void* ptr) : m_ptr(ptr_type(ptr)) {}
        ALWAYS_INLINE ~address_base_t() = default;

        ALWAYS_INLINE operator ptr_type() const { return m_ptr; }

        ALWAYS_INLINE operator void* () const { return reinterpret_cast<void*>(m_ptr); }

        ALWAYS_INLINE ptr_type get_inner() const { return m_ptr; }

        template <typename t = address_base_t<ptr_type>>
        ALWAYS_INLINE bool compare(t in) const { return m_ptr == ptr_type(in); }

        ALWAYS_INLINE address_base_t<ptr_type>& self_get(uint8_t in = 1) {
            m_ptr = get<ptr_type>(in);

            return *this;
        }

        ALWAYS_INLINE address_base_t<ptr_type>& add(ptrdiff_t offset) {
            m_ptr += offset;

            return *this;
        }

        template <typename t = address_base_t<ptr_type>>
        ALWAYS_INLINE address_base_t<ptr_type>& relative(ptrdiff_t offset = 0x1) {
            m_ptr = jmp(offset);

            return *this;
        }

        template <typename t = address_base_t<ptr_type>>
        ALWAYS_INLINE address_base_t<ptr_type>& set(t in) {
            m_ptr = ptr_type(in);

            return m_ptr ? *this : t();
        }

        template <typename t = ptr_type>
        ALWAYS_INLINE t cast() { return m_ptr ? t(m_ptr) : t(); }

        template <typename t = address_base_t<ptr_type>>
        ALWAYS_INLINE t get(uint8_t in = 1) {
            ptr_type dummy = m_ptr;

            while (in--)
                /// Check if pointer is still valid
                if (dummy)
                    dummy = *reinterpret_cast<ptr_type*>(dummy);

            return m_ptr ? t(dummy) : t();
        }

        template <typename t = address_base_t<ptr_type>>
        ALWAYS_INLINE t jmp(ptrdiff_t offset = 0x1) {
            ptr_type base     = m_ptr + offset;
            auto displacement = *reinterpret_cast<int32_t*>(base);
            base += sizeof(uint32_t);
            base += displacement;

            return m_ptr ? t(base) : t();
        }
    };
    using address_t = address_base_t<uintptr_t>;

	typedef void* (*instantiate_nterface_fn)();
    class interface_reg {
    public:
        instantiate_nterface_fn m_create;
        const char*             m_name;
        interface_reg*          m_next;
    };

    template <typename T>
    ALWAYS_INLINE T* get_interface(const char* file, const char* name, bool includeVersion = false) {
	    void* lib = dlopen(file, RTLD_NOLOAD | RTLD_NOW | RTLD_LOCAL);
        if (lib) {
            interface_reg* interface = *reinterpret_cast<interface_reg**>(dlsym(lib, _("s_pInterfaceRegs")));
            dlclose(lib);

            for (interface_reg* cur = interface; cur; cur = cur->m_next) {
                if ((strstr(cur->m_name, name) && strlen(cur->m_name)-3 == strlen(name)) || 
                    (includeVersion && (strstr(cur->m_name, name) && strlen(cur->m_name) == strlen(name)))) {
                    T* iface = reinterpret_cast<T*>(cur->m_create());
                    return iface;
                }
            }
        }

        dlclose(lib);
        return nullptr;
    }

    struct dlinfo_t {
        std::size_t     m_size{};
        std::uintptr_t  m_address{};
        const char*     m_library{};
    };

    extern std::vector<dlinfo_t> m_libraries;

    address_t find_pattern(const char *module, const char *signature);

	template <typename t = address_t>
    ALWAYS_INLINE t get_vfunc(address_t pointer, std::size_t index) { return static_cast<t>(pointer.get<t*>()[index]); }
}

#define SIG(module_name, sig) memory::find_pattern(_(module_name), _(sig))

#define VFUNC(func, index, type, ...) ALWAYS_INLINE auto func { return memory::get_vfunc<type>(this, index)(this, ##__VA_ARGS__); };
#define PVFUNC(func, pointer, index, type, ...) ALWAYS_INLINE auto func { return memory::get_vfunc<type>(pointer, index)(pointer, ##__VA_ARGS__); };
#define VFUNC_SIG(func, module_name, sig, type, ...) ALWAYS_INLINE auto func { static const auto fn = SIG(module_name, sig).cast<type>(); return fn(this, ##__VA_ARGS__); };
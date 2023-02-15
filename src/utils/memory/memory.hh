#pragma once

namespace memory {
    struct address_t {
        uint8_t* m_ptr = nullptr;

        address_t() = default;
        address_t(uint8_t* ptr) { m_ptr = ptr; };
        address_t(uintptr_t* ptr) { m_ptr = reinterpret_cast<uint8_t*>(ptr); };
        address_t(void* ptr) { m_ptr = reinterpret_cast<uint8_t*>(ptr); };

        ALWAYS_INLINE operator uint8_t* () const { return m_ptr; }

        template <typename T>
        ALWAYS_INLINE T cast() const { return (T)(m_ptr); }

        template <typename T = address_t>
        ALWAYS_INLINE T offset(ptrdiff_t value) const { return (T)(m_ptr + value); };

        ALWAYS_INLINE address_t& self_offset(ptrdiff_t value) {
            m_ptr += value;

            return *this;
        }

        template <typename T = address_t>
        ALWAYS_INLINE T rel8(ptrdiff_t offset = 0x1) const { return (T)(m_ptr + offset + sizeof(uint8_t) + *reinterpret_cast<int8_t*>(m_ptr + offset)); }

        ALWAYS_INLINE address_t& self_rel8(ptrdiff_t offset = 0x1) {
            m_ptr = rel8(offset);

            return *this;
        }

        template <typename T = address_t>
        ALWAYS_INLINE T rel32(ptrdiff_t offset = 0x1) const { return (T)(m_ptr + offset + sizeof(uint32_t) + *reinterpret_cast<int32_t*>(m_ptr + offset)); }

        ALWAYS_INLINE address_t& self_rel32(ptrdiff_t offset = 0x1) {
            m_ptr = rel32(offset);

            return *this;
        }

        template <typename T = address_t>
        ALWAYS_INLINE T find_opcode(uint8_t opcode, ptrdiff_t offset = 0) const {
            auto ptr = m_ptr;

            while (const auto it = *ptr) {
                if (opcode == it)
                    break;

                ptr += 1u;
            }

            ptr += offset;

            return (T)(ptr);
        }

        ALWAYS_INLINE address_t& self_find_opcode(uint8_t opcode, ptrdiff_t offset = 0) {
            m_ptr = find_opcode(opcode, offset);

            return *this;
        }

        template <typename T = address_t>
        ALWAYS_INLINE T deref(size_t count = 1u) {
            auto ptr = m_ptr;
            
            for (; ptr && count; --count)
                ptr = *cast<T*>();

            return (T)(ptr);
        }

        ALWAYS_INLINE address_t& self_deref(size_t count = 1u) {
            m_ptr = deref(count);

            return *this;
        }
    };

    struct dlinfo_t {
        std::size_t     m_size{};
        std::uintptr_t  m_address{};
        const char*     m_library{};
    };

    extern std::vector<dlinfo_t> m_libraries;

    address_t find_pattern(const char* module, const char* signature);

    address_t get_interface(const char* file, const char* name);

    template <typename T = address_t>
    ALWAYS_INLINE T get_vfunc(address_t pointer, std::size_t index) { return (*memory::address_t(pointer).cast<T**>())[index]; }
}

#define SIG(module_name, sig) memory::find_pattern(_(module_name), _(sig))

#define VFUNC(func, index, type, ...) ALWAYS_INLINE auto func { return memory::get_vfunc<type>(this, index)(this, ##__VA_ARGS__); };
#define PVFUNC(func, pointer, index, type, ...) ALWAYS_INLINE auto func { return memory::get_vfunc<type>(pointer, index)(pointer, ##__VA_ARGS__); };
#define VFUNC_SIG(func, module_name, sig, type, ...) ALWAYS_INLINE auto func { static const auto fn = SIG(module_name, sig).cast<type>(); return fn(this, ##__VA_ARGS__); };
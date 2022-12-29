#pragma once
#include "../../sdk/datatypes/recv_prop.hh"

namespace netvars {
	void init();

	void dump_recursive(const char* base_class, recv_table_t* table, uint32_t offset);

	extern std::unordered_map<uint32_t, std::pair<recv_prop_t*, uint32_t>> m_list;

	template<typename T>
	ALWAYS_INLINE T get(uint32_t hash) { return std::get<T>(m_list.at(hash)); }
};

#define NETVAR(func, type, name) \
	ALWAYS_INLINE type& func { \
		static const auto offset = netvars::get<uint32_t>(FNV1A(name)); \
		return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
	}

#define ANETVAR(func, type, size, name) \
	ALWAYS_ALWAYS_INLINE std::array<type, size>& func { \
		static const auto offset = netvars::get<uint32_t>(FNV1A(name)); \
		return *reinterpret_cast<std::array<type, size>*>(reinterpret_cast<uintptr_t>(this) + offset); \
	}

#define PNETVAR(func, type, name) \
	ALWAYS_INLINE type* func { \
		static const auto offset = netvars::get<uint32_t>(FNV1A(name)); \
		return reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
	}

#define NETVAR_OFFSET(func, type, name, add) \
	ALWAYS_INLINE type& func { \
		static const auto offset = netvars::get<uint32_t>(FNV1A(name)); \
		return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset + add); \
	}

#define PNETVAR_OFFSET(func, type, name, add) \
	ALWAYS_INLINE type* func { \
		static const auto offset = netvars::get<uint32_t>(FNV1A(name)); \
		return reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset + add); \
	}

#define MNETVAR(func, type, name, modifier) \
	ALWAYS_INLINE type& func { \
		static const auto offset = netvars::get<uint32_t>(FNV1A(name)); \
		return **reinterpret_cast<type**>(reinterpret_cast<uintptr_t>(this) + offset * modifier); \
	}

#define NETPROP(func, name) \
	ALWAYS_INLINE static recv_prop_t* func { \
		static const auto prop = netvars::get<recv_prop_t*>(FNV1A(name)); \
		return prop; \
	}

#define OFFSET(func, type, offset) ALWAYS_INLINE type& func { return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); }

#define POFFSET(func, type, offset) ALWAYS_INLINE type* func { return reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); }

#define PPOFFSET(func, type, offset) ALWAYS_INLINE type& func { return **reinterpret_cast<type**>(reinterpret_cast<uintptr_t>(this) + offset); }

#define MOFFSET(func, type, offset, modifier) ALWAYS_INLINE type& func { return **reinterpret_cast<type**>(reinterpret_cast<uintptr_t>(this) + offset * modifier); }
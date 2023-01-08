#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#include "../common_includes.hh"
#include "../sdk/definitions.hh"

#include "math/datatypes.hh"
#include "math/math.hh"

#include "obfuscation/fnv1a.hh"
#include "obfuscation/xor.hh"

#include "memory/memory.hh"

#include "hooking/vmt.hh"

#include "imgui/imgui.hh"
#include "imgui/imgui_internal.hh"
#include "imgui/imconfig.hh"
#include "imgui/backend/imgui_impl_opengl3.hh"
#include "imgui/backend/imgui_impl_sdl.hh"

#include "render/render.hh"

#include "netvars/netvars.hh"
#include "netvars/data_map.hh"

#include "config/config.hh"

#include "input/input.hh"

namespace utils {
    // https://stackoverflow.com/questions/4804298
    ALWAYS_INLINE std::string to_utf8(const std::wstring& wstr) {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;

        return converterX.to_bytes(wstr);
    }

    ALWAYS_INLINE std::wstring to_unicode(const std::string& str) {
        using convert_typeX = std::codecvt_utf8<wchar_t>;
        std::wstring_convert<convert_typeX, wchar_t> converterX;

        return converterX.from_bytes(str);
    }
}
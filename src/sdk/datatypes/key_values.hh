#pragma once

class c_key_values {
public:
    ~c_key_values();

    VFUNC_SIG(init(const char* key_name), "/client_client.so", "81 27 00 00 00 FF 55 45 31 C0 48 89 E5 5D", void(*)(void*, const char*, int, int), key_name, 0, 0)
    VFUNC_SIG(load_from_buffer(const char* resource_name, const char* buf, void* file_sys = nullptr, const char* path_id = nullptr, void* eval_sym_proc = nullptr, void* unk = nullptr),
        "/client_client.so", "55 48 89 E5 41 57 41 56 41 55 41 54 49 89 D4 53 48 81 EC ? ? ? ? 48 85", void(*)(void*, const char*, const char*, void*, const char*, void*, void*), resource_name, buf, file_sys, path_id, eval_sym_proc, unk)
};
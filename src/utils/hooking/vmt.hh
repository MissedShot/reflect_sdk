#pragma once

namespace vmt_hook {
    inline int pagesize = sysconf(_SC_PAGE_SIZE);
    inline int pagemask = ~(pagesize - 1);

    ALWAYS_INLINE int unprotect(void* region) {
        mprotect((void*)((intptr_t)region & pagemask), pagesize, PROT_READ | PROT_WRITE | PROT_EXEC);
        return PROT_READ | PROT_EXEC;
    }

    ALWAYS_INLINE void protect(void* region, int protection) {
        mprotect((void*)((intptr_t)region & pagemask), pagesize, protection);
    }

    ALWAYS_INLINE void* hook(void* instance, void* hook, int offset) {
        intptr_t vtable = *((intptr_t*)instance);
        intptr_t entry = vtable + sizeof(intptr_t) * offset;
        intptr_t original = *((intptr_t*)entry);

        int originalProtection = unprotect((void*)entry);
        *((intptr_t*)entry) = (intptr_t)hook;
        protect((void*)entry, originalProtection);

        return (void*)original;
    }
}
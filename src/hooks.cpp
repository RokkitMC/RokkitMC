//
// Created by mwmat on 24/12/2020.
//
#include "hooks.h"
#include <subhook_private.h>
void* GetSymbol(const char* funcName) {
#ifdef __unix__
    return dlsym(RTLD_DEFAULT, funcName);
#elif defined(_WIN32) || defined(WIN32)
#error "Not implemented"
#endif
}

std::list<subhook_t> activeHooks;

std::list<subhook_t> GetHooks() {
    return activeHooks;
}

subhook_t Hook (void** original, void* hook, const char* funcName)
{
    *original = GetSymbol(funcName);
    subhook_t newHook = subhook_new(*original, hook, static_cast<subhook_flags>(SUBHOOK_64BIT_OFFSET));
    int rc = subhook_install(newHook);
    if(rc != 0)
        printf("%s[RokkitMC]: Failed to hook %s with error-code %d %s\n", RED, funcName, rc, RESET);
    activeHooks.insert(activeHooks.end(), newHook);
    return newHook;
}
//
// Created by mwmat on 24/12/2020.
//
#include "hooks.h"
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
    subhook_t newHook = subhook_new(*original, hook, static_cast<subhook_flags>(0));
    int rc = subhook_install(newHook);
    if(rc != 0)
        printf("%s[RokkitMC]: Error hooking %s %s\n", RED, funcName, RESET);
    activeHooks.insert(activeHooks.end(), newHook);
    return newHook;
}
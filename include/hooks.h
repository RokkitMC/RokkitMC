//
// Created by mwmat on 07/12/2020.
//

#ifndef ROKKITMC_HOOKS_H
#define ROKKITMC_HOOKS_H
#include <iostream>
#include <list>
#include <subhook.h>

#ifdef __unix__
#include <dlfcn.h>
#endif

#include "logger.h"

std::list<subhook_t> activeHooks;

void* GetSymbol(const char* funcName) {
#ifdef __unix__
    return dlsym(RTLD_DEFAULT, funcName);
#elif defined(_WIN32) || defined(WIN32)
#error "Not implemented"
#endif
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
#endif //ROKKITMC_HOOKS_H

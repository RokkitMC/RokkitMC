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

void* GetSymbol(const char* funcName);
subhook_t Hook(void** original, void* hook, const char* funcName);
std::list<subhook_t> GetHooks();

#endif //ROKKITMC_HOOKS_H

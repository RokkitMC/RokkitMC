#include <iostream>
#include <dlfcn.h>
#include <thread>
#include <unistd.h>
#include "hooks.h"
#include "logger.h"

using std::cout;
using std::string;
using subhook::Hook;

subhook_t clientAuthHook;
void* clientAuthOrig;

typedef uint64_t(*clientAuthenticated_t)(int64_t*, int64_t*, int64_t*);

uint64_t clientAuthenticated(int64_t* self, int64_t* ni, int64_t* cert) {
    printf("Client Authenticated!\n");
    subhook_remove(clientAuthHook);
    auto original = (clientAuthenticated_t)clientAuthOrig;
    auto result = original(self, ni, cert);
    subhook_install(clientAuthHook);
    return result;
}
__attribute((constructor))
void entry() {
    string version = "1.16.10";
    printf("Loading RokkitMC for BDS: %s!\n", version.c_str());
    clientAuthHook = Hook(&clientAuthOrig, (void*)clientAuthenticated, "_ZN20ServerNetworkHandler22_onClientAuthenticatedERK17NetworkIdentifierRK11Certificate");
    printf("%d %d %d", clientAuthOrig, clientAuthenticated, clientAuthHook);
}

//static struct init {
//    init()
//    {
//        entry();
//    }
//    ~init()
//    {
//        std::list<subhook_t>::iterator it;
//        for (it = activeHooks.begin(); it != activeHooks.end(); ++it) {
//            subhook_remove(*it);
//            subhook_free(*it);
//        }
//    }
//} init;
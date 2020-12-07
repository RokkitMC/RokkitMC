#include <thread>
#include "hooks.h"
#include "logger.h"
#include "Rokkit/Rokkit.h"
using std::cout;
using std::string;
using subhook::Hook;

subhook_t clientAuthHook;
void* clientAuthOrig;

typedef uint64_t(*clientAuthenticated_t)(int64_t*, int64_t*, Rokkit::Certificate*);
typedef char* (*getIdentityName_t)(string*, int64_t*);

uint64_t clientAuthenticated(int64_t* self, int64_t* ni, Rokkit::Certificate* cert) {
    Logger::Info("Client Authenticated!\n");
    Rokkit::Player player(cert);
    printf("[RokkitMC]: Player name is: %s\n", player.Name.c_str());

    subhook_remove(clientAuthHook);
    auto original = (clientAuthenticated_t)clientAuthOrig;
    auto result = original(self, ni, cert);
    subhook_install(clientAuthHook);

    return result;
}

void entry() {
    string version = "1.16.10";
    printf("[RokkitMC]: Loading RokkitMC for BDS: %s!\n", version.c_str());
    clientAuthHook = Hook(&clientAuthOrig, (void*)clientAuthenticated, "_ZN20ServerNetworkHandler22_onClientAuthenticatedERK17NetworkIdentifierRK11Certificate");
}

static struct init {
    init()
    {
        entry();
    }
    ~init()
    {
        std::list<subhook_t>::iterator it;
        for (it = activeHooks.begin(); it != activeHooks.end(); ++it) {
            subhook_remove(*it);
            subhook_free(*it);
        }
    }
} init;
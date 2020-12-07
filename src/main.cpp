#include <thread>
#include "hooks.h"
#include "logger.h"

using std::cout;
using std::string;
using subhook::Hook;

subhook_t clientAuthHook;
void* clientAuthOrig;

subhook_t playerMessageHook;
void* playerMessageOrig;

typedef uint64_t (*playerMessage_t)(unsigned int, string, string, string, string);

typedef uint64_t(*clientAuthenticated_t)(int64_t*, int64_t*, int64_t*);
typedef char* (*getIdentityName_t)(string*, int64_t*);

uint64_t playerMessage(unsigned int self, string sender, string reciever, string message, string messageType) {
	cout << sender << " : " << message;
	
	subhook_remove(playerMessageHook);
	auto original = (playerMessage_t)playerMessageOrig;
	auto result = original(self, sender, reciever, message, messageType);
	subhook_install(playerMessageHook);

	return result;
}

uint64_t clientAuthenticated(int64_t* self, int64_t* ni, int64_t* cert) {
    Logger::Info("Client Authenticated!\n");
    string username;
    auto getIdentityName = (getIdentityName_t)dlsym(RTLD_DEFAULT, "_ZN19ExtendedCertificate15getIdentityNameB5cxx11ERK11Certificate");
    getIdentityName(&username, cert);
    printf("[RokkitMC]: Player name is: %s\n", username.c_str());
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
    playerMessageHook = Hook(&playerMessageOrig, (void*) playerMessage, "_ZN17MinecraftEventing22fireEventPlayerMessageERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES7_S7_S7_");
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
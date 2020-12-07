#include <iostream>
#include <dlfcn.h>
#include <subhook.h>

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

__attribute__((constructor))
void rokkitmc_init() {
	string version = "1.16.10";
	printf("Loading RokkitMC for BDS: %s!\n", version.c_str());
    clientAuthOrig = dlsym(RTLD_DEFAULT, "_ZN20ServerNetworkHandler22_onClientAuthenticatedERK17NetworkIdentifierRK11Certificate");
	if(!clientAuthOrig) {
		printf(":(\n");
		return;
	}

	void* clientAuth = (void*) clientAuthenticated;
	clientAuthHook = subhook_new(clientAuthOrig, clientAuth, static_cast<subhook_flags>(0));

	int rc = subhook_install(clientAuthHook);

	printf("Subhook Install: %d\n", rc);
}

__attribute__((destructor))
void rokkitmc_deinit() {
	subhook_remove(clientAuthHook);
	subhook_free(clientAuthHook);
}
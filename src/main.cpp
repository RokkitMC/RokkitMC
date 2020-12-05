#include <iostream>
#include <dlfcn.h>
#include <subhook.h>

using std::cout;
using std::string;
using subhook::Hook;

subhook_t clientAuthHook;

typedef void(*__fastcall clientAuthenticated_t)(int64_t, int64_t, int64_t);

void clientAuthenticated(int64_t* ni, int64_t* cert) {
	printf("Client Authenticated!");

	void* trampoline = subhook_get_trampoline(clientAuthHook);
	auto original = (clientAuthenticated_t)trampoline;
	original(ni, cert);
}

__attribute__((constructor))
void rokkitmc_init() {
	string version = "1.16.10";
	printf("Loading RokkitMC for BDS: %s!\n", version.c_str());

	void* ptr = dlsym(RTLD_DEFAULT, "_ZN20ServerNetworkHandler22_onClientAuthenticatedERK17NetworkIdentifierRK11Certificate");

	if(!ptr) {
		printf(":(\n");
		return;
	}

	void* clientAuth = (void*) clientAuthenticated;
	clientAuthHook = subhook_new(ptr, clientAuth, static_cast<subhook_flags>(0));

	int rc = subhook_install(clientAuthHook);

	printf("Subhook Install: %d\n", rc);
}

__attribute__((destructor))
void rokkitmc_deinit() {
	subhook_remove(clientAuthHook);
	subhook_free(clientAuthHook);
}
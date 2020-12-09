#include "hooks.h"
#include "logger.h"
#include "Rokkit/Rokkit.h"
#include "ModLoader.h"
using std::cout, std::string, std::endl;
using subhook::Hook;

subhook_t clientAuthHook;
void* clientAuthOrig;

subhook_t playerMessageHook;
void* playerMessageOrig;

subhook_t recordEventHook;
void* recordEventOriginal;

typedef uint64_t (*playerMessage_t)(uint64_t*, string, string, string, string);

uint64_t playerMessage(uint64_t* self, string sender, string receiver, string message, string messageType) {
	cout << "[RokkitMC]: " << sender << ": " << message << endl;

	subhook_remove(playerMessageHook);
	auto original = (playerMessage_t)playerMessageOrig;
	auto result = original(self, sender, receiver, message, messageType);
	subhook_install(playerMessageHook);

	return result;
}

typedef uint64_t(*clientAuthenticated_t)(int64_t*, int64_t*, Rokkit::Certificate*);

uint64_t clientAuthenticated(int64_t* self, int64_t* ni, Rokkit::Certificate* cert) {
    Logger::Info("Client Authenticated!\n");
    Rokkit::Player player(cert);
    cout << "[RokkitMC]: Player name is: " << player.Name << "\n";

    subhook_remove(clientAuthHook);
    auto original = (clientAuthenticated_t)clientAuthOrig;
    auto result = original(self, ni, cert);
    subhook_install(clientAuthHook);

    return result;
}

typedef uint64_t(*recordEvent_t)(int64_t*, Rokkit::Event*);

uint64_t recordEvent(int64_t* self, Rokkit::Event* event) {
    Logger::Info("Event fired\n");
    //cout << event->propertiesAsJsonValue()->toStyledString() << endl;
    subhook_remove(recordEventHook);
    auto original = (recordEvent_t)recordEventOriginal;
    auto result = original(self, event);
    subhook_install(recordEventHook);
    return result;
}

void entry() {
    string version = "1.16.20";
    printf("%s[RokkitMC]:%s Loading RokkitMC for BDS: %s!\n", GREEN, WHITE, version.c_str());
    clientAuthHook = Hook(&clientAuthOrig, (void*)clientAuthenticated, "_ZN20ServerNetworkHandler22_onClientAuthenticatedERK17NetworkIdentifierRK11Certificate");
    playerMessageHook = Hook(&playerMessageOrig, (void*) playerMessage, "_ZN17MinecraftEventing22fireEventPlayerMessageERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES7_S7_S7_");
    recordEventHook = Hook(&recordEventOriginal, (void*) recordEvent, "_ZN6Social6Events12EventManager11recordEventERNS0_5EventE");

    //Do JVM init last
    Rokkit::ModLoader* modLoader = new Rokkit::ModLoader(JNI_VERSION_1_8);
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
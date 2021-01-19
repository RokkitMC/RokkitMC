#include "Rokkit/Rokkit.h"
#include "hooks.h"
#include "logger.h"
#include <definitions.h>
#include "PluginLoader.h"
#include <unordered_map>

using std::cout, std::string, std::endl;
using subhook::Hook;

subhook_t recordEventHook;
void* recordEventOriginal;

typedef std::string(*getName_t)(int64_t*);

uint64_t recordEvent(int64_t* self, Rokkit::Event* event) {
	Logger::Info("Event fired\n");

	Json::Value* properties = event->propertiesAsJsonValue();

	if(properties != NULL) {
		cout << properties->toStyledString() << endl;
	}

	subhook_remove(recordEventHook);
	auto original = (recordEvent_t)recordEventOriginal;
	auto result = original(self, event);
	subhook_install(recordEventHook);
	return result;
}

static struct init {
	std::list<subhook_t> activeHooks;

	init()
	{
		string version = "1.16.20";
		printf("%s[RokkitMC]:%s Loading RokkitMC for BDS: %s!\n", GREEN, WHITE, version.c_str());
//#if defined _M_IX86 || defined __i386__
//		printf("%s[RokkitMC]:%s Running in 34 bit mode!\n", GREEN, WHITE);
//#elif defined _M_AMD64 || __amd64__
//		printf("%s[RokkitMC]:%s Running in 64 bit mode!\n", GREEN, WHITE);
//#else
//#error Unsupported CPU Architecture
//#endif
		recordEventHook = Hook(&recordEventOriginal, (void*) recordEvent, "_ZN6Social6Events12EventManager11recordEventERNS0_5EventE");
//		clientAuthHook = Hook(activeHooks, &clientAuthOrig, (void*)clientAuthenticated, "_ZN20ServerNetworkHandler22_onClientAuthenticatedERK17NetworkIdentifierRK11Certificate");
//		playerMessageHook = Hook(activeHooks, &playerMessageOrig, (void*) playerMessage, "_ZN17MinecraftEventing22fireEventPlayerMessageERKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES7_S7_S7_");

		//Do JVM init last
		//Rokkit::ModLoader* modLoader = new Rokkit::ModLoader(JNI_VERSION_1_8);
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
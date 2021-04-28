#include "Rokkit/Rokkit.h"
#include "logger.h"
#include <unordered_map>
#include <vector>
#include <algorithm>

using std::cout, std::string, std::endl;
using subhook::Hook;

class Property {

};

class Event {
public:
	std::vector<std::string> getPropkeys() {
		auto map = (std::unordered_map<std::string, Property*>)*(((uint64_t *) this) + 64);

		std::vector<std::string> keys(map.size());
		transform(map.begin(), map.end(), keys.begin(), [](auto pair) {return pair.first;});
		return keys;
	}
};

typedef uint64_t *(*recordEventFunc)(uint64_t* self, Event* ev);

subhook_t recordEventHook;
recordEventFunc recordEventOrig;

uint64_t* recordEventLogger(uint64_t* self, Event* ev) {

	for(const std::string& key: ev->getPropkeys()) {
		printf("%s[RokkitMC]:%s Key: %s", GREEN, WHITE, key.c_str());
	}

	subhook_remove(recordEventHook);
	auto returnVal = recordEventOrig(self, ev);

	subhook_install(recordEventHook);

	return returnVal;
}

static struct init {
	init()
	{
		string version = "1.16.20";
		printf("%s[RokkitMC]:%s Loading RokkitMC for BDS: %s!\n", GREEN, WHITE, version.c_str());

		recordEventOrig = *(recordEventFunc*)dlsym(RTLD_DEFAULT, "_ZN6Social6Events12EventManager11recordEventERNS0_5EventE");
		recordEventHook = subhook_new((void*)recordEventOrig, (void *)recordEventLogger, static_cast<subhook_flags>(SUBHOOK_64BIT_OFFSET));

		if(subhook_install(recordEventHook) != 0)
			printf("%s[RokkitMC]:%s Failed to install hook into bedrock", GREEN, RED);
	}

	~init() {
		subhook_free(recordEventHook);
	}
} init;
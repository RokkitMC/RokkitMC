//
// Created by mwmat on 09/12/2020.
//

#include "Rokkit/Rokkit.h"

typedef int64_t*(*propertiesAsJsonValue_t)(Json::Value*, Rokkit::Event*);

namespace Rokkit {
    Json::Value* Event::propertiesAsJsonValue() {
        Json::Value* json = new Json::Value();
        auto original = (propertiesAsJsonValue_t)dlsym(RTLD_DEFAULT, "_ZNK6Social6Events5Event21propertiesAsJsonValueEv");
        original(json, this);
        return json;
    }
}
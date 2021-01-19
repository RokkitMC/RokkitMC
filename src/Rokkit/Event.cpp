//
// Created by mwmat on 09/12/2020.
//

#include "Rokkit/Rokkit.h"
typedef int64_t*(*getIdentityName_t)(Rokkit::Event*, Json::Value*);
namespace Rokkit {
    Json::Value* Event::propertiesAsJsonValue() {
        Json::Value* json = new Json::Value();
        auto original = (getIdentityName_t)dlsym(RTLD_DEFAULT, "_ZNK6Social6Events5Event21propertiesAsJsonValueEv");
        original(this, json);
        return json;
    }
}
//
// Created by mwmat on 09/12/2020.
//

#include "Rokkit.h"
#include "hooks.h"

typedef int64_t*(*getIdentityName_t)(Json::Value*, Rokkit::Event*);
namespace Rokkit {
    Json::Value* Event::propertiesAsJsonValue() {
        Json::Value* json = new Json::Value();
        auto original1 = (getIdentityName_t)GetSymbol("_ZNK6Social6Events5Event21propertiesAsJsonValueEv");
        original1(json, this);
        return json;
    }
}
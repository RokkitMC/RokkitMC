//
// Created by mwmat on 07/12/2020.
//
#include "Rokkit/Rokkit.h"
#include "hooks.h"

typedef void (*propertiesAsJsonValue_t)(string*, Rokkit::Certificate*);

namespace Rokkit {
    std::string Certificate::getIdentityName() {
        std::string buff;
        auto original = (propertiesAsJsonValue_t)GetSymbol("_ZN19ExtendedCertificate15getIdentityNameB5cxx11ERK11Certificate");
        original(&buff, this);
        return buff;
    }
}
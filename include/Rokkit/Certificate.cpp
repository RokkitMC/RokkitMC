//
// Created by mwmat on 07/12/2020.
//
#include "Rokkit.h"

typedef void (*getIdentityName_t)(string*, Rokkit::Certificate*);
namespace Rokkit {
    std::string Certificate::getIdentityName() {
        std::string buff;
        auto original = (getIdentityName_t)dlsym(RTLD_DEFAULT, "_ZN19ExtendedCertificate15getIdentityNameB5cxx11ERK11Certificate");
        original(&buff, this);
        return buff;
    }
}

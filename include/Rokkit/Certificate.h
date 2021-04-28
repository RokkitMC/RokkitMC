//
// Created by mwmat on 07/12/2020.
//

#ifndef ROKKITMC_CERTIFICATE_H
#define ROKKITMC_CERTIFICATE_H
#include <dlfcn.h>
#include <string>

namespace Rokkit {
    class Certificate {
    public:
        std::string getIdentityName();
    };
}


#endif //ROKKITMC_CERTIFICATE_H

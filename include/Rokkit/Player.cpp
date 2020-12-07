//
// Created by mwmat on 07/12/2020.
//
#include "Rokkit.h"

namespace Rokkit {
    Player::Player(Certificate* cert) {
        this->certificate = cert;
        this->Name = cert->getIdentityName();
    }
}


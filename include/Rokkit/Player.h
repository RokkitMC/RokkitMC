//
// Created by mwmat on 07/12/2020.
//

#ifndef ROKKITMC_PLAYER_H
#define ROKKITMC_PLAYER_H
#include <iostream>
#include "Certificate.h"
using std::string;

namespace Rokkit {
    class Player {
    public:
        Player(Certificate* cert);
        string Name;
    private:
        Certificate* certificate;
    };
}
#endif //ROKKITMC_PLAYER_H

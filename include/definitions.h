//
// Created by mwmat on 02/12/2020.
//

#ifndef ROKKITMC_DEFINITIONS_H
#define ROKKITMC_DEFINITIONS_H
#include <stdint.h>

typedef int64_t*(__fastcall* playerJoined_t)(int64_t* leaderboard, int64_t plr);
playerJoined_t onPlayerJoinedO;

typedef void(__fastcall* clientAuthenticated_t)(int64_t, int64_t, int64_t);
clientAuthenticated_t onClientAuthenticatedO;

int64_t _handleBase;

int64_t offset(int64_t x)
{
    return ((x) - 0x140000000 + (_handleBase));
}

void DefineTypedefs(int64_t handleBase)
{
    _handleBase = handleBase;
    onPlayerJoinedO = reinterpret_cast<playerJoined_t>(offset(0x1411E5B70));
    onClientAuthenticatedO = reinterpret_cast<clientAuthenticated_t>(offset(0x140993090));
}

#endif //ROKKITMC_DEFINITIONS_H

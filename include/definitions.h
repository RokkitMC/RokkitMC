//
// Created by mwmat on 02/12/2020.
//

#ifndef ROKKITMC_DEFINITIONS_H
#define ROKKITMC_DEFINITIONS_H
#include <stdint.h>

// Player Message received
typedef uint64_t (*playerMessage_t)(uint64_t*, string, string, string, string);

// Client authentication
typedef uint64_t(*clientAuthenticated_t)(int64_t*, int64_t*, Rokkit::Certificate*);

// Record Event
typedef uint64_t(*recordEvent_t)(int64_t*, Rokkit::Event*);

#endif //ROKKITMC_DEFINITIONS_H
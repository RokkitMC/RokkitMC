//
// Created by mwmat on 09/12/2020.
//

#ifndef ROKKITMC_EVENT_H
#define ROKKITMC_EVENT_H
#include "json.h"
namespace Rokkit {
    class Event {
    public:
        Json::Value* propertiesAsJsonValue();
    };
}



#endif //ROKKITMC_EVENT_H

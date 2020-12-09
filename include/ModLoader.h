//
// Created by mwmat on 09/12/2020.
//

#ifndef ROKKITMC_MODLOADER_H
#define ROKKITMC_MODLOADER_H
#include <jni.h>
namespace Rokkit {
    class ModLoader {
    public:
        ModLoader(jint version);

    private:
        JavaVM *_jvm;
        JNIEnv *_env;
    };
}
#endif //ROKKITMC_MODLOADER_H

//
// Created by mwmat on 09/12/2020.
//

#ifndef ROKKITMC_PLUGINLOADER_H
#define ROKKITMC_PLUGINLOADER_H
#include <jni.h>
namespace Rokkit {
    class PluginLoader {
    public:
        PluginLoader(jint version);

    private:
        JavaVM *_jvm;
        JNIEnv *_env;
    };
}
#endif //ROKKITMC_PLUGINLOADER_H

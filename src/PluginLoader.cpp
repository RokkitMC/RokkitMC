//
// Created by mwmat on 09/12/2020.
//
#include "PluginLoader.h"
#include <stdlib.h>
#include "logger.h"
namespace Rokkit {
    PluginLoader::PluginLoader(jint version) {
        Logger::Info("Initialising JVM\n");
        JavaVM *jvm;
        JNIEnv *env;

        JavaVMInitArgs vm_args;
        JavaVMOption* options = new JavaVMOption[1];
        options[0].optionString = "-Djava.class.path=.";
        vm_args.version = version;
        vm_args.nOptions = 1;
        vm_args.options = options;
        vm_args.ignoreUnrecognized = false;

        jint rc = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
        delete options;
        if (rc != JNI_OK) {
            Logger::Error("Error initialising Java environment\n");
            exit(EXIT_FAILURE);
        }

        Logger::Info("JVM initialised\n");
        this->_env = env;
        this->_jvm = jvm;
    }
}
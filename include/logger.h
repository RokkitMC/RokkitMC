//
// Created by mwmat on 07/12/2020.
//

#ifndef ROKKITMC_LOGGER_H
#define ROKKITMC_LOGGER_H
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#include <stdio.h>
#include <string.h>
class Logger {
public:
    static void Info(const char* message) {
        std::cout << WHITE << "[RokkitMC]: " << message << RESET;
    }
    static void Error(const char* message) {
        std::cout << RED << "[RokkitMC]: " << message << RESET;
    }
    static void Warn(const char* message) {
        std::cout << YELLOW << "[RokkitMC]: " << message << RESET;
    }
    static void InfoF(const char* fmt, ...) {
        printf(fmt);
    }
};

#endif //ROKKITMC_LOGGER_H

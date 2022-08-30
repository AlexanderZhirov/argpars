/*
 * argpars.hpp
 *
 *  Created on: 30 авг. 2022 г.
 *      Author: alexander
 */

#pragma once

#include <getopt.h>
#include <vector>
#include <string>
#include <cstring>
#include <map>

class ArgPars
{
private:
    typedef void (*cPtr)();
public:
    enum hasArg {NO, REQUIRED, OPTIONAL};

    ArgPars(cPtr callback = nullptr, bool silencemode = true);
    void readArguments(int argc, char *argv[]);
    void addKey(const char shortKey, const std::string &longKey, hasArg argument);
    bool checkKey(const char shortKey);
    std::string getValue(const char shortKey);
    std::vector<std::string> getValues(const char shortKey);
private:
    struct option *longOptions;
    size_t sizeLongOption;
    char* shortOptions;
    size_t sizeShortOption;
    std::map<char, std::pair<bool, std::vector<std::string>>> cfg;

    cPtr _callback;

    void addShortOption(const char shortKey, hasArg argument);
    struct option createNewOption(const char shortKey, const std::string &longKey, hasArg argument);
    void addLongOption(const char shortKey, const std::string &longKey, hasArg argument);
    void addNullKey();
};

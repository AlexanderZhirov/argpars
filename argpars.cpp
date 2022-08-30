/*
 * argpars.cpp
 *
 *  Created on: 30 авг. 2022 г.
 *      Author: alexander
 */

#include <argpars.hpp>

ArgPars::ArgPars(cPtr callback, bool silencemode) :
        longOptions(nullptr), sizeLongOption(0), shortOptions(nullptr), sizeShortOption(0), _callback(callback)
{
    if (silencemode)
    {
        shortOptions = new char[++sizeShortOption];
        shortOptions[0] = ':';
    }
}

void ArgPars::addShortOption(const char shortKey, hasArg argument)
{
    size_t sizeTemp = sizeShortOption;
    if (argument == hasArg::REQUIRED)
        ++sizeShortOption;
    else if (argument == hasArg::OPTIONAL)
        sizeShortOption += 2;
    char *temp = new char[++sizeShortOption];
    if (sizeTemp)
        strcpy(temp, shortOptions);
    temp[sizeTemp++] = shortKey;
    if (argument == hasArg::REQUIRED)
        temp[sizeTemp] = ':';
    else if (argument == hasArg::OPTIONAL)
        strcpy(&temp[sizeTemp], "::");
    delete[] shortOptions;
    shortOptions = temp;
    cfg[shortKey].first = false;
}

struct option ArgPars::createNewOption(const char shortKey, const std::string &longKey, hasArg argument)
{
    struct option newOption;
    char *name = new char[longKey.length() + 1];
    strcpy(name, longKey.c_str());
    newOption.name = name;
    newOption.has_arg = argument;
    newOption.flag = nullptr;
    newOption.val = shortKey;
    return newOption;
}

void ArgPars::addLongOption(const char shortKey, const std::string &longKey, hasArg argument)
{
    struct option *temp = new struct option[++sizeLongOption];
    for (size_t i = 0; i < sizeLongOption - 1; ++i)
        temp[i] = longOptions[i];
    temp[sizeLongOption - 1] = createNewOption(shortKey, longKey, argument);
    delete[] longOptions;
    longOptions = temp;
}

void ArgPars::readArguments(int argc, char *argv[])
{
    int option_index;
    int next_option;
    while ((next_option = getopt_long(argc, argv, shortOptions, longOptions, &option_index)) != -1)
    {
        if (cfg.count(next_option))
        {
            cfg[next_option].first = true;
            if (optarg)
                cfg[next_option].second.push_back(std::string(optarg));
        }
        if (next_option == '?' && _callback)
            _callback();
    }
}

void ArgPars::addKey(const char shortKey, const std::string &longKey, hasArg argument)
{
    addShortOption(shortKey, argument);
    addLongOption(shortKey, longKey, argument);
}

void ArgPars::addNullKey()
{
    struct option *temp = new struct option[++sizeLongOption];
    for (size_t i = 0; i < sizeLongOption - 1; ++i)
        temp[i] = longOptions[i];
    temp[sizeLongOption - 1] = option
    { nullptr, 0, nullptr, 0 };
    delete[] longOptions;
    longOptions = temp;
}

bool ArgPars::checkKey(const char shortKey)
{
    return cfg.count(shortKey) > 0 && cfg[shortKey].first;
}

std::string ArgPars::getValue(const char shortKey)
{
    if (cfg.count(shortKey) && cfg[shortKey].first)
    {
        if (cfg[shortKey].second.size())
            return cfg[shortKey].second.front();
    }
    return {};
}

std::vector<std::string> ArgPars::getValues(const char shortKey)
{
    if (cfg.count(shortKey) && cfg[shortKey].first)
        return cfg[shortKey].second;
    return {};
}

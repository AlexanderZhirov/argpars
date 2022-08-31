/*
 * argpars.hpp
 *
 *  Created on: 30 авг. 2022 г.
 *      Author: alexander
 */

#pragma once

#include <iostream>
#include <getopt.h>

#include <vector>
#include <string>
#include <cstring>
#include <map>

#include <boost/range/adaptors.hpp>
#include <iostream>

namespace args
{

enum hasArg
{
    NO, REQUIRED, OPTIONAL
};

typedef std::vector<std::string> (*_handler)(const std::vector<std::string>&);

class ConfigOption
{
private:
    char *_longParameter;
    const char _shortParameter;
    const hasArg _ha;
    const _handler _h;
public:
    ConfigOption(const std::string &longParameter, const char shortParameter, const hasArg ha, _handler h = nullptr);
    const char* getLongParameter() const;
    const char& getShortParameter() const;
    const hasArg& getPresenceArgument() const;
    const _handler getHandler() const;
};

class Option
{
private:
    _handler _h;
    std::vector<std::string> _values;
    std::vector<std::string> _handling() const;
public:
    Option(const _handler h = nullptr);
    void push(const std::string &value);
    std::vector<std::string> getValues(bool handling = false);
};

class Hub
{
private:
    struct option *_longOptions;
    char *_shortOptions;
    std::map<char, std::pair<bool, Option>> _arguments;
    void _createArguments(const std::vector<ConfigOption> &options, bool silence);
public:
    Hub(const std::vector<ConfigOption> &options, bool silence = true);
    void readArguments(int argc, char *argv[], void (*_callback)() = nullptr);
    Option getOption(char key) const;
    ~Hub();
};

}

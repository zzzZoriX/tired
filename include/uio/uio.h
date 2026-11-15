#pragma once

#include "colors.h"
#include <string>


class uio {
public:
    static void ok(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
    static void info(const std::string& msg);
};
#include "../../include/uio/uio.h"
#include <iostream>
#include <format>


void uio::ok(const std::string& msg) {
#ifdef _WIN32
    std::cout << GREEN << "[OK] ";
    RESET;
    std::cout << msg << std::endl;
#else
    std::cout << std::format("{}[OK]{} {}", GREEN, RESET, msg) << std::endl;
#endif
}

void uio::warn(const std::string& msg) {
#ifdef _WIN32
    std::cout << YELLOW << "[WARN] ";
    RESET;
    std::cout << msg << std::endl;
#else
    std::cout << std::format("{}[WARN]{} {}", YELLOW, RESET, msg) << std::endl;
#endif
}

void uio::error(const std::string& msg) {
#ifdef _WIN32
    std::cout << RED << "[ERROR] ";
    RESET;
    std::cout << msg << std::endl;
#else
    std::cout << std::format("{}[ERROR]{} {}", RED, RESET, msg) << std::endl;
#endif
}

void uio::info(const std::string& msg) {
#ifdef _WIN32
    std::cout << BLUE << "[INFO] ";
    RESET;
    std::cout << msg << std::endl;
#else
    std::cout << std::format("{}[INFO]{} {}", BLUE, RESET, msg) << std::endl;
#endif
}
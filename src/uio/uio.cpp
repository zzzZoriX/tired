#include "../../include/uio/uio.h"
#include "../../include/uio/input_map.h"
#include "../../include/uio/colors.h"
#include "../../include/executor/executor.h"
#include <iostream>
#include <format>


void uio::ok(const std::string& msg) {
#ifdef _WIN32
    GREEN;
    std::cout << "[OK] ";
    RESET;
    std::cout << msg << std::endl;
#else
    std::cout << std::format("{}[OK]{} {}", GREEN, RESET, msg) << std::endl;
#endif
}

void uio::warn(const std::string& msg) {
#ifdef _WIN32
    YELLOW;
    std::cout << "[WARN] ";
    RESET;
    std::cout << msg << std::endl;
#else
    std::cout << std::format("{}[WARN]{} {}", YELLOW, RESET, msg) << std::endl;
#endif
}

void uio::error(const std::string& msg) {
#ifdef _WIN32
    RED;
    std::cout << "[ERROR] ";
    RESET;
    std::cout << msg << std::endl;
#else
    std::cout << std::format("{}[ERROR]{} {}", RED, RESET, msg) << std::endl;
#endif
}

void uio::info(const std::string& msg) {
#ifdef _WIN32
    BLUE;
    std::cout << "[INFO] ";
    RESET;
    std::cout << msg << std::endl;
#else
    std::cout << std::format("{}[INFO]{} {}", BLUE, RESET, msg) << std::endl;
#endif
}

void uio::only_msg(const std::string& msg) {
    std::cout << msg << std::endl;
}

void uio::init_uinput(void) {
    uinput_thread = std::jthread(&uio::input_thread);
}

void uio::input_thread(std::stop_token stoken) {
    std::string input;

    while(!stoken.stop_requested()) {
        if(!std::getline(std::cin, input)) {
            uio::ok("Quitting...");
            break;
        }

        const auto code{get_code(input)};

        if(executor::get_instance().execute(code) == -1)
            return;
    }
}

void uio::wait(void) {
    if(uinput_thread.joinable())
        uinput_thread.join();
}
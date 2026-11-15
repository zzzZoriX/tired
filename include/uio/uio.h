#pragma once

#include <string>
#include <thread>


class uio {
    std::jthread uinput_thread;

public:
    static void ok(const std::string& msg);
    static void warn(const std::string& msg);
    static void error(const std::string& msg);
    static void info(const std::string& msg);
    static void only_msg(const std::string& msg);

    void init_uinput(void);
    void wait(void);

private:
    static void input_thread(std::stop_token stoken);
};
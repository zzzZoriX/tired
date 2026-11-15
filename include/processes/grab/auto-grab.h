#pragma once

#include <thread>
#include <chrono>


class auto_grab {
    std::jthread timer_thread;
    std::chrono::milliseconds wait{5000};
    bool running;

public:
    void start(void);
    void stop(void);
    void set_wait_time(std::chrono::milliseconds wait);
    bool get_status(void) const;

private:
    static void timer(std::stop_token stoken, std::chrono::milliseconds wait);
};
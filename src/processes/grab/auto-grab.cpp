#include "../../../include/processes/grab/auto-grab.h"
#include "../../../include/processes/grab/grab.h"
#include <condition_variable>
#include <mutex>


void auto_grab::start(void) {
    running = true;
    timer_thread = std::jthread(&auto_grab::timer, wait);
}

void auto_grab::stop(void) {
    running = false;
    timer_thread.request_stop();
}

void auto_grab::set_wait_time(std::chrono::milliseconds wait) {
    this->wait = wait;
}

bool auto_grab::get_status(void) const {
    return running;
}


void auto_grab::timer(std::stop_token stoken, std::chrono::milliseconds wait) {
    std::mutex mutex;
    std::condition_variable_any cv;
    std::unique_lock lock{mutex};

    while(!stoken.stop_requested()) {
        cv.wait_for(lock, stoken, wait, [] { return false; });

        if(stoken.stop_requested())
            break;

        grab::save_processes(grab::grab_processes());
    }
}
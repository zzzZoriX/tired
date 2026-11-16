#include "../../include/executor/executor.h"
#include "../../include/uio/uio.h"
#include "../../include/uio/help.h"
#include "../../include/processes/grab/grab.h"
#include "../../include/processes/restore/restore.h"
#include <iostream>


executor& executor::get_instance(void) {
    static executor instance;
    return instance;
}

int executor::execute(const int code) {
    switch(code) {
        case 0:
            uio::ok("Quitting...");
            return -1;
        case 1:
            uio::only_msg(HELP_MESSAGE);
            break;
        case 2:
            grab::save_processes(grab::grab_processes());
            break;
        case 3:
            restore::restore_processes();
            break;
        case 4:
            if(auto_grab_.get_status()) {
                auto_grab_.stop();
                uio::ok("auto grab disabled.");
            }
            else {
                auto_grab_.start();
                uio::ok("auto grab enabled.");
            }
            break;
        case 5: {
            std::string new_wait_time;

            uio::only_msg("Enter the new wait time(in milliseconds): ");
            std::getline(std::cin, new_wait_time);

            auto_grab_.set_wait_time(std::chrono::milliseconds(std::stol(new_wait_time)));

            uio::info("The wait time for Auto Grab has been successfully changed. To apply the changes, please restart Auto Grab.");

            break;
        }
        default:
            uio::warn("Unknown command.");
            break;
    }

    return 0;
}
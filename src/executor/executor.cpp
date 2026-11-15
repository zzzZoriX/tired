#include "../../include/executor/executor.h"
#include "../../include/uio/uio.h"
#include "../../include/uio/help.h"
#include "../../include/processes/grab/grab.h"


executor& executor::get_instance(void) {
    static executor instance;
    return instance;
}

int executor::execute(const int code) const {
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
            break;
        case 4:
            break;
        case 5:
            break;
        default:
            uio::warn("Unknown command.");
            break;
    }

    return 0;
}
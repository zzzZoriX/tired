#include "../include/uio/uio.h"
#include "../include/processes/files.h"


int main(void) {
    if(!check())
        uio::warn("The directory required for 'tired' to function was not found. A new one has been created.");

    uio user_io;

    user_io.init_uinput();
    user_io.wait();

    return 0;
}
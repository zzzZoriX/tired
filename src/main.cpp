#include "../include/uio/uio.h"
#include <string>


int main(void) {
    uio user_io;

    user_io.init_uinput();
    user_io.wait();

    return 0;
}
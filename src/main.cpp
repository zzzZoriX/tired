#include "../include/uio/uio.h"


int main(void) {
    uio::ok("This is an OK message.");
    uio::warn("This is a warning message.");
    uio::error("An error has occurred.");
    uio::info("This is an informational message.");

    return 0;
}
#pragma once

#include "../../include/processes/grab/auto-grab.h"


class executor {
    auto_grab auto_grab_;

public:
    executor(const executor&) = delete;
    executor(const executor&&) = delete;
    executor& operator=(const executor&) = delete;
    executor& operator=(const executor&&) = delete;

    static executor& get_instance(void);
    
    int execute(const int code);

private:
    executor(void) = default;
    ~executor(void) = default;
};
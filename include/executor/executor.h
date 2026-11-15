#pragma once


class executor {
public:
    executor(const executor&) = delete;
    executor(const executor&&) = delete;
    executor& operator=(const executor&) = delete;
    executor& operator=(const executor&&) = delete;

    static executor& get_instance(void);
    
    int execute(const int code) const;

private:
    executor(void) = default;
    ~executor(void) = default;
};
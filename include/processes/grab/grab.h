#pragma once

#include <vector>
#include <filesystem>


class grab {
public:
    grab(const grab&) = delete;
    grab(grab&&) = delete;
    grab& operator=(const grab&) = delete;
    grab& operator=(grab&&) = delete;
    grab(void) = delete;
    ~grab(void) = delete;

    static std::vector<std::filesystem::path> grab_processes(void);
    static void save_processes(const std::vector<std::filesystem::path>& processes);

private:
    static std::filesystem::path get_process_path(const std::uint32_t pid);   
};
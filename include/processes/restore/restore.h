#pragma once

#include <vector>
#include <filesystem>
#include <string>
#include <optional>


class restore {
public:
    static void restore_processes(void);

private:
    static std::optional<std::vector<std::filesystem::path>> read_tpf(void);
    static bool is_active(const std::filesystem::path& path);
    static bool restore_process(const std::filesystem::path& path);
};
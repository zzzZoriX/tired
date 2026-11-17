#pragma once

#include <unordered_set>
#include <string>
#include <optional>
#include <expected>


class ignore {
public:
    static std::expected<void, std::string> add(const std::string& process);
    static std::expected<void, std::string> remove(const std::string& process);
    static std::expected<bool, std::string> is_ignored(const std::string& process);

private:
    static std::optional<std::unordered_set<std::string>> get_ignored(void);
};
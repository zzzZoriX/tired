#include "../../../include/processes/ignore/ignore.h"
#include "../../../include/processes/files.h"
#include <fstream>
#include <format>


std::optional<std::unordered_set<std::string>> ignore::get_ignored(void) {
    std::ifstream file{get_home_path() / "tired/processes/ignored.txt", std::ios::in};
    if(!file.is_open())
        return std::nullopt;

    std::unordered_set<std::string> ignored;
    std::string ignored_process;

    while(std::getline(file, ignored_process)) 
        ignored.insert(ignored_process);

    return ignored;
}

std::expected<void, std::string> ignore::add(const std::string& process) {
    auto ignored_processes{ignore::get_ignored()};
    if(!ignored_processes.has_value())
        return std::unexpected(std::format("Can't open {} file.", (get_home_path() / "tired/processes/ignored.txt").string()));

    auto insert_result{ignored_processes.value().insert(process).second};
    if(!insert_result)
        return std::unexpected("Process is already ignored.");
        
    std::ofstream file{get_home_path() / "tired/processes/ignored.txt", std::ios::out | std::ios::trunc};
    if(!file.is_open())
        return std::unexpected(std::format("Can't open {} file.", (get_home_path() / "tired/processes/ignored.txt").string()));

    for(const auto& process: ignored_processes.value())
        file << process << std::endl;

    return {};
}

std::expected<void, std::string> ignore::remove(const std::string& process) {
    auto ignored_processes{ignore::get_ignored()};
    if(!ignored_processes.has_value())
        return std::unexpected(std::format("Can't open {} file.", (get_home_path() / "tired/processes/ignored.txt").string()));

    auto insert_result{ignored_processes.value().insert(process)};
    if(insert_result.second)
        return std::unexpected("The process is not being ignored.");
    else
        ignored_processes.value().erase(insert_result.first);

    std::ofstream file{get_home_path() / "tired/processes/ignored.txt", std::ios::out | std::ios::trunc};
    if(!file.is_open())
        return std::unexpected(std::format("Can't open {} file.", (get_home_path() / "tired/processes/ignored.txt").string()));

    for(const auto& process: ignored_processes.value())
        file << process << std::endl;

    return {};
}

std::expected<bool, std::string> ignore::is_ignored(const std::string& process) {
    auto ignored_processes{ignore::get_ignored()};
    if(!ignored_processes.has_value())
        return std::unexpected(std::format("Can't open {} file.", (get_home_path() / "tired/processes/ignored.txt").string()));

    auto insert_result{ignored_processes.value().insert(process).second};
    if(!insert_result)
        return true;
    else
        return false;
}
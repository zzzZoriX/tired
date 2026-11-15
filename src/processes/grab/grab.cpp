#include "../../../include/processes/grab/grab.h"
#include "../../../include/processes/files.h"
#include "../../../include/uio/uio.h"
#include <fstream>
#include <algorithm>

#ifdef _WIN32
#include <windows.h>
#include <TlHelp32.h>
#else
#include <array>
#endif


void grab::save_processes(const std::vector<std::filesystem::path>& processes) {
    std::ofstream file{get_home_path() / "tired/processes/processes.txt", std::ios::out | std::ios::trunc};
    if(!file.is_open()) {
        uio::error("Failed to open processes.txt for writing.");
        return;
    }

    for(const auto& process : processes)
        file << process.string() << std::endl;

    uio::ok("Processes saved successfully.");
}

std::vector<std::filesystem::path> grab::grab_processes(void) {
    std::vector<std::filesystem::path> processes;
    
#ifdef _WIN32
    HANDLE snapshot{CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)};

    if(snapshot == INVALID_HANDLE_VALUE)
        return;

    PROCESSENTRY32 entry{};
    entry.dwSize{sizeof(PROCESSENTRY32)};

    if(Process32First(snapshot, &entry)) {
        do {
            processes.push_back(get_process_path(std::stoul(entry.th32ProcessID)));
        } while(Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
#else
    for(const auto& entry : std::filesystem::directory_iterator("/proc")) {
        if(!entry.is_directory()) 
            continue;

        const auto pid{entry.path().filename().string()};

        if(pid.empty() || !std::all_of(pid.begin(), pid.end(), ::isdigit))
            continue;

        processes.push_back(get_process_path(std::stoul(pid)));
    }
#endif

    return processes;
}

std::filesystem::path grab::get_process_path(const std::uint32_t pid) {
    std::string path;

#ifdef _WIN32
    HANDLE process{OpenProcess(
        PROCESS_QUERY_LIMITED_INFORMATION,
        FALSE,
        pid
    )};

    if(!process)
        return {};

    std::vector<char> buffer(32768);
    DWORD size{static_cast<DWORD>(buffer.size())};

    if(QueryFullProcessImageNameA(
        process,
        0,
        buffer.data(),
        &size
    )) path.assign(buffer.data(), size);

    CloseHandle(process);
#else
    std::string link{"/proc/" + std::to_string(pid) + "/exe"};

    std::array<char, 4096> buffer{};

    ssize_t length{readlink(
        link.c_str(),
        buffer.data(),
        buffer.size() - 1
    )};

    if(length == -1)
        return {};

    path.assign(buffer.data(), length);
#endif

    return path;
}
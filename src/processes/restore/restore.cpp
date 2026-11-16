#include "../../../include/processes/restore/restore.h"
#include "../../../include/processes/files.h"
#include "../../../include/uio/uio.h"
#include <fstream>
#include <format>
#include <boost/process/v2/process.hpp>
#include <boost/process/v2/stdio.hpp>
#include <boost/asio/io_context.hpp>

#ifdef _WIN32
    #include <windows.h>
    #include <tlhelp32.h
#endif


bool restore::is_active(const std::string& path) {
#ifdef _WIN32
    auto to_lower{[](std::wstring str) { std::transform(str.begin(), str.end(), str.begin(), ::tolower); return str}};
    int size_needed{MultiByteToWideChar(CP_UTF8, 0, path.data(), (int)path.size(), nullptr, 0)};
    std::wstring wpath(size_needed, 0);
    MultiByteToWideChar(CP_UTF8, 0, path.data(), (int)path.size(), &wpath[0], size_needed);

    std::wstring lpath{ToLower(wpath)};
    HANDLE hsnapshot{CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0)};
    if(hsnapshot == INVALID_HANDLE_VALUE) 
        return false;

    PROCESSENTRY32W pe32;
    pe32.dwSize{sizeof(PROCESSENTRY32W)};

    if(Process32FirstW(hsnapshot, &pe32)) {
        do {
            HANDLE hproc = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe32.th32ProcessID);
            if(hproc) {
                wchar_t buffer[MAX_PATH];
                DWORD size{MAX_PATH};
                if(QueryFullProcessImageNameW(hproc, 0, buffer, &size)) {
                    if(ToLower(buffer) == lpath) {
                        CloseHandle(hproc);
                        CloseHandle(hproc);
                        return true;
                    }
                }
                CloseHandle(hproc);
            }
        } while(Process32NextW(hsnapshot, &pe32));
    }

    CloseHandle(hsnapshot);
#else
    std::error_code ec;
    std::filesystem::path ct{std::filesystem::weakly_canonical(path, ec)};

    for(const auto& entry: std::filesystem::directory_iterator("/proc", ec)) {
        if(!std::filesystem::is_directory(entry))
            continue;

        const auto filename{entry.path().filename().string()};
        if(filename.find_first_not_of("012345789") != std::string::npos)
            continue;

        std::filesystem::path exe{entry.path() / "exe"};
        std::filesystem::path actual_path{std::filesystem::read_symlink(exe, ec)};

        if(!ec && actual_path == path)
            return true;
    }
#endif

    return false;
}

std::optional<std::vector<std::filesystem::path>> restore::read_tpf(void) {
    std::ifstream file{get_home_path() / "tired/processes/processes.txt", std::ios::in};
    if(!file.is_open()) {
        uio::error("Failed to open processes.txt for reading.");
        return std::nullopt;
    }

    std::string process;
    std::vector<std::filesystem::path> processes;
    while(std::getline(file, process))
        processes.push_back(process);

    return processes;
}


void restore::restore_processes(void) {
    const auto processes{restore::read_tpf()};
    if(!processes.has_value())
        return;

    for(const auto& process: processes.value()) {
        if(!restore::is_active(process)) {
            auto result{restore::restore_process(process)};
        
            if(!result)
                uio::info(std::format("Process {} cannot be restored.", process.filename().string()));
        }
    }
}

bool restore::restore_process(const std::filesystem::path& path) {
    try {
        boost::asio::io_context ioc;

        boost::process::process proc{
            ioc, 
            path.string(), 
            {}, 
            boost::process::v2::process_stdio{nullptr, nullptr, nullptr}
        };
        proc.detach();

        return true;
    }
    catch(const std::exception& e) {
        uio::error(std::format("Restore error: {}", e.what()));
        return false;
    }
}
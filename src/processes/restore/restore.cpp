#include "../../../include/processes/restore/restore.h"
#include "../../../include/processes/files.h"
#include "../../../include/processes/grab/grab.h"
#include "../../../include/uio/uio.h"
#include <fstream>
#include <format>
#include <boost/process/v2/process.hpp>
#include <boost/process/v2/stdio.hpp>
#include <boost/asio/io_context.hpp>


bool restore::is_active(const std::string& path) {
    return grab::grab_processes().contains(path);
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
        if(!restore::is_active(process.string())) {
            auto result{restore::restore_process(process)};
        
            if(!result)
                uio::info(std::format("Process {} cannot be restored.", process.filename().string()));
            else
                uio::info(std::format("Process {} has been restored.", process.filename().string()));
        }
        else 
            uio::warn(std::format("Process {} already launched.", process.filename().string()));
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
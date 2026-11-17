#include "../../include/processes/files.h"
#include <fstream>

#ifdef _WIN32
    #include <windows.h>
#endif

std::filesystem::path get_home_path(void) {
#if defined(_WIN32)
    wchar_t user_profile[MAX_PATH];

    if (GetEnvironmentVariableW(
        L"USERPROFILE",
        user_profile,
        MAX_PATH
    )) {
        return std::filesystem::path(user_profile);
    }
#else
    const char* home{std::getenv("HOME")};
    if(home) {
        return std::filesystem::path(home);
    }
#endif

    return std::filesystem::path();
}

bool check(void) {
    bool check_result{true};
    const auto td_path{get_home_path() / "tired"};

    if(!std::filesystem::exists(td_path)) {
        std::filesystem::create_directory(td_path);
        check_result = false;
    }
    if(!std::filesystem::exists(td_path / "processes")) {
        std::filesystem::create_directory(td_path / "processes");
        check_result = false;
    }
    if(!std::filesystem::exists(td_path / "processes/ignored.txt")) {
        std::ofstream file_creator{td_path / "processes/ignored.txt", std::ios::out};
        check_result = false;
    }

    return check_result;
}
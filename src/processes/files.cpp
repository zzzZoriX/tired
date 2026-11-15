#include "../../include/processes/files.h"


std::filesystem::path get_home_path(void) {
#if defined(_WIN32)
    const char* user_profile{std::getenv("USERPROFILE")};
    if(user_profile) {
        return std::filesystem::path(user_profile);
    }
    const char* home_drive{std::getenv("HOMEDRIVE")};
    const char* home_path{std::getenv("HOMEPATH")};
    if(home_drive && home_path) {
        return std::filesystem::path(home_drive) / home_path;
    }
#else
    const char* home{std::getenv("HOME")};
    if(home) {
        return std::filesystem::path(home);
    }
#endif

    return std::filesystem::path();
}
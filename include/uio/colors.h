#pragma once

#ifdef _WIN32
    #include <windows.h>

    #define RED FOREGROUND_RED | FOREGROUND_INTENSITY
    #define GREEN FOREGROUND_GREEN | FOREGROUND_INTENSITY
    #define YELLOW FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
    #define BLUE FOREGROUND_BLUE | FOREGROUND_INTENSITY
    #define RESET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), defaultAttributes)
#else
    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"
    #define RESET "\033[0m"
#endif
#pragma once
#include <Windows.h>
#include <string>

namespace SafeUtils {
    void clearScreen();
    void setConsoleColor(const std::string& colorCode);
}
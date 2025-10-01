#include "SafeUtils.hpp"

void SafeUtils::clearScreen() {
    COORD coordScreen = { 0, 0 };
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    
    if (hConsole == INVALID_HANDLE_VALUE) return;
    
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    
    if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten)) return;
    
    if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    
    if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) return;
    
    SetConsoleCursorPosition(hConsole, coordScreen);
}

void SafeUtils::setConsoleColor(const std::string& colorCode) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;
    
    WORD color = 0;
    if (colorCode.length() >= 2) {
        int bg = 0, fg = 0;
        if (colorCode[0] >= '0' && colorCode[0] <= '9') bg = colorCode[0] - '0';
        else if (colorCode[0] >= 'A' && colorCode[0] <= 'F') bg = colorCode[0] - 'A' + 10;
        
        if (colorCode[1] >= '0' && colorCode[1] <= '9') fg = colorCode[1] - '0';
        else if (colorCode[1] >= 'A' && colorCode[1] <= 'F') fg = colorCode[1] - 'A' + 10;
        
        color = (bg << 4) | fg;
        SetConsoleTextAttribute(hConsole, color);
    }
}
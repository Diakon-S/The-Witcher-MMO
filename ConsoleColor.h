#pragma once
#include <windows.h>
#include <iostream>

namespace Color {
    const int Default = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    const int Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    const int Gray = FOREGROUND_INTENSITY;
    const int Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int Red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    const int Magenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    const int Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    inline void set(int colorCode) {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode);
    }
}
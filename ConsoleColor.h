#pragma once
#define NOMINMAX
#include <windows.h>
#include <iostream>

namespace Color {
    const int Default = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    const int Green = FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int DarkGreen = FOREGROUND_GREEN;
    const int Blue = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    const int Gray = FOREGROUND_INTENSITY;
    const int Yellow = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
    const int Red = FOREGROUND_RED | FOREGROUND_INTENSITY;
    const int Magenta = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    const int Cyan = FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;

    inline void set(int colorCode) { SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorCode); }

    inline void gotoxy(int x, int y) {
        COORD coord = { (SHORT)x, (SHORT)y };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
    }
    inline void hideCursor() {
        CONSOLE_CURSOR_INFO cursorInfo;
        GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
        cursorInfo.bVisible = false;
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }
    inline void setupConsole() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        COORD newSize = { 130, 50 };
        SetConsoleScreenBufferSize(hOut, newSize);
        SMALL_RECT windowSize = { 0, 0, 129, 49 };
        SetConsoleWindowInfo(hOut, TRUE, &windowSize);
        hideCursor();
    }

    inline void clearScreen() {
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count;
        DWORD cellCount;
        COORD homeCoords = { 0, 0 };

        if (hOut == INVALID_HANDLE_VALUE) return;
        if (!GetConsoleScreenBufferInfo(hOut, &csbi)) return;
        cellCount = csbi.dwSize.X * csbi.dwSize.Y;

        FillConsoleOutputCharacter(hOut, (TCHAR)' ', cellCount, homeCoords, &count);
        FillConsoleOutputAttribute(hOut, csbi.wAttributes, cellCount, homeCoords, &count);
        SetConsoleCursorPosition(hOut, homeCoords);
    }
}
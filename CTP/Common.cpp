#include "Common.h"

#ifdef _WIN32
#include <Windows.h>
#else
#include <stdio.h>
#endif

void SleepFor(int milliseconds)
{
	std::chrono::milliseconds tsleep(milliseconds);
	std::this_thread::sleep_for(tsleep);
}

void InitScreen()
{
	system("mode con:cols=110  lines=31");
	SetCursorPosition(90, 0);
	std::cout << "     " << ppInstrumentID[0];
	SetCursorPosition(90, 1);
	std::cout << "Ask: ";
	SetCursorPosition(90, 2);
	std::cout << "-----------------";
	SetCursorPosition(90, 3);
	std::cout << "Bid: ";
	SetCursorPosition(0, 0);
}

#ifdef _WIN32
CONSOLE_SCREEN_BUFFER_INFO cursor_info;
HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
void SetCursorPosition(int x, int y)
{
	COORD cursorPosition;
	cursorPosition.X = x;
	cursorPosition.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

void StoreCursorPosition()
{
	GetConsoleScreenBufferInfo(handle, &cursor_info);
}

void RestoreCursorPosition()
{
	COORD cursorPosition;
	cursorPosition.X = cursor_info.dwCursorPosition.X;
	cursorPosition.Y = cursor_info.dwCursorPosition.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}
#else
void SetCursorPosition(int x, int y)
{
	printf("%c[%d;%df", 0x1b, y, x);
}
#endif

#ifdef _WIN32
void SetTextColor(int back_color, int fore_color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), back_color|fore_color|FOREGROUND_INTENSITY);
}

void RestoreTextColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
}
#else
void SetTextColor(int back_color, int fore_color)
{
	printf("%c[%d;%dm", 0x1b, fore_color, back_color);
}

#endif
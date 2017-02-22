#pragma once

#include "vars.h"
#include "DisplayBuffer.h"
#include <chrono>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <Windows.h>
#endif

class MdSpi;
class TdSpi;


void SleepFor(int milliseconds);
void InitScreen();
void InitThreads();
void StoreCursorPosition(COORD* coord);
void RestoreCursorPosition(COORD* coord);

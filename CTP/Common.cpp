#include "Common.h"

void SleepFor(int milliseconds)
{
	std::chrono::milliseconds tsleep(milliseconds);
	std::this_thread::sleep_for(tsleep);
}
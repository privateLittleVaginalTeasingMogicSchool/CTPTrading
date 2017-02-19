#define _CRT_SECURE_NO_WARNINGS

#include "Common.h"
#include "command.h"

#include <conio.h>

COORD command::coord;
char command::buffer[1024] = { 0 };
char* command::pbuf = buffer;
bool command::can_input = true;

void command::thread_work()
{
	while (true)
	{
		if (char c = _getch())
		{
			if (!can_input)
				continue;
			StoreCursorPosition(&coord);
			SetCursorPosition(pbuf - buffer + 10, 49);
			switch (c)
			{
				case VK_RETURN:
					{
						int len = (int)(pbuf - buffer);
						for (int i = 0;i < len; i++)
						{
							putchar('\b');
						}
						for (int i = 0;i < len; i++)
						{
							putchar(' ');
						}
						for (int i = 0;i < len; i++)
						{
							putchar('\b');
						}
						*pbuf = 0;
						can_input = false;
						std::thread tmp_thread(analyze_command);
					}
					break;
				case VK_BACK:
					{
						pbuf--;
						puts("\b \b");
					}
					break;
				default:
					{
						*(pbuf++) = c;
						putchar(c);
					}
					break;
			}
			RestoreCursorPosition(&coord);
		}
	}
}

void command::analyze_command()
{
	char _cmd[1024];
	strcpy(_cmd, buffer);
	pbuf = buffer;
	can_input = true;
	return;
}
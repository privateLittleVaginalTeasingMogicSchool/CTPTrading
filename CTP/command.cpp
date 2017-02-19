#define _CRT_SECURE_NO_WARNINGS

#include "Common.h"
#include "command.h"

#include <conio.h>

COORD command::coord;
char command::buffer[1024] = { 0 };
char* command::pbuf = buffer;
bool command::can_input = true;
std::thread* command::Analyzer = nullptr;

void command::thread_work()
{
	while (true)
	{
		if (char c = _getch())
		{
			if (!can_input)
				continue;
			_Get_Output_Mutex
			StoreCursorPosition(&coord);
			SetCursorPosition(pbuf - buffer + 10, 49);
			switch (c)
			{
				case VK_RETURN:
					{
						can_input = false;
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
						Analyzer = new std::thread(analyze_command);
					}
					break;
				case VK_BACK:
					{
						if (pbuf>buffer)
						{
							pbuf--;
							puts("\b \b");
						}
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
			_Release_Output_Mutex
		}
	}
}

/*
* 命令：
*   h                帮助
*   cl               清除屏幕
*   b [num]          买num手
*   s [num]          卖num手
*   cb [num]         平买num手
*   cs [num]         平卖num手
*   q                停止自动交易
*   rs               （重新）开始自动交易
*   exit             退出程序
*/

void command::analyze_command()
{
	while (!Analyzer);
	char cmd[1024];
	strcpy(cmd, buffer);
	pbuf = buffer;
	can_input = true;

	switch (cmd[0])
	{
		case 'h':
			//_Get_Output_Mutex
			lgr << Log::t << "[cm]b [num]          买num手" << Log::endl
				<< Log::t << "[cm]s [num]          卖num手" << Log::endl
				<< Log::t << "[cm]cb [num]         平买num手" << Log::endl
				<< Log::t << "[cm]cs [num]         平卖num手" << Log::endl
				<< Log::t << "[cm]q                停止自动交易" << Log::endl
				<< Log::t << "[cm]rs               （重新）开始自动交易" << Log::endl
				<< Log::t << "[cm]exit             退出程序" << Log::endl;
			//_Release_Output_Mutex
			break;
		case 'b':
			break;
		case 's':
			break;
		case 'c':
			{
				switch (cmd[1])
				{
					case 'b':
						break;
					case 's':
						break;
					case 'l':
						system("cls");
						InitScreen();
						break;
					default:
						_Get_Output_Mutex
						lgr << Log::t << "[cm]Illegal Input!" << Log::endl;
						_Release_Output_Mutex
						break;
				}
			}
		case 'q':
			break;
		case 'r':
			break;
		case 'e':
			break;
		default:
			_Get_Output_Mutex
			lgr << Log::t << "[cm]Illegal Input!" << Log::endl;
			_Release_Output_Mutex
			break;
	}

	Analyzer = nullptr;
}
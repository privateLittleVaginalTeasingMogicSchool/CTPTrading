#define _CRT_SECURE_NO_WARNINGS

#include "Common.h"
#include "command.h"
#include "Trade.h"
#include "Query.h"

#include <conio.h>
#include <sstream>

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
			SetCursorPosition(pbuf - buffer + 12, BUFFER_ROW_NUM - 2);
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
						if (pbuf - buffer < 50)
						{
							*(pbuf++) = c;
							putchar(c);
						}
						else
							break;
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
*   t                查看所有订单
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

	std::string cmdstr = cmd;
	lgr << Log::t << "[cm]Command Received (" << cmd << ")" << Log::endl;

	if (cmdstr == "h")
	{
		lgr << Log::t << "[cm]b [num]          买num手" << Log::endl
			<< Log::t << "[cm]s [num]          卖num手" << Log::endl
			<< Log::t << "[cm]cb [num]         平买num手" << Log::endl
			<< Log::t << "[cm]cs [num]         平卖num手" << Log::endl
			<< Log::t << "[cm]t                查看所有订单" << Log::endl
			<< Log::t << "[cm]q                停止自动交易" << Log::endl
			<< Log::t << "[cm]rs               （重新）开始自动交易" << Log::endl
			<< Log::t << "[cm]exit             退出程序" << Log::endl;
	}
	
	else if (cmdstr == "cl")
	{
		system("cls");
		InitScreen();
	}
	
	else if (cmdstr[0] == 'b')
	{
		if (cmdstr[1] == ' ')
		{
			try
			{
				std::stringstream ss(cmd + 2);
				int lot = 0;
				ss >> lot;
				OrderSend(ppInstrumentID[0], THOST_FTDC_OF_Open, THOST_FTDC_D_Buy, lot);
			}

			catch (std::exception)
			{
				lgr << Log::t << "[cm]Illegal Command" << Log::endl;
			}
		}
		else
			lgr << Log::t << "[cm]Illegal Command" << Log::endl;
	}

	else if (cmdstr[0] == 's')
	{
		if (cmdstr[1] == ' ')
		{
			try
			{
				std::stringstream ss(cmd + 2);
				int lot = 0;
				ss >> lot;
				OrderSend(ppInstrumentID[0], THOST_FTDC_OF_Open, THOST_FTDC_D_Sell, lot);
			}

			catch (std::exception)
			{
				lgr << Log::t << "[cm]Illegal Command" << Log::endl;
			}
		}
		else
			lgr << Log::t << "[cm]Illegal Command" << Log::endl;
	}

	else if (cmdstr[0] == 'c')
	{
		if (cmdstr[1] == 'b')
		{
			try
			{
				std::stringstream ss(cmd + 3);
				int lot = 0;
				ss >> lot;
				OrderSend(ppInstrumentID[0], THOST_FTDC_OF_CloseToday, THOST_FTDC_D_Sell, lot);
			}

			catch (std::exception)
			{
				lgr << Log::t << "[cm]Illegal Command" << Log::endl;
			}
		}
		else if (cmdstr[1] == 's')
		{
			try
			{
				std::stringstream ss(cmd + 3);
				int lot = 0;
				ss >> lot;
				OrderSend(ppInstrumentID[0], THOST_FTDC_OF_CloseToday, THOST_FTDC_D_Buy, lot);
			}

			catch (std::exception)
			{
				lgr << Log::t << "[cm]Illegal Command" << Log::endl;
			}
		}
		else
			lgr << Log::t << "[cm]Illegal Command" << Log::endl;
	}

	else if (cmdstr == "accinfo")
	{
		tdspi->ReqQryTradingAccount();
	}

	else if (cmdstr == "exit")
	{
		// TODO: Safely terminate the program.
	}

	else
		lgr << Log::t << "[cm]Illegal Command" << Log::endl;
	Analyzer = nullptr;
}
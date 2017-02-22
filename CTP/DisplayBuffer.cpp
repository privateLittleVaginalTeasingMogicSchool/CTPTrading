#define _CRT_SECURE_NO_WARNINGS

#include "vars.h"
#include "DisplayBuffer.h"
#include <queue>
#include <string>
#include <vector>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <iostream>
#include <sstream>
#include <iomanip>

char DisplayBuffer[BUFFER_ROW_NUM][BUFFER_COL_NUM + 1];
const int cnt = BUFFER_ROW_NUM*(BUFFER_COL_NUM + 1);
char* FIRST_LINE =	"©³©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©×©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©·";
char* OTHER_LINE =	"©§                                                                                              ©§                    ©§";
char* MIDDLE_LINE =	"©Ç©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©ß©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©Ï";
char* LAST_LINE =	"©»©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¥©¿";
std::vector<std::string> prompt;
std::vector<std::string> info;
int prompt_begin = 0;
int info_begin = 0;

void InitDisplayBuffer()
{
	for (int i = 0;i < BUFFER_ROW_NUM - 4;i++)
	{
		prompt.push_back("                                                                                              ");
		info.push_back("                    ");
	}
	strcpy((char*)DisplayBuffer, FIRST_LINE);
	strcpy((char*)(DisplayBuffer + BUFFER_ROW_NUM - 3), MIDDLE_LINE);
	for (int i = 1;i < BUFFER_ROW_NUM-1;i++)
	{
		if (i != BUFFER_ROW_NUM - 3)
			strcpy((char*)(DisplayBuffer + i), OTHER_LINE);
	}
	strcpy((char*)(DisplayBuffer + BUFFER_ROW_NUM - 1), LAST_LINE);
	
	memcpy(&DisplayBuffer[BUFFER_ROW_NUM - 2][2], "Command > ", 10);
	DisplayBuffer[BUFFER_ROW_NUM - 2][96] = ' ';
	DisplayBuffer[BUFFER_ROW_NUM - 2][97] = ' ';
	int len = strlen(ppInstrumentID[0]);
	std::stringstream ss;
	int rightblank = (20 - len) / 2;
	ss << std::setw(20 - rightblank) << std::right << ppInstrumentID[0];
	ss << std::setw(rightblank) << std::right << " ";
	info[0] = ss.str();
}

void FirstPrintDisplayBuffer()
{	
	_Get_Output_Mutex
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
	SetTextColor(NULL, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	for (int i = 0;i < BUFFER_ROW_NUM;i++)
	{
		puts(DisplayBuffer[i]);
	}
	
	RestoreTextColor();
	_Release_Output_Mutex
}

void PrintPromptAndInfo()
{
	for (int i = 0;i < BUFFER_ROW_NUM - 4;i++)
	{
		SetTextColor(NULL, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("©§");
		RestoreTextColor();
		printf("%s", prompt[(i + prompt_begin) % prompt.size()].c_str());
		SetTextColor(NULL, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("©§");
		RestoreTextColor();
		printf("%s", info[(i + info_begin) % info.size()].c_str());
		SetTextColor(NULL, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
		printf("©§");
		RestoreTextColor();
	}
}

void PrintDisplayBuffer()
{
	while (true)
	{
		Sleep(100);
		_Get_Output_Mutex
		SetCursorPosition(0, 1);
		PrintPromptAndInfo();
		_Release_Output_Mutex
	}
}

void NewInfo(const char* str)
{
	int len = strlen(str);
	prompt[prompt_begin%prompt.size()] = str;
	for (int i = len;i < 94;i++)
	{
		prompt[prompt_begin%prompt.size()].push_back(' ');
	}
	prompt_begin++;
}

void NewInfo(std::string& str)
{
	prompt[prompt_begin%prompt.size()] = str;
	for (int i = str.size();i < 94;i++)
	{
		prompt[prompt_begin%prompt.size()].push_back(' ');
	}
	prompt_begin++;
}
#pragma once

#include <string>

const int CONSOLE_COL_NUM = 120;
const int CONSOLE_ROW_NUM = 55;
const int BUFFER_ROW_NUM = CONSOLE_ROW_NUM - 5;
const int BUFFER_COL_NUM = CONSOLE_COL_NUM;

extern char DisplayBuffer[BUFFER_ROW_NUM][BUFFER_COL_NUM+1];

void InitDisplayBuffer();
void FirstPrintDisplayBuffer();
void PrintDisplayBuffer();
void SetTextColor(int back_color, int fore_color);
void RestoreTextColor();
void SetCursorPosition(int x, int y);
void NewPrompt(const char* str);
void NewPrompt(std::string& str);
void NewInfo(std::string& str);


#define _Get_Output_Mutex      do{\
                               while(output_mutex);\
                               output_mutex = true;

#define _Release_Output_Mutex  output_mutex = false;\
                               }while(0);
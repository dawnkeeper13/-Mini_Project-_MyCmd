#pragma once
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <locale.h>
#include <TlHelp32.h>

#define PAUSE system("pause")
#define CMP_CMD(token, command) _tcscmp(StrLower(token), command) == 0

#define TOKEN_NUM	10 
#define STR_LEN		256

TCHAR ERROR_CMD[];
TCHAR DELEMITER[];

void ProcessCmdArg(int argc, TCHAR* argv[], TCHAR cmdTokenList[][STR_LEN]);

int GetInput(TCHAR cmdTokenList[][STR_LEN]);
int Tokenization(TCHAR cmdTokenList[][STR_LEN], TCHAR userInput[]);
BOOL ProcessCmd(TCHAR cmdTokenList[][STR_LEN], int tokenNum);
BOOL ProcessSnapInit(HANDLE hProcessSnap);

TCHAR* StrLower(TCHAR* cmd);
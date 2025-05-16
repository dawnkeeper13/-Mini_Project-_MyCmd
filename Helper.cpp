#include "Helper.h"

TCHAR ERROR_CMD[] = _T("%s는(은) 올바른 명령어가 아닙니다\n");
TCHAR DELEMITER[] = _T(" ,\t\n");

void ProcessCmdArg(int argc, TCHAR* argv[], TCHAR cmdTokenList[][STR_LEN])
{
	int tokenNum = 0;
	for (int i = 1; i < argc; ++i)
	{
		_tcscpy_s(cmdTokenList[i - 1], argv[i]);
		++tokenNum;
	}
	ProcessCmd(cmdTokenList, tokenNum);
}

int GetInput(TCHAR cmdTokenList[][STR_LEN])
{
	TCHAR userInput[STR_LEN];
	_tprintf(_T("CMD>> "));
	_fgetts(userInput, STR_LEN, stdin);
	int tokenNum = Tokenization(cmdTokenList, userInput);
	
	return tokenNum;
}

int Tokenization(TCHAR cmdTokenList[][STR_LEN], TCHAR userInput[])
{
	TCHAR* nextToken = NULL;
	TCHAR* token = _tcstok_s(userInput, DELEMITER, &nextToken);
	int tokenNum = 0;

	while (token != NULL)
	{
		_tcscpy_s(cmdTokenList[tokenNum++], token);
		token = _tcstok_s(NULL, DELEMITER, &nextToken);
	}

	return tokenNum;
}

BOOL ProcessCmd(TCHAR cmdTokenList[][STR_LEN], int tokenNum)
{
	STARTUPINFO si = {};
	si.cb = sizeof si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&pi, sizeof(pi));

	TCHAR cmdWithArgs[STR_LEN] = {};
	TCHAR cmdArgs[STR_LEN] = {};

	if (CMP_CMD(cmdTokenList[0], _T("exit")))
	{
		return FALSE;
	}
	else if (CMP_CMD(cmdTokenList[0], _T("echo")))
	{
		if (tokenNum >= 2)
		{
			_stprintf_s(cmdArgs, _T("%s"), cmdTokenList[1]);

			for (int i = 2; i < tokenNum; ++i)
			{
				_stprintf_s(cmdArgs, _T("%s %s"), cmdArgs, cmdTokenList[i]);
			}

			_tprintf(_T("%s\n"), cmdArgs);
		}
		else
		{
			_tprintf(_T("\n"));
		}
	}
	else if (CMP_CMD(cmdTokenList[0], _T("start")))
	{
		if (tokenNum >= 3) // start + 추가명령어 + 인자 (최소 3개 토큰)
		{
			_stprintf_s(cmdArgs, _T("%s"), cmdTokenList[1]);

			for (int i = 2; i < tokenNum; ++i)
			{
				_stprintf_s(cmdArgs, _T("%s %s"), cmdArgs, cmdTokenList[i]);
			}
			_stprintf_s(cmdWithArgs, _T("%s %s"), _T("[Mini_Project]_MyCmd.exe"), cmdArgs);

			CreateProcess(
				NULL, cmdWithArgs, NULL, NULL,
				FALSE, CREATE_NEW_CONSOLE, NULL, NULL,
				&si, &pi
			);
		}
		else
		{
			TCHAR command[] = _T("[Mini_Project]_MyCmd.exe");
			CreateProcess(
				NULL, command, NULL, NULL,
				FALSE, CREATE_NEW_CONSOLE, NULL, NULL,
				&si, &pi
			);
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else if (CMP_CMD(cmdTokenList[0], _T("lp")))
	{


		do 
		{
			_tprintf_s(_T("%40s %5d\n"), pe32.szExeFile, pe32.th32ProcessID);
		} while (Process32Next(hProcessSnap, &pe32));

		CloseHandle(hProcessSnap);
	}
	else if (CMP_CMD(cmdTokenList[0], _T("kp")))
	{

	}
	// 정의한 명령어 이외의 문자열 처리 //
	else
	{
		BOOL isSuccess;
		isSuccess = CreateProcess(NULL, cmdTokenList[0], NULL, NULL,
			FALSE, NULL, NULL, NULL,
			&si, &pi);

		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);

		if (isSuccess == FALSE)
		{
			_tprintf(ERROR_CMD, cmdTokenList[0]);
		}
	}
	return TRUE;
}

BOOL ProcessSnapInit(HANDLE hProcessSnap)
{
	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE)
	{
		_tprintf_s(_T("CreateToolhelp32Snapshot error!\n"));
		return FALSE;
	}
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(PROCESSENTRY32);

	if (!Process32First(hProcessSnap, &pe32))
	{
		_tprintf_s(_T("Process32First error!\n"));
		CloseHandle(hProcessSnap);
		return FALSE;
	}

	return TRUE;
}

TCHAR* StrLower(TCHAR* cmd)
{
	for (size_t i = 0; i < _tcslen(cmd); ++i)
	{
		if (_istupper(cmd[i]))
		{
			cmd[i] = _tolower(cmd[i]);
		}
	}
	return cmd;
}
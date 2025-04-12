/*----------------------------------------
	CommandPrompt_One.cpp
	���α׷� ���� : ��� ������Ʈ�� ���
------------------------------------------*/
#include <cstdio>
#include <cstdlib>
#include <clocale>
#include <tchar.h>
#include <windows.h>

#define STR_LEN			256
#define CMD_TOKEN_NUM	10
#define DIR_LEN			MAX_PATH+1

TCHAR ERROR_CMD[]
= _T("'%s'��(��) ������ �� �ִ� ���α׷��� �ƴմϴ�.\n");

int CmdProcessing(void);
TCHAR* StrLower(TCHAR*);

int _tmain(int argc, TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T("korean"));

	DWORD isExit; // typedef unsigned long DWORD
	while (true) {
		isExit = CmdProcessing();
		if (isExit == TRUE) {
			_fputts(_T("����� �����մϴ�\n"), stdout);
			break;
		}
	}
	return 0;
}

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");
TCHAR* nextToken = NULL;

/************************************************************************
�Լ� : int CmdProcessing(void)
��� : ��ɾ �Է� �޾Ƽ� �ش� ��ɾ �����ܾ� �ִ� ����� �����Ѵ�.
	   exit�� �ԷµǸ� TRUE�� ��ȯ�ϰ� �̴� ���α׷��� ����� �̾�����.
*************************************************************************/
int CmdProcessing(void)
{
	_fputts(_T("Best command prompt>> "), stdout);
	_fgetts(cmdString, STR_LEN, stdin); // ����� �Է� �ޱ�

	TCHAR* token = _tcstok_s(cmdString, seps, &nextToken);
	int tokenNum = 0;
	while (token != NULL) {
		_tcscpy_s(cmdTokenList[tokenNum++], StrLower(token));
		token = _tcstok_s(NULL, seps, &nextToken);
	}

	if (!_tcscmp(cmdTokenList[0], _T("exit"))) { return TRUE; }

	// else if (!_tcscmp(cmdTokenList[0], _T("notepad"))) { }

	//else if (!_tcscmp(cmdTokenList[0], _T("�߰��Ǵ� ��ɾ� 2"))) { }

	else {
		BOOL status;
		STARTUPINFO si = { 0 };
		PROCESS_INFORMATION pi;
		ZeroMemory(&pi, sizeof(pi));
		status = CreateProcess(
			NULL, cmdTokenList[0], NULL, NULL, 
			TRUE, CREATE_NEW_CONSOLE, NULL, NULL,
			&si, &pi
		);
		if (status)
			return FALSE;
		else {
			_tprintf(ERROR_CMD, cmdTokenList[0]);
			return FALSE;
		}
	}

	//return FALSE;
}

/******************************************************************************
�Լ� : TCHAR* StrLower(TCHAR* pStr)
��� : ���ڿ� ���� �����ϴ� ��� �빮�ڸ� �ҹ��ڷ� �����Ѵ�.
	   ����� ���ڿ��� �����͸� ��ȯ�Ѵ�.
*******************************************************************************/
TCHAR* StrLower(TCHAR* pStr)
{
	TCHAR* ret = pStr;

	while (*pStr) {
		if (_istupper(*pStr)) *pStr = _totlower(*pStr);
		++pStr;
	}
	return ret;
}

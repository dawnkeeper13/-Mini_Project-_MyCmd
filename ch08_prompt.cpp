#include "Helper.h"
#include <tlHelp32.h>

TCHAR cmdTokenList[TOKEN_NUM][STR_LEN];
BOOL isRunning = TRUE;

int _tmain(int argc, TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T("Korean"));

	if (argc > 2)
	{
		ProcessCmdArg(argc, argv, cmdTokenList);
	}

	while (1)
	{
		if (isRunning == FALSE)
		{
			_tprintf(_T("\n*****프롬프트를 종료합니다*****\n"));
			break;
		}
		int tokenNum = GetInput(cmdTokenList);
		isRunning = ProcessCmd(cmdTokenList, tokenNum);
	}

	return 0;
}
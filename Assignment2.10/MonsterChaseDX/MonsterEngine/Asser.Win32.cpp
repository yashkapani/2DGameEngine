#include <stdio.h>
#include <Windows.h>
#include "ConsolePrint.h"

bool _MessagedAssert(const char * i_pExpression, const char * i_pMessage, const char * i_pFile, unsigned int i_LineNo)
{
	const size_t sizeMessage = 1024;
	char Message[sizeMessage];

	sprintf_s(Message, sizeMessage, "%s(%d): %s\nError: %s\nShould we try to continue ?",
		i_pFile, i_LineNo, i_pExpression, i_pMessage);

	int result = MessageBoxA(NULL, Message, "Exit?", MB_YESNO);

	switch (result)
	{
	case IDYES:
		ConsolePrint(3, "%s(%d): %s is false\n", i_pFile, i_LineNo, i_pExpression);
		ConsolePrint(3, "%s\n", i_pMessage);
		return true;
	default:
		return false;
	}
}
#include <stdio.h>
#include <Windows.h>


#include "ConsolePrint.h"

namespace Engine
{
	bool _MessagedAssert(const char * i_pExp, const char * i_pMessage, const char * i_pFile, unsigned int i_LineNo)
	{
		const size_t sizeMessage = 1024;
		char Message[sizeMessage];

		sprintf_s(Message, sizeMessage, "ASSERT: %s\n\nFile: %s Line: %d\n\nMessage: %s\n\nShould we try to continue ?",
			i_pExp, i_pFile, i_LineNo, i_pMessage);

		int result = MessageBoxA(NULL, Message, "Not Valid!", MB_YESNO);

		switch (result)
		{
		case IDYES:
			Engine::ConsolePrint(1, "File: %s Line: %d Condition: %s\n", i_pFile, i_LineNo, i_pExp);
			Engine::ConsolePrint(1, "Message: %s\n", i_pMessage );
			return true;
		default:
			return false;
		}
	}

} // namespace Engine
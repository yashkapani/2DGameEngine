#include <stdarg.h>
#include <stdio.h>
#include <Windows.h>

int verbosityLvl = 3;

void ConsolePrint(int verbosity, const char * i_fmt, ...)
{
	const size_t lenTemp = 256;
	char strTemp[lenTemp] = "DEBUG: ";
	//char compName[lenTemp];

	//LPDWORD wordLength = new DWORD(256);
	//GetComputerNameA(compName, wordLength);
	//strcat_s(strTemp, "Comp Name: ");
	//strcat_s(strTemp, compName);


	if (verbosity <= verbosityLvl)
	{
		switch (verbosity)
		{
		case 1:
			strcat_s(strTemp, "Log: ");
			break;
		case 2:
			strcat_s(strTemp, "Warning: ");
			break;
		case 3:
			strcat_s(strTemp, "Error: ");
			break;
		default:
			break;
		}
	}
	strcat_s(strTemp, i_fmt);
	const size_t lenOutput = lenTemp + 32;
	char strOutput[lenOutput];
	va_list args;
	va_start(args, i_fmt);
	vsprintf_s(strOutput, lenOutput, strTemp, args);
	va_end(args);
	OutputDebugStringA(strOutput);
}
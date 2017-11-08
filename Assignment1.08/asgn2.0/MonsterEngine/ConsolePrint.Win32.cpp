#include <stdarg.h>		// for va_<xxx>
#include <stdio.h>		// for vsprintf_s()
#include <Windows.h>	// for OutputDebugStringA(). Uggh.. this pulls in a lot of Windows specific stuff

namespace Engine
{
	int verbosityLevel = 3; 

void ConsolePrint(int verbosity,  const char * i_fmt, ... ) 
{
	const size_t lenTemp = 256;
	char strTemp[lenTemp] = " ";

	if (verbosity <= verbosityLevel)
	{
		switch (verbosity)
		{
		case 1: 
			strcat_s(strTemp, "DEBUG ERROR:");
			break;
		case 2:
			strcat_s(strTemp, "DEBUG WARNING Or ERROR");
			break;
		case 3:
			strcat_s(strTemp, "DEBUG ERROR WARNING OR LOG:");
			break;
		default:
			break;
		}
	}
	

	strcat_s(strTemp, i_fmt);

	const size_t lenOutput = lenTemp + 32;

	char strOutput[lenOutput];

	// define a variable argument list variable 
	va_list args;
	
	// initialize it. second parameter is variable immediately
	// preceeding variable arguments
	va_start(args, i_fmt);

	// (safely) print our formatted string to a char buffer
	vsprintf_s(strOutput, lenOutput, strTemp, args);

	va_end(args);

	OutputDebugStringA(strOutput);
}

} // namespace Engine
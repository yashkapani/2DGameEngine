#ifndef GUARD_ConsolePrint_h
#define GUARD_ConsolePrint_h
#include <cstdio>


void ConsolePrint(int verbosityLvl, const char * i_fmt, ...);


#if defined(_DEBUG)  &&  !defined(DISABLE_DEBUG_PRINT)
#define DEBUG_PRINT(verbosityLvl ,fmt,...) ConsolePrint((verbosityLvl),(fmt),__VA_ARGS__)
#else
#define DEBUG_PRINT(fmt,...) void(0)
#endif //_DEBUG


#endif // GUARD_ConsolePrint_h
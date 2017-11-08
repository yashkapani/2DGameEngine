#include <windows.h>
#include <limits.h>
#include "Assert.h"""
#include "Timing.h"

namespace Timing
{

	unsigned int LastFrame_ms;

	LARGE_INTEGER PerformanceFrequency = { 0 };

	bool Initialize()
	{
		if (!QueryPerformanceFrequency(&PerformanceFrequency))
			return false;

		return true;
	}

	tick GetCurrentTickCounter()
	{

		LARGE_INTEGER CurrentFrameCounter;

		BOOL success = QueryPerformanceCounter(&CurrentFrameCounter);
		MessagedAssert(success == TRUE,"");

		return (CurrentFrameCounter.QuadPart);
	}
	float TicksToMS(tick i_ticks)
	{
		if (PerformanceFrequency.QuadPart == 0LL)
			Initialize();

		float diff = static_cast<float>(i_ticks)* 1000.0f / PerformanceFrequency.QuadPart;

		return diff;
	}


	float GetTimeDiff_ms(tick i_StartTime, tick i_EndTime)
	{
		if (PerformanceFrequency.QuadPart == 0)
		{
			bool success = Initialize();
			MessagedAssert(success == true,"");
		}

		return (1000.0f * static_cast<float>(i_EndTime - i_StartTime)) / PerformanceFrequency.QuadPart;
	}

} 
#include <windows.h>

#include <assert.h>
#include <limits.h>

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
	//	assert(success == TRUE);

		return (CurrentFrameCounter.QuadPart);
	}

	float GetTimeDiff_ms(tick i_StartTime, tick i_EndTime)
	{
		if (PerformanceFrequency.QuadPart == 0)
		{
			bool success = Initialize();
			//assert(success == true);
		}

		return (1000.0f * static_cast<float>(i_EndTime - i_StartTime)) / PerformanceFrequency.QuadPart;
	}

} // Timing
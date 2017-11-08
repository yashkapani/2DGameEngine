#include <windows.h>

#include <assert.h>
#include <limits.h>

#include "Timing.h"

namespace Engine
{
namespace Timing
{
	unsigned int LastFrame_ms;

	LARGE_INTEGER PerformanceFrequency;

	bool Initialize()
	{
		if( !QueryPerformanceFrequency( & PerformanceFrequency ) )
			return false;
	
		return true;
	}

	tick GetCurrentTickCounter()
	{
		assert(PerformanceFrequency.QuadPart > 0);

		LARGE_INTEGER CurrentFrameCounter;

		BOOL success = QueryPerformanceCounter( &CurrentFrameCounter );
		assert( success == TRUE );

		return CurrentFrameCounter.QuadPart;
	}

	unsigned int GetTimeDiff_ms(tick i_StartTime, tick i_EndTime)
	{
		assert(PerformanceFrequency.QuadPart > 0);

		LONGLONG diff = (i_EndTime - i_StartTime) * 1000 / PerformanceFrequency.QuadPart;
		assert(diff < UINT_MAX);

		return static_cast<unsigned int>(diff);
	}

} // Timing
} // Engine
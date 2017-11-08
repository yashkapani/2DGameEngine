#ifndef GUARD_TIMING_H
#define GUARD_TIMING_H

#include <stdint.h>

namespace Timing
{
	typedef uint64_t tick;
	bool Initialize();
	tick GetCurrentTickCounter();
	float GetTimeDiff_ms(tick i_StartTime, tick i_EndTime = GetCurrentTickCounter());

	inline float CvtSecondsToMilliseconds(float i_Seconds);
	inline float CvtPerSecondToPerMillisecond(float i_PerSecond);

}


#include "Timing.inl"

#endif // GUARD_TIMING_H
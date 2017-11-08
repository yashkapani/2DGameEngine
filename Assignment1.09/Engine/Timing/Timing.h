#ifndef __TIMING_H
#define __TIMING_H

#include <stdint.h>

namespace Engine
{
namespace Timing
{
	typedef uint64_t	tick;
	
	bool Initialize();
	
	tick GetCurrentTickCounter();
	unsigned int GetTimeDiff_ms(tick i_StartTime, tick i_EndTime = GetCurrentTickCounter());

	inline float CvtSecondsToMilliseconds( float i_Seconds );
	inline float CvtPerSecondToPerMillisecond( float i_PerSecond );
	
}
} // namespace Engine

#include "Timing.inl"

#endif // __TIMING_H
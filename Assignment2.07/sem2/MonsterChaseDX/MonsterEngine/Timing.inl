namespace Timing
{
	inline float SecondsToMilliseconds(float i_Seconds)
	{
		return i_Seconds * 1000.0f;
	}
	inline float PerSecondToPerMillisecond(float i_PerSecond)
	{
		return i_PerSecond / 1000.0f;
	}
	inline unsigned int GetDifferenceTicks(tick i_Start, tick i_End)
	{
		// make sure we're not going to overflow
		//MessagedAssert(i_End - i_Start < UINT_MAX,"");

		return static_cast<unsigned int>(i_End - i_Start);
	}
}
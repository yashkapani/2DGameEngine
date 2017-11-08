namespace Engine
{
namespace Timing
{
inline float SecondsToMilliseconds( float i_Seconds )
{ 
	return i_Seconds * 1000.0f; 
}

inline float PerSecondToPerMillisecond( float i_PerSecond ) 
{
	return i_PerSecond / 1000.0f;
}

}
} // namespace Azra
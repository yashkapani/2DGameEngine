#ifndef __PROFILER_H
#define __PROFILER_H

#include <assert.h>

#include <map>
#include <string>

#include "Timing.h"

namespace Profiling
{

	class Profiler
	{
		struct Accumulator
		{
			unsigned int	m_Count;
			unsigned int	m_Sum;
			unsigned int	m_Max;
			unsigned int	m_Min;

			Accumulator()
			{
				m_Count = 0;
				m_Sum = 0;
				m_Max = 0;
				m_Min = UINT_MAX;
			}
		};

		std::map<std::string, struct Accumulator> s_Accumulators;

	public:
		void addTiming(const char * i_pName, unsigned int i_MS);

		void PrintAccumulators(void);
	};

	extern Profiler g_Profiler;

	class ScopedTimer
	{
		const char *		m_pScopeName;
		Timing::tick			m_Start;

	public:
		ScopedTimer(const char * i_pName) :
			m_Start(Timing::GetCurrentTickCounter()),
			m_pScopeName(i_pName)
		{
#if defined(_DEBUG)
			printf("Scoped Timer %s started at Tick %lld\n", m_pScopeName ? m_pScopeName : "Unnamed", m_Start);
#endif
			//assert(i_pName);
		}

		~ScopedTimer()
		{
			Timing::tick End = Timing::GetCurrentTickCounter();

#if defined(_DEBUG)
			printf("Scoped Timer %s ended at Tick %lld ran for %fms \n", m_pScopeName ? m_pScopeName : "Unnamed", End, Timing::GetTimeDiff_ms(m_Start, End));
#endif

			g_Profiler.addTiming(m_pScopeName, Timing::GetDifferenceTicks(m_Start, End));
		}

	};

}


#if defined( ENABLE_PROFILING )
#define PROFILE_CONCAT_HELPER(left, right) left##right
#define PROFILE_CONCAT(left, right) PROFILE_CONCAT_HELPER(left, right)

#define PROFILE_SCOPE_BEGIN(str)	{ Profiling::ScopedTimer PROFILE_CONCAT(__Timer, __LINE__)( str );
#define PROFILE_SCOPE_END()			}

#define PROFILE_UNSCOPED(str)		Profiling::ScopedTimer PROFILE_CONCAT(__Timer, __LINE__)( str );
#define PROFILE_PRINT_RESULTS()		Profiling::g_Profiler.PrintAccumulators();
#else
#define PROFILE_SCOPE_BEGIN(str)	__noop
#define PROFILE_SCOPE_END			__noop
#define PROFILE_UNSCOPED(str)		__noop
#define PROFILE_PRINT_RESULTS()		__noop
#endif // ENABLE_PROFILING

#endif // __PROFILER_H
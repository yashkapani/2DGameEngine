#include "Timing.h"
#include<assert.h>
#include <string>

namespace Profiling
{
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
			assert(i_pName);
		}

		~ScopedTimer()
		{
			Timing::tick End = Timing::GetCurrentTickCounter();

#if defined(_DEBUG)
			printf("Scoped Timer %s ended at Tick %lld ran for %d \n", m_pScopeName ? m_pScopeName : "Unnamed", End, Timer::GetDifferenceMS(m_Start, End));
#endif

			g_Profiler.addTiming(m_pScopeName, Timing::GetTimeDiff_ms(m_Start, End));
		}

	};
}
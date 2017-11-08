#include "Profiling.h"
#include "Timing.h"
#include <Windows.h>

namespace Profiling
{

	Profiler g_Profiler;

	void Profiler::addTiming(const char * i_pName, unsigned int i_MS)
	{
		struct Accumulator & myAccumulator = s_Accumulators[i_pName];

		if (i_MS < myAccumulator.m_Min)
			myAccumulator.m_Min = i_MS;
		if (i_MS > myAccumulator.m_Max)
			myAccumulator.m_Max = i_MS;

		myAccumulator.m_Count++;
		myAccumulator.m_Sum += i_MS;
	}

	void Profiler::PrintAccumulators(void)
	{
		std::map<std::string, struct Accumulator>::iterator iter = s_Accumulators.begin();

		for (iter; iter != s_Accumulators.end(); ++iter)
		{
			float AverageTicks = iter->second.m_Count ? ((float)iter->second.m_Sum) / iter->second.m_Count : 0.0f;
			float AverageMS = iter->second.m_Count ? Timing::TicksToMS(iter->second.m_Sum / iter->second.m_Count) : 0.0f;
			char  OutPrint[50];
			sprintf(OutPrint,"[%s] Count: %d\n", iter->first.c_str(), iter->second.m_Count);
			OutputDebugStringA(OutPrint);
			sprintf(OutPrint," -- Ticks: Sum: %d Min: %d Max: %d Ave: %f\n", iter->second.m_Sum, iter->second.m_Min, iter->second.m_Max, AverageTicks);
			OutputDebugStringA(OutPrint);
			sprintf(OutPrint," --    ms: Sum: %f Min: %f Max: %f Ave: %f\n", Timing::TicksToMS(iter->second.m_Sum), Timing::TicksToMS(iter->second.m_Min), Timing::TicksToMS(iter->second.m_Max), AverageMS);
			OutputDebugStringA(OutPrint);
		}
	}

};
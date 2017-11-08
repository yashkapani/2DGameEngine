#pragma once
#ifndef _MATH_FLOAT_CHECK
#define _MATH_FLOAT_CHECK

#include <assert.h>
#include <math.h>

class FloatingPoint
{

public:
	static bool IsNaN(float i_Input);
	static bool IsInfinity(float i_Input1);
	static bool CheckFloatEqualWithULPS(float i_InputA, float i_InputB, int maxULPS); // ULPS = Units in Last Place
};

inline bool FloatingPoint::IsNaN(float i_Input)
{
	return i_Input != i_Input;
}

inline bool FloatingPoint::IsInfinity(float i_Input)
{
	return (i_Input>0 && i_Input / i_Input != i_Input / i_Input) || (i_Input<0 && i_Input / i_Input != i_Input / i_Input);
}

inline bool FloatingPoint::CheckFloatEqualWithULPS(float i_InputA, float i_InputB, int maxULPS)
{
	assert(maxULPS > 0 && maxULPS < 4 * 1024 * 1024);

	int i_InputA_IntRepresentation = *(int*)&i_InputA;

	if (i_InputA_IntRepresentation < 0)
	{
		i_InputA_IntRepresentation = 0x80000000 - i_InputA_IntRepresentation;
	}

	
	int i_InputB_IntRepresentation = *(int*)&i_InputB;
	if (i_InputB_IntRepresentation < 0)
	{
		i_InputB_IntRepresentation = 0x80000000 - i_InputB_IntRepresentation;
	}

	int intDiff = abs(i_InputA_IntRepresentation - i_InputB_IntRepresentation);

	if (intDiff <= maxULPS)
	{
		return true;
	}
	return false;
}


#endif

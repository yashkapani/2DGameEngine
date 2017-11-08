#ifndef _DetectCollision_h
#define _DetectCollision_h
#include "Actor.h"
#include "Matrix.h"

namespace Engine
{

	bool detectCollision(const Actor & i_A, const Actor & i_B, const Matrix & i_WorldToi, const Matrix & i_iToWorld, float FrameTime);
	bool CheckXAxis(const Actor & i_A, const Actor & i_B, const Matrix & i_WorldToi, const Matrix & i_iToWorld, float dt);
};
#endif
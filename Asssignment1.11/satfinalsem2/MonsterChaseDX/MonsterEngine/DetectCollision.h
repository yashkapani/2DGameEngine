#ifndef _DetectCollision_h
#define _DetectCollision_h
#include "Actor.h"
#include "Matrix.h"

namespace Engine
{

	bool detectCollision(const Actor & i_A, const Actor & i_B, const Matrix & i_WorldToi, const Matrix & i_iToWorld, float dt, float& o_collisionTime, Vector4& o_collisionNormal);
	bool CheckXAxis(const Actor & i_A, const Actor & i_B, const Matrix & i_WorldToi, const Matrix & i_iToWorld, float dt);
	bool CheckYAxis(const Actor & i_A, const Actor & i_B, const Matrix & i_WorldToi, const Matrix & i_iToWorld, float dt);
	bool CheckZAxis(const Actor & i_A, const Actor & i_B, const Matrix & i_WorldToi, const Matrix & i_iToWorld, float dt);
};
#endif
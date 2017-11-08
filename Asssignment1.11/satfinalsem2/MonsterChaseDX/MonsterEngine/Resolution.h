#ifndef _Resolution_h
#define _Resolution_h
#include "Actor.h"
#include "Matrix.h"
#include "DetectCollision.h"
#include "StringPool.h"

namespace Engine
{
	void CollisionResolution(Actor & i_A, Actor & i_B, Vector3 i_normal, float i_collisionTime);
};

#endif
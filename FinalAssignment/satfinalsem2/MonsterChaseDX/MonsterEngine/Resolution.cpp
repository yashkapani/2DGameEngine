#include "Resolution.h"

namespace Engine
{
	void CollisionResolution(Actor & i_A, Actor & i_B, Vector3 i_normal, float i_collisionTime)
	{
		//DEBUG_PRINT(1, "%s(%d): Collision-Detected, Resolving\n", __FILE__, __LINE__);
		//Calculating velocity after collision.
		Vector3 newAVel = i_A.GetVelocity()*((i_A.GetMass() - i_B.GetMass()) / (i_A.GetMass() + i_B.GetMass())) + i_B.GetVelocity()*((2 * i_B.GetMass()) / (i_A.GetMass() + i_B.GetMass()));
		Vector3 newBVel = i_B.GetVelocity()*((i_B.GetMass() - i_A.GetMass()) / (i_A.GetMass() + i_B.GetMass())) + i_A.GetVelocity()*((2 * i_A.GetMass()) / (i_A.GetMass() + i_B.GetMass()));

		//Getting correct direction
		Vector3 negNormal = -i_normal;
		Vector3 newA = (-newAVel) - ((i_normal * 2)*((-newAVel).DotProduct(i_normal)));
		i_A.SetVelocity(newA);
		Vector3 newB = (-newBVel) - ((negNormal * 2)*((-newBVel).DotProduct(negNormal)));
		i_B.SetVelocity(newB);

		//Updating Actors to current dt
		

	}
}
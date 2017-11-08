
#include "DetectCollision.h"

namespace Engine
{

	Matrix jRot;
	Matrix jToWorld;
	Matrix WorldToj;
	Matrix jToi;
	Matrix iToj;
	Vector4 Temp;
	Vector3 jCenterIni;
	Vector3 jWidthIni;
	Vector3 jHeightIni;
	Vector3 jDepthIni;
	Vector3 unitVecX;
	float lastCollision;
	float firstSeperation;
	Vector3 jRelative;

	bool detectCollision(const Actor & i_A, const Actor & i_B, const Matrix & i_WorldToi, const Matrix & i_iToWorld, float dt, float& o_collisionTime, Vector4& o_collisionNormal)
	{
	 jRot = Matrix::CreateZRotation(i_B.GetRotation().Z());
	 jToWorld = Matrix::CreateTransformationToWorld(i_B.GetPosition(), jRot);
	 WorldToj = jToWorld.GetInverse();
	 jToi = i_WorldToi*jToWorld;
	 iToj = WorldToj*i_iToWorld;
	 int normalToReturn = 0;
	 //Checking j(i_B) in i's(i_A) local space.
	 //X-Axis Test.

	 //Bringing B's center to A's local coordinates as a Point.
	 Temp = jToi*(i_B.GetBoundingBoxCenter()); //Need temp to convert to Vec 3.
	 jCenterIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());

	 //Bring the Half-Widths, Half-Heights, Half-Depths from B to A as a vector.
	 Temp = jToi*(Vector4(i_B.GetBoundingBoxExtent().X(), 0.0f, 0.0f, 0.0f));
	 jWidthIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
	 Temp = jToi*(Vector4(0.0f, i_B.GetBoundingBoxExtent().Y(), 0.0f, 0.0f));
	 jHeightIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
	 Temp = jToi*(Vector4(0.0f, 0.0f, i_B.GetBoundingBoxExtent().Z(), 0.0f));
	 jDepthIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
	 unitVecX = Vector3(1.0f, 0.0f, 0.0f);

	 //Calculating A's Projection on the Axis, considering B as a point.
	 float jProjectedX = (std::fabsf(jWidthIni.DotProduct(unitVecX))) + (std::fabsf(jHeightIni.DotProduct(unitVecX)));
	 float iOnXRight = i_A.GetBoundingBoxCenter().X() + (i_A.GetBoundingBoxExtent().X() + jProjectedX);
	 float iOnXLeft = i_A.GetBoundingBoxCenter().X() - (i_A.GetBoundingBoxExtent().X() + jProjectedX);
	 if (iOnXLeft > iOnXRight) //Swap start and end if start is greater than end.
	 {
		 float temp = iOnXLeft;
		 iOnXLeft = iOnXRight;
		 iOnXRight = temp;
	 }

	 //Bringing A's Velocity to Zero & Calculating B's relative. Note, brought Velocities from World space to local as Vectors.
	 Temp = i_WorldToi*(Vector4(i_A.GetVelocity().X(), i_A.GetVelocity().Y(), i_A.GetVelocity().Z(), 0.0f));
	 Vector3 iVelIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
	 Temp = i_WorldToi*(Vector4(i_B.GetVelocity().X(), i_B.GetVelocity().Y(), i_B.GetVelocity().Z(), 0.0f));
	 Vector3 jVelIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
	 Vector3 jRelative = jVelIni - iVelIni;

	 float lastCollision = 0.0f;
	 float firstSeperation = dt;

	 float jCollisionTimeX;
	 float jSeperationTimeX;

	 //Starting Swept-Seperating Axis Test.
	 if (jRelative.X() == 0)
	 {
		 if (iOnXLeft > jCenterIni.X() || iOnXRight < jCenterIni.X())
		 {
			 return false;
		 }
		 else
		 {
			 jCollisionTimeX = 0.0f;
			 jSeperationTimeX = dt;
		 }
	 }
	 else if (jRelative.X() != 0)
	 {
		 jSeperationTimeX = ((iOnXRight - jCenterIni.X()) / jRelative.X());
		 jCollisionTimeX = ((iOnXLeft - jCenterIni.X()) / jRelative.X());
		 if (jCollisionTimeX > jSeperationTimeX)
		 {
			 float temp = jCollisionTimeX;
			 jCollisionTimeX = jSeperationTimeX;
			 jSeperationTimeX = temp;
		 }
		 //Check if overlap occurs in this frame.
		 if (jCollisionTimeX >= dt || jSeperationTimeX <= 0.0f)
			 return false;
	 }

	 if (jCollisionTimeX > lastCollision)
	 {
		 lastCollision = jCollisionTimeX;
		 normalToReturn = 1;
	 }
	 if (jSeperationTimeX < firstSeperation)
		 firstSeperation = jSeperationTimeX;

	 //return true;
	 
	/*if (CheckXAxis(i_A, i_B, i_WorldToi, i_iToWorld, dt)==true)
		{

		}
		else
		{
			return false;
		}
		*/
		//Y-Axis Test
		Vector3 unitVecY = Vector3(0.0f, 1.0f, 0.0f);
		float jProjectedY = (std::fabsf(jWidthIni.DotProduct(unitVecY)) + std::fabsf(jHeightIni.DotProduct(unitVecY)));
		float iOnYTop = i_A.GetBoundingBoxCenter().Y() + (i_A.GetBoundingBoxExtent().Y() + jProjectedY);
		float iOnYBottom = i_A.GetBoundingBoxCenter().Y() - (i_A.GetBoundingBoxExtent().Y() + jProjectedY);
		if (iOnYBottom > iOnYTop) //Swap start and end if start is greater than end.
		{
			float temp = iOnYBottom;
			iOnYBottom = iOnYTop;
			iOnYTop = temp;
		}
		float jCollisionTimeY;
		float jSeperationTimeY;

		//Starting Swept-Seperating Axis Test.
		if (jRelative.Y() == 0)
		{
			if (iOnYBottom > jCenterIni.Y() || iOnYTop < jCenterIni.Y())
			{
				return false;
			}
			else
			{
				jCollisionTimeY = 0.0f;
				jSeperationTimeY = dt;
			}
		}
		else if (jRelative.Y() != 0)
		{
			jCollisionTimeY = ((iOnYBottom - jCenterIni.Y()) / jRelative.Y());
			jSeperationTimeY = ((iOnYTop - jCenterIni.Y()) / jRelative.Y());
			if (jCollisionTimeY > jSeperationTimeY)
			{
				float temp = jCollisionTimeY;
				jCollisionTimeY = jSeperationTimeY;
				jSeperationTimeY = temp;
			}
			if (jCollisionTimeY >= dt || jSeperationTimeY <= 0.0f)
				return false;
		}

		if (jCollisionTimeY > lastCollision)
		{
			lastCollision = jCollisionTimeY;
			normalToReturn = 2;
		}
		if (jSeperationTimeY < firstSeperation)
			firstSeperation = jSeperationTimeY;

		//Z-Axis Test
		Vector3 unitVecZ = Vector3(0.0f, 0.0f, 1.0f);
		float jProjectedZ = (std::fabsf(jDepthIni.DotProduct(unitVecZ)) + std::fabsf(jHeightIni.DotProduct(unitVecZ)));
		float iOnZFront = i_A.GetBoundingBoxCenter().Z() + (i_A.GetBoundingBoxExtent().Z() + jProjectedZ);
		float iOnZBehind = i_A.GetBoundingBoxCenter().Z() - (i_A.GetBoundingBoxExtent().Z() + jProjectedZ);
		if (iOnZBehind > iOnZFront) //Swap start and end if start is greater than end.
		{
			float temp = iOnZBehind;
			iOnZBehind = iOnZFront;
			iOnZFront = temp;
		}
		float jCollisionTimeZ;
		float jSeperationTimeZ;

		//Starting Swept-Seperating Axis Test.
		if (jRelative.Z() == 0)
		{
			if (iOnZBehind > jCenterIni.Z() || iOnZFront < jCenterIni.Z())
			{
				return false;
			}
			else
			{
				jCollisionTimeZ = 0.0f;
				jSeperationTimeZ = dt;
			}
		}
		else if (jRelative.Z() != 0)
		{
			jCollisionTimeZ = ((iOnZBehind - jCenterIni.Y()) / jRelative.Y());
			jSeperationTimeZ = ((iOnZFront - jCenterIni.Y()) / jRelative.Y());
			if (jCollisionTimeZ > jSeperationTimeZ)
			{
				float temp = jCollisionTimeZ;
				jCollisionTimeZ = jSeperationTimeZ;
				jSeperationTimeZ = temp;
			}
			if (jCollisionTimeZ >= dt || jSeperationTimeZ <= 0.0f)
				return false;
		}

		if (jCollisionTimeZ > lastCollision)
		{
			lastCollision = jCollisionTimeZ;
			normalToReturn = 3;
		}
			if (jSeperationTimeZ < firstSeperation)
			firstSeperation = jSeperationTimeZ;



		//Finished checking j(i_B) in i's(i_A) local space

		//Checking i(i_A) in j(i_B)'s local space.
		//X-Axis Test.

		//Bringing A's center to B's local coordinates as a Point.
		Temp = iToj*(i_A.GetBoundingBoxCenter()); //Need temp to convert to Vec 3.
		Vector3 iCenterInj = Vector3(Temp.X(), Temp.Y(), Temp.Z());

		//Bring the Half-Widths, Half-Heights, Half-Depths from A to B as a vector.
		Temp = iToj*(Vector4(i_A.GetBoundingBoxExtent().X(), 0.0f, 0.0f, 0.0f));
		Vector3 iWidthInj = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		Temp = iToj*(Vector4(0.0f, i_A.GetBoundingBoxExtent().Y(), 0.0f, 0.0f));
		Vector3 iHeightInj = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		Temp = iToj*(Vector4(0.0f, 0.0f, i_A.GetBoundingBoxExtent().Z(), 0.0f));
		Vector3 iDepthInj = Vector3(Temp.X(), Temp.Y(), Temp.Z());

		//Calculating B's Projection on the Axis, considering A as a point.
		float iProjectedX = (std::fabsf(iWidthInj.DotProduct(unitVecX)) + std::fabsf(iHeightInj.DotProduct(unitVecX)));
		float jOnXRight = i_B.GetBoundingBoxCenter().X() + (i_B.GetBoundingBoxExtent().X() + iProjectedX);
		float jOnXLeft = i_B.GetBoundingBoxCenter().X() - (i_B.GetBoundingBoxExtent().X() + iProjectedX);
		if (jOnXLeft > jOnXRight) //Swap start and end if start is greater than end.
		{
			float temp = jOnXLeft;
			jOnXLeft = jOnXRight;
			jOnXRight = temp;
		}

		//Bringing B's Velocity to Zero & Calculating A's relative. Note, brought Velocities from World space to local as Vectors.
		Temp = WorldToj*(Vector4(i_A.GetVelocity().X(), i_A.GetVelocity().Y(), i_A.GetVelocity().Z(), 0.0f));
		Vector3 iVelInj = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		Temp = WorldToj*(Vector4(i_B.GetVelocity().X(), i_B.GetVelocity().Y(), i_B.GetVelocity().Z(), 0.0f));
		Vector3 jVelInj = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		Vector3 iRelative = iVelInj - jVelInj;

		float iCollisionTimeX;
		float iSeperationTimeX;

		//Starting Swept-Seperating Axis Test.
		if (iRelative.X() == 0)
		{
			if (jOnXLeft > iCenterInj.X() || jOnXRight < iCenterInj.X())
			{
				return false;
			}
			else
			{
				iCollisionTimeX = 0.0f;
				iSeperationTimeX = dt;
			}
		}
		else if (iRelative.X() != 0)
		{
			iCollisionTimeX = ((jOnXLeft - iCenterInj.X()) / iRelative.X());
			iSeperationTimeX = ((jOnXRight - iCenterInj.X()) / iRelative.X());
			if (iCollisionTimeX > iSeperationTimeX)
			{
				float temp = iCollisionTimeX;
				iCollisionTimeX = iSeperationTimeX;
				iSeperationTimeX = temp;
			}
			//Check if overlap occurs in this frame.
			if (iCollisionTimeX >= dt || iSeperationTimeX <= 0.0f)
				return false;
		}

		if (iCollisionTimeX > lastCollision)
		{
			lastCollision = iCollisionTimeX;
			normalToReturn = 4;
		}
		if (iSeperationTimeX < firstSeperation)
			firstSeperation = iSeperationTimeX;

		//Y-Axis Test
		float iProjectedY = (std::fabsf(iWidthInj.DotProduct(unitVecY)) + std::fabsf(iHeightInj.DotProduct(unitVecY)));
		float jOnYTop = i_B.GetBoundingBoxCenter().Y() + (i_B.GetBoundingBoxExtent().Y() + iProjectedY);
		float jOnYBottom = i_B.GetBoundingBoxCenter().Y() - (i_B.GetBoundingBoxExtent().Y() + iProjectedY);
		if (jOnYBottom > jOnYTop) //Swap start and end if start is greater than end.
		{
			float temp = jOnYBottom;
			jOnYBottom = jOnYTop;
			jOnYTop = temp;
		}
		float iCollisionTimeY;
		float iSeperationTimeY;

		//Starting Swept-Seperating Axis Test.
		if (iRelative.Y() == 0)
		{
			if (jOnYBottom > iCenterInj.Y() || jOnYTop < iCenterInj.Y())
			{
				return false;
			}
			else
			{
				iCollisionTimeY = 0.0f;
				iSeperationTimeY = dt;
			}
		}
		else if (iRelative.Y() != 0)
		{
			iCollisionTimeY = ((jOnYBottom - iCenterInj.Y()) / iRelative.Y());
			iSeperationTimeY = ((jOnYTop - iCenterInj.Y()) / iRelative.Y());
			if (iCollisionTimeY > iSeperationTimeY)
			{
				float temp = iCollisionTimeY;
				iCollisionTimeY = iSeperationTimeY;
				iSeperationTimeY = temp;
			}
			if (iCollisionTimeY >= dt || iSeperationTimeY <= 0.0f)
				return false;
		}

		if (iCollisionTimeY > lastCollision)
		{
			lastCollision = iCollisionTimeY;
			normalToReturn = 5;
		}
		if (iSeperationTimeY < firstSeperation)
			firstSeperation = iSeperationTimeY;

		//Z-Axis Test
		float iProjectedZ = (std::fabsf(iDepthInj.DotProduct(unitVecZ)) + std::fabsf(iHeightInj.DotProduct(unitVecZ)));
		float jOnZFront = i_B.GetBoundingBoxCenter().Z() + (i_B.GetBoundingBoxExtent().Z() + iProjectedZ);
		float jOnZBehind = i_B.GetBoundingBoxCenter().Z() - (i_B.GetBoundingBoxExtent().Z() + iProjectedZ);
		if (jOnZBehind > jOnZFront) //Swap start and end if start is greater than end.
		{
			float temp = jOnZBehind;
			jOnZBehind = jOnZFront;
			jOnZFront = temp;
		}
		float iCollisionTimeZ;
		float iSeperationTimeZ;

		//Starting Swept-Seperating Axis Test.
		if (iRelative.Z() == 0)
		{
			if (jOnZBehind > iCenterInj.Z() || jOnZFront < iCenterInj.Z())
			{
				return false;
			}
			else
			{
				iCollisionTimeZ = 0.0f;
				iSeperationTimeZ = dt;
			}
		}
		else if (iRelative.Z() != 0)
		{
			iCollisionTimeZ = ((jOnZBehind - iCenterInj.Y()) / iRelative.Y());
			iSeperationTimeZ = ((jOnZFront - iCenterInj.Y()) / iRelative.Y());
			if (iCollisionTimeZ > iSeperationTimeZ)
			{
				float temp = iCollisionTimeZ;
				iCollisionTimeZ = iSeperationTimeZ;
				iSeperationTimeZ = temp;
			}
			if (iCollisionTimeZ >= dt || iSeperationTimeZ <= 0.0f)
				return false;
		}

		if (iCollisionTimeZ > lastCollision)
		{
			lastCollision = iCollisionTimeZ;
			normalToReturn = 6;
		}
		if (iSeperationTimeZ < firstSeperation)
			firstSeperation = iSeperationTimeZ;

		if (lastCollision < firstSeperation)
		{
			switch (normalToReturn)
			{
			case 1:
				o_collisionNormal = i_iToWorld*Vector4(1.0f, 0.0f, 0.0f, 0.0f);
				break;
			case 2:
				o_collisionNormal = i_iToWorld*Vector4(0.0f, 1.0f, 0.0f, 0.0f);
				break;
			case 3:
				o_collisionNormal = i_iToWorld*Vector4(0.0f, 0.0f, 1.0f, 0.0f);
				break;
			case 4:
				o_collisionNormal = jToWorld*Vector4(1.0f, 0.0f, 0.0f, 0.0f);
				break;
			case 5:
				o_collisionNormal = jToWorld*Vector4(0.0f, 1.0f, 0.0f, 0.0f);
				break;
			case 6:
				o_collisionNormal = jToWorld*Vector4(0.0f, 0.0f, 1.0f, 0.0f);
				break;
			}
			o_collisionTime = lastCollision;
			return true;
		}
		//	return true;
		else
			return false;
	}


	bool CheckXAxis(const Actor & i_A, const Actor & i_B, const Matrix & i_WorldToi, const Matrix & i_iToWorld, float dt)
	{
		//Checking j(i_B) in i's(i_A) local space.
		//X-Axis Test.

		//Bringing B's center to A's local coordinates as a Point.
		Temp = jToi*(i_B.GetBoundingBoxCenter()); //Need temp to convert to Vec 3.
		jCenterIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());

		//Bring the Half-Widths, Half-Heights, Half-Depths from B to A as a vector.
		Temp = jToi*(Vector4(i_B.GetBoundingBoxExtent().X(), 0.0f, 0.0f, 0.0f));
		jWidthIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		Temp = jToi*(Vector4(0.0f, i_B.GetBoundingBoxExtent().Y(), 0.0f, 0.0f));
	    jHeightIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		Temp = jToi*(Vector4(0.0f, 0.0f, i_B.GetBoundingBoxExtent().Z(), 0.0f));
		jDepthIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		unitVecX = Vector3(1.0f, 0.0f, 0.0f);

		//Calculating A's Projection on the Axis, considering B as a point.
		float jProjectedX = (std::fabsf(jWidthIni.DotProduct(unitVecX))) + (std::fabsf(jHeightIni.DotProduct(unitVecX)));
		float iOnXRight = i_A.GetBoundingBoxCenter().X() + (i_A.GetBoundingBoxExtent().X() + jProjectedX);
		float iOnXLeft = i_A.GetBoundingBoxCenter().X() - (i_A.GetBoundingBoxExtent().X() + jProjectedX);
		if (iOnXLeft > iOnXRight) //Swap start and end if start is greater than end.
		{
			float temp = iOnXLeft;
			iOnXLeft = iOnXRight;
			iOnXRight = temp;
		}

		//Bringing A's Velocity to Zero & Calculating B's relative. Note, brought Velocities from World space to local as Vectors.
		Temp = i_WorldToi*(Vector4(i_A.GetVelocity().X(), i_A.GetVelocity().Y(), i_A.GetVelocity().Z(), 0.0f));
		Vector3 iVelIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		Temp = i_WorldToi*(Vector4(i_B.GetVelocity().X(), i_B.GetVelocity().Y(), i_B.GetVelocity().Z(), 0.0f));
		Vector3 jVelIni = Vector3(Temp.X(), Temp.Y(), Temp.Z());
		Vector3 jRelative = jVelIni - iVelIni;

		float lastCollision = 0.0f;
		float firstSeperation = dt;

		float jCollisionTimeX;
		float jSeperationTimeX;

		//Starting Swept-Seperating Axis Test.
		if (jRelative.X() == 0)
		{
			if (iOnXLeft > jCenterIni.X() || iOnXRight < jCenterIni.X())
			{
				return false;
			}
			else
			{
				jCollisionTimeX = 0.0f;
				jSeperationTimeX = dt;
			}
		}
		else if (jRelative.X() != 0)
		{
			jSeperationTimeX = ((iOnXRight - jCenterIni.X()) / jRelative.X());
			jCollisionTimeX = ((iOnXLeft - jCenterIni.X()) / jRelative.X());
			if (jCollisionTimeX > jSeperationTimeX)
			{
				float temp = jCollisionTimeX;
				jCollisionTimeX = jSeperationTimeX;
				jSeperationTimeX = temp;
			}
			//Check if overlap occurs in this frame.
			if (jCollisionTimeX >= dt || jSeperationTimeX <= 0.0f)
				return false;
		}

		if (jCollisionTimeX > lastCollision)
			lastCollision = jCollisionTimeX;
		if (jSeperationTimeX < firstSeperation)
			firstSeperation = jSeperationTimeX;


		return true;


	}
}
#ifndef _VECTOR3_H
#define _VECTOR3_H
namespace MonsterEngine
{
	class Vector3
	{
		float m_X, m_Y, m_Z;

	public:
		Vector3();
		Vector3(float i_X, float i_Y, float i_Z);

		void Set(float i_X, float i_Y, float i_Z);

		//Setters
		void X(const float i_X) { m_X = i_X; }
		void Y(const float i_Y) { m_Y = i_Y; }
		void Z(const float i_Z) { m_Z = i_Z; }

		//Getters
		const float X() const { return m_X; }
		const float Y() const { return m_Y; }
		const float Z() const { return m_Z; }

		

	};

	Vector3 operator+ (const Vector3&, const Vector3&);
	Vector3 operator- (const Vector3&, const Vector3&);
	Vector3 operator* (const Vector3&, const float);
	Vector3 operator* (const float, const Vector3&);
}
#include "Vector3.inl"

#endif
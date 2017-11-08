#ifndef GUARD_vector4_h
#define GUARD_vector4_h

#include "Vector3.h"

class Vector4
{
public:
	Vector4() :m_X(0), m_Y(0), m_Z(0), m_W(1) {}
	Vector4(const float i_X, const float i_Y, const float i_Z, const float i_W) : m_X(i_X), m_Y(i_Y), m_Z(i_Z), m_W(i_W) {}
	Vector4(const float i_X, const float i_Y, const float i_Z) : m_X(i_X), m_Y(i_Y), m_Z(i_Z), m_W(1) {}
	Vector4(const Vector3 & i_other)
	{
		m_X = i_other.X();
		m_Y = i_other.Y();
		m_Z = i_other.Z();
		m_W = 1.0f;
	}
	Vector3 toVec3()
	{
		return Vector3(m_X, m_Y, m_Z);
	}

	//Getters
	const float X() const { return m_X; }
	const float Y() const { return m_Y; }
	const float Z() const { return m_Z; }
	const float W() const { return m_W; }

	bool operator==(const Vector4 & i_rhs)
	{
		if (m_X == i_rhs.m_X &&
			m_Y == i_rhs.m_Y &&
			m_Z == i_rhs.m_Z &&
			m_W == i_rhs.m_W)
			return true;
		else
			return false;
	}

private:
	float m_X, m_Y, m_Z, m_W;
};

#endif // GUARD_Vector4_h
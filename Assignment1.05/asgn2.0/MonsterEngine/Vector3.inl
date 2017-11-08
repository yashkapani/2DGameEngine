#include "Vector3.h"


	inline Vector3::Vector3() :
		m_X(0.0f),
		m_Y(0.0f),
		m_Z(0.0f)
	{ }


	inline Vector3::Vector3(float i_X, float i_Y, float i_Z) :
		m_X(i_X),
		m_Y(i_Y),
		m_Z(i_Z)
	{

	}

	inline Vector3& Vector3::operator= (const Vector3& i_rhs)
	{
		m_X = i_rhs.m_X;
		m_Y = i_rhs.m_Y;
		m_Z = i_rhs.m_Z;
		return *this;
	}
	inline Vector3& Vector3::operator+= (const Vector3& i_rhs)
	{
		m_X += i_rhs.m_X;
		m_Y += i_rhs.m_Y;
		m_Z += i_rhs.m_Z;
		return *this;
	}
	inline Vector3& Vector3::operator-= (const Vector3& i_rhs)
	{
		m_X -= i_rhs.m_X;
		m_Y -= i_rhs.m_Y;
		m_Z -= i_rhs.m_Z;
		return *this;
	}

	inline Vector3 operator+ (const Vector3& i_lhs, const Vector3& i_rhs)
	{
		return Vector3(i_lhs.X() + i_rhs.X(), i_lhs.Y() + i_rhs.Y(), i_lhs.Z() + i_rhs.Z());
	}
	inline Vector3 operator- (const Vector3& i_lhs, const Vector3& i_rhs)
	{
		return Vector3(i_lhs.X() - i_rhs.X(), i_lhs.Y() - i_rhs.Y(), i_lhs.Z() - i_rhs.Z());
	}
	inline Vector3 operator* (const Vector3& i_lhs, const float i_rhs)
	{
		return Vector3(i_lhs.X() * i_rhs, i_lhs.Y() * i_rhs, i_lhs.Z() * i_rhs);
	}
	inline Vector3 operator* (const float i_lhs, const Vector3& i_rhs)
	{
		return i_rhs * i_lhs;
	}

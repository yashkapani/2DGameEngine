#include <assert.h>

namespace Engine
{

inline Vector3::Vector3( float i_x, float i_y, float i_z ) :
	m_x( i_x ),
	m_y( i_y ),
	m_z( i_z )
{
}

inline Vector3::Vector3( const Vector3 & i_rhs ) :
	m_x( i_rhs.m_x ),
	m_y( i_rhs.m_y ),
	m_z( i_rhs.m_z )
{
}

// operators
inline const Vector3 & Vector3::operator=( const Vector3 & i_rhs )
{
	m_x = i_rhs.m_x;
	m_y = i_rhs.m_y;
	m_z = i_rhs.m_z;

	return *this;
}

// accessors
inline float Vector3::x( void ) const
{
	return m_x;
}

inline float Vector3::y( void ) const
{
	return m_y;
}

inline float Vector3::z( void ) const
{
	return m_z;
}

inline void Vector3::x( float i_x )
{
	m_x = i_x;
}

inline void Vector3::y( float i_y )
{
	m_y = i_y;
}

inline void Vector3::z( float i_z )
{
	m_z = i_z;
}

inline Vector3 & Vector3::operator+=( const Vector3 & i_rhs )
{
	m_x += i_rhs.m_x;
	m_y += i_rhs.m_y;
	m_z += i_rhs.m_z;

	return *this;
}

inline Vector3 & Vector3::operator-=( const Vector3 & i_rhs )
{
	m_x -= i_rhs.m_x;
	m_y -= i_rhs.m_y;
	m_z -= i_rhs.m_z;

	return *this;
}

inline Vector3 & Vector3::operator*=( float i_rhs )
{
	m_x *= i_rhs;
	m_y *= i_rhs;
	m_z *= i_rhs;

	return *this;
}

inline Vector3 & Vector3::operator/=( float i_rhs )
{
	m_x /= i_rhs;
	m_y /= i_rhs;
	m_z /= i_rhs;

	return *this;
}

inline Vector3 & Vector3::operator-( void )
{
	m_x = -m_x;
	m_y = -m_y;
	m_z = -m_z;

	return *this;
}

// stand alone operators
inline Vector3 operator+( const Vector3 & i_lhs, const Vector3 & i_rhs )
{
	return Vector3( i_lhs.x() + i_rhs.x(), i_lhs.y() + i_rhs.y(), i_lhs.z() + i_rhs.z() );
}

inline Vector3 operator-( const Vector3 & i_lhs, const Vector3 & i_rhs )
{
	return Vector3( i_lhs.x() - i_rhs.x(), i_lhs.y() - i_rhs.y(), i_lhs.z() - i_rhs.z() );
}

inline Vector3 operator*( const Vector3 & i_lhs, float i_rhs )
{
	return Vector3( i_lhs.x() * i_rhs, i_lhs.y() * i_rhs, i_lhs.z() * i_rhs );
}

inline Vector3 operator*( float i_lhs, const Vector3 & i_rhs )
{
	return Vector3( i_rhs.x() * i_lhs, i_rhs.y() * i_lhs, i_rhs.z() * i_lhs );
}

inline Vector3 operator/( const Vector3 & i_lhs, float i_rhs )
{
	return Vector3( i_lhs.x() / i_rhs, i_lhs.y() / i_rhs, i_lhs.z() / i_rhs );
}

inline float dot( const Vector3 & i_lhs, const Vector3 & i_rhs )
{
	return i_lhs.x() * i_rhs.x() + i_lhs.y() * i_rhs.y() + i_lhs.z() * i_rhs.z();
}

} // Namespace Engine
#ifndef __VECTOR3_H
#define __VECTOR3_H

namespace Engine
{

class Vector3
{
	float	m_x, m_y, m_z;

public:
	// default constructor
	Vector3( void );

	// standard constructor
	inline Vector3( float i_x, float i_y, float i_z );

	// copy constructor - for completeness
	inline Vector3( const Vector3 & i_rhs );

	// assignment operator
	inline const Vector3 & operator=( const Vector3 & i_rhs );

	// element accessors
	// - get individual element
	inline float x( void ) const;
	inline float y( void ) const;
	inline float z( void ) const;
	// - set individual element
	inline void x( float i_x );
	inline void y( float i_y );
	inline void z( float i_z );

	Vector3 & operator+=( const Vector3 & i_rhs );
	Vector3 & operator-=( const Vector3 & i_rhs );

	Vector3 & operator*=( float i_val );
	Vector3 & operator/=( float i_val );

	float length( void );
	// negate
	Vector3 & operator-( void );

	// - ( 0.0f, 0.0f, 0.0f )
	static const Vector3 Zero;
} ;

inline Vector3 operator+( const Vector3 & i_lhs, const Vector3 & i_rhs );
inline Vector3 operator-( const Vector3 & i_lhs, const Vector3 & i_rhs );

inline Vector3 operator*( const Vector3 & i_lhs, float i_rhs );
inline Vector3 operator*( float i_lhs, const Vector3 & i_rhs );
inline Vector3 operator/( const Vector3 & i_lhs, float i_rhs );

inline float dot( const Vector3 & i_lhs, const Vector3 & i_rhs );
inline Vector3 cross( const Vector3 & i_lhs, const Vector3 & i_rhs );

} // Namespace Engine

#include "Vector3.inl"
#endif // __VECTOR3_H
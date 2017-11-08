#include "Vector3.h"

#include <math.h>

namespace Engine
{

const Vector3 Vector3::Zero( 0.0f, 0.0f, 0.0f );

Vector3::Vector3() :
	m_x( 0.0f ),
	m_y( 0.0f ),
	m_z( 0.0f )
{

}

float Vector3::length()
{
	float length_sq = (m_x * m_x) + (m_y * m_y) + (m_z * m_z);

	if( length_sq > .00001f )
		return sqrt( length_sq );
	else
		return 0.0f;
}

} // Namespace Engine
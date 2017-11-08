#include "GameObject.h"

#include <new>
#include <stdlib.h>


uint32_t GameObject::baseIdentifier = 0;

GameObject::GameObject( const char * i_pName, Alignment i_Alignment, uint32_t i_DeactivationDelay, const Engine::Vector3 & i_InitialPosition, float i_Mass ) :
	m_UniqueID( baseIdentifier++ ),
	m_Alignment( i_Alignment ),
	m_pController( NULL ),
	m_bUpdatedThisFrame( false ),
	m_bActive( true ),
	m_Health( 100 ),
	m_Mass( i_Mass ),
	m_DeactivationDelay( i_DeactivationDelay ),
	m_Position( i_InitialPosition ),
	m_Velocity( Engine::Vector3::Zero ),
	m_Heading( Engine::Vector3::Zero ),
	m_LeftToDeactivate( 0 )
{

	const char * pName = i_pName ? i_pName : "Unnamed";

	m_pName = _strdup( pName );
}

GameObject::~GameObject()
{
	if( m_pName )
		free( m_pName );
}

void GameObject::Reanimate( Alignment i_Alignment )
{
	assert( m_bActive == false );

	m_bActive = true;
	m_Health = 100;

	m_Alignment = i_Alignment;
}

void GameObject::SetAlignment( Alignment i_Alignment )
{
	m_Alignment = i_Alignment;
}

GameObject::Alignment GameObject::GetAlignment()
{
	return m_Alignment;
}

void GameObject::StartUpdate( float i_lastFrameTime )
{
	m_bUpdatedThisFrame = false;

	m_Velocity += m_Acceleration * i_lastFrameTime;
	m_DesiredPosition = m_Position + m_Velocity * i_lastFrameTime;
}

void GameObject::FinishUpdate()
{
	m_Position = m_DesiredPosition;

	if( m_Health <= 0 )
		m_bActive = 0;

	m_bUpdatedThisFrame = true;
}

void GameObject::Deactivate()
{
	m_bActive = false;
}

bool GameObject::IsActive()
{
	return m_bActive;
}

void GameObject::ApplyForce( const Engine::Vector3 & i_Force )
{
	m_Acceleration = i_Force / m_Mass;
}

void GameObject::SetVelocity( const Engine::Vector3 & i_Velocity )
{
	m_Velocity = i_Velocity;
}

void GameObject::SetHeading( const Engine::Vector3 & i_Heading )
{
	m_Heading = i_Heading;
}

void GameObject::SetSize( const Engine::Vector3 & i_Size )
{
	m_Size = i_Size;
}

Engine::Vector3 GameObject::GetSize()
{
	return m_Size;
}

Engine::Vector3 GameObject::GetPosition()
{
	return m_Position;
}

void GameObject::ReduceHealth( int i_Hit )
{
	m_Health -= i_Hit;

	if( m_Health < 0 )
		m_Health = 0;
}


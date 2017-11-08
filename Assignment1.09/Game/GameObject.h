#ifndef __GAME_OBJECT_H
#define __GAME_OBJECT_H

#include <stdint.h>
#include "Math/Vector3.h"

class IGameObjectController;

struct GameObject
{
	Engine::Vector3			m_Position;				// where am I at in the world
	Engine::Vector3			m_DesiredPosition;		// where I'd like to be at the end of the frame
	Engine::Vector3			m_Velocity;				// which direction / how fast am I moving
	Engine::Vector3			m_Acceleration;			// what acceleration is being applied
	Engine::Vector3			m_Heading;				// which direction am I looking
	Engine::Vector3			m_Size;					// my size

	enum Alignment
	{
		ALIGNMENT_GOOD = 0,
		ALIGNMENT_NEUTRAL,
		ALIGNMENT_BAD,
		ALIGNMENT_CRAZY
	};
	uint32_t				m_DeactivationDelay;	// How long to wait after Health == 0 to deactivate
	uint32_t				m_LeftToDeactivate;		//

	IGameObjectController *	m_pController;			// Our controller

	char *					m_pName;				// Name

	uint32_t				m_UniqueID;				// a unique ID

	unsigned int 			m_bUpdatedThisFrame:1;	// Have we been updated this frame
	unsigned int			m_bActive:1;				// Is this an active GameObject
	Alignment				m_Alignment;
	int						m_Health;

	float					m_Mass;					// my mass
	

	

	

	GameObject( const char * i_pName, Alignment i_Alignment, uint32_t i_DeactivationDelay, const Engine::Vector3 & i_InitialPosition, float i_Mass );
	~GameObject();

	void SetAlignment( Alignment i_Alignment );
	Alignment GetAlignment();

	void StartUpdate( float i_lastFrameTime );
	void FinishUpdate();

	void ApplyForce( const Engine::Vector3 & i_Force );
	void SetVelocity( const Engine::Vector3 & i_Velocity );
	void SetHeading( const Engine::Vector3 & i_Heading );

	void SetSize( const Engine::Vector3 & i_Size );
	Engine::Vector3 GetSize();

	Engine::Vector3 GetPosition( void );

	void ReduceHealth( int i_Hit );

	void Reanimate( Alignment i_Alignment );
	void Deactivate();
	bool IsActive();

	static uint32_t baseIdentifier;
};

#endif // __GAME_OBJECT_H
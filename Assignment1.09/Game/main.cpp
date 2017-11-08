#include <new>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "Math/Vector3.h"
#include "Timing/Timing.h"

#include "GameObject.h"

const size_t		numTestObjects = 40 * 1024;
struct GameObject * pTestObjects = NULL;
//bool activeGameObjects[numTestObjects];

void SetupTest();
void RunAI();

int CountActive()
{
	assert( pTestObjects );

	int active = 0;

	for( size_t i = 0; i < numTestObjects; i++ )
	{
		if( pTestObjects[i].IsActive() )
			active++;
	}

	return active;
}

GameObject * FindInctive()
{
	for( size_t i = 0; i < numTestObjects; i++ )
		if( !pTestObjects[i].IsActive() )
			return pTestObjects + i;

	return NULL;
}

GameObject * FindNearest( GameObject * i_pMe )
{

	float closestDistance = static_cast<float>( RAND_MAX ) * 3.0f;

	GameObject * pClosest = NULL;

	GameObject * pOther = pTestObjects;
	uint32_t count = numTestObjects;

	while( count-- )
	{
		if( pOther->IsActive() && pOther != i_pMe )
		{
			Engine::Vector3 difference;

			difference = pOther->GetPosition() - i_pMe->GetPosition();

			if( difference.length() < closestDistance )
			{
				closestDistance = difference.length();
				pClosest = pOther;
			}
		}

		pOther++;	
	}

	return pClosest;
} 

void RunAI()
{
	GameObject * pMe = pTestObjects;
	uint32_t count = numTestObjects;

	while( count-- )
	{
		// printf( "%d\n",count );
		 
		if( pMe->IsActive() )
		{
			GameObject * pNearest = FindNearest( pMe );

			if( pNearest )
			{
				Engine::Vector3 difference;

				difference = pNearest->GetPosition() - pMe->GetPosition();

				float distance = difference.length();

				if( distance < pMe->GetSize().length() + pNearest->GetSize().length() )
				{
					if( pMe->GetAlignment() == pNearest->GetAlignment() )
					{
						GameObject * pInactive = FindInctive();
						if( pInactive )
							pInactive->Reanimate( pMe->GetAlignment() );
					}
					else
					{
						switch( pMe->GetAlignment() )
						{
						case GameObject::ALIGNMENT_GOOD:
						case GameObject::ALIGNMENT_NEUTRAL:
							switch( pNearest->GetAlignment() )
							{
							case GameObject::ALIGNMENT_BAD:
								pMe->ReduceHealth( 10 );
								break;
							case GameObject::ALIGNMENT_CRAZY:
								pMe->Deactivate();
								break;
							}
						}
					}
				}
				else
					pMe->ReduceHealth( 1 );
			}
		}

		pMe++;
	}

}

int main( int i_argc, char ** i_argl )
{
	using namespace Engine;

	Engine::Timing::Initialize();

	SetupTest();

	if( pTestObjects == NULL ) 
		return 0;

	// This loop needs to run faster
	do
	{
		Timing::tick start = Timing::GetCurrentTickCounter();

		for( size_t i = 0; i < numTestObjects; i++ )
			pTestObjects[i].StartUpdate( .001f );

		// Assume other systems run here
		// ProcessCollisions();

		for( size_t i = 0; i < numTestObjects; i++ )
			pTestObjects[i].FinishUpdate();

		RunAI();

		// RenderScene();

		Timing::tick runTicks = Timing::GetCurrentTickCounter() - start;
		printf( "Frame run time = %I64d\n", runTicks );

	} while( CountActive() > 0 );

	return 0;
}

void SetupTest()
{
	size_t sizeGameObject = sizeof(GameObject);

	pTestObjects = reinterpret_cast<GameObject *>( new uint8_t[numTestObjects * sizeof(GameObject)] );

	if( pTestObjects == NULL )
		return;

	for( size_t i = 0; i < numTestObjects; i++ )
	{
		const size_t	tempStringLength = 32;
		char			temp[tempStringLength];

		sprintf_s( temp, tempStringLength, "Actor %04d", i );

		Engine::Vector3	randomPosition( static_cast<float>( rand() ), static_cast<float>( rand() ), static_cast<float>( rand() ) );

		float mass = static_cast<float>( rand() ) / static_cast<float>( RAND_MAX);

		GameObject::Alignment alignment;

		switch( rand() & 0x03 )
		{
		default:
		case 0:
			alignment = GameObject::ALIGNMENT_GOOD;
			break;
		case 1:
			alignment = GameObject::ALIGNMENT_NEUTRAL;
			break;
		case 2:
			alignment = GameObject::ALIGNMENT_BAD;
			break;
		case 3:
			alignment = GameObject::ALIGNMENT_CRAZY;
			break;
		}

		GameObject * pCurrent = new (pTestObjects + i) GameObject( temp, alignment, 4, randomPosition, mass );

		Engine::Vector3	randomForce( 
			static_cast<float>( rand() ) / static_cast<float>( RAND_MAX),
			static_cast<float>( rand() ) / static_cast<float>( RAND_MAX),
			static_cast<float>( rand() ) / static_cast<float>( RAND_MAX) );

		pCurrent->ApplyForce( randomForce );

		Engine::Vector3	randomSize( 
			(static_cast<float>( rand() ) * 5.0f) / static_cast<float>( RAND_MAX),
			(static_cast<float>( rand() ) * 5.0f) / static_cast<float>( RAND_MAX),
			(static_cast<float>( rand() ) * 5.0f) / static_cast<float>( RAND_MAX) );

		
		//GameObject * pCurrent = new (pTestObjects + i) GameObject(temp, alignment, 4, randomPosition, mass, randomSize, randomForce);

		pCurrent->SetSize( randomSize );
	}

}


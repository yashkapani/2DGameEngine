#ifndef _RANDOM_H
#define _RANDOM_H

#include "IAController.h"
#include "EngineHeader.h"


class Random : public IActorController
{
public:
	Random()
	{
		
	}
	void UpdateActor(Actor * i_pActor);
	

private:
	Vector3 m_velocity;
	
	
};

#endif
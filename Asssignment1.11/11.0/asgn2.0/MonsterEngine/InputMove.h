#ifndef _INPUTMOVE_H
#define _INPUTMOVE_H

#include "IAController.h"
#include "EngineHeader.h"


class InputMove : public IActorController
{
public:
	InputMove()
	{
		
		m_velocity = Vector3(0.0f, 0.0f, 0.0f);
	}
	void UpdateActor(Actor * i_pActor);


private:
	Vector3 m_velocity;
};

#endif
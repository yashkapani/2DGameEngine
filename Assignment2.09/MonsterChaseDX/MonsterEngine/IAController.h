#ifndef _IACONTROLLER_H
#define _IACONTROLLER_H

#include "Actor.h"


	class IActorController
	{

	public:
		virtual void UpdateActor(Actor * i_pActor) = 0;
	};


#endif
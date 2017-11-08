#ifndef _IActorController_h
#define _IActorController_h
#include "Actor.h"
#include "Vector3.h"




class IActorController
{
public:
	virtual void UpdateActor(Vector3 & m_Acceleration) = 0;
	virtual ~IActorController() {}
};
#endif 
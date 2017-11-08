#ifndef _IAController_h
#define _IAController_h
#include "Actor.h"
#include "Vector3.h"




class IAController
{
public:
	virtual void UpdateActor(Vector3 & m_Acceleration) = 0;
	virtual ~IAController() {}
};
#endif 
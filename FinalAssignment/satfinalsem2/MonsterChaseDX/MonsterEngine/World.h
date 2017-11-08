#ifndef GUARD_World_h
#define GUARD_World_h

#include <vector>
#include "Actor.h"


class World{
public:
	World(){}
	~World(){}
	std::vector<Actor*> actorList;
	void addActor(Actor* actor){ actorList.push_back(actor); }
};
#endif
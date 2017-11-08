#ifndef _World_h
#define _World_h

#include <vector>
#include "Actor.h"
#include <vector>
#include "SharedPtr.h"


namespace
{
	std::vector<Engine::SharedPtr<Actor>>* gameObjects;
}


namespace Engine
{

	
	
	 void intializeActrorList();
	 void addActors();
	 void updateActors();
	 std::vector<Engine::SharedPtr<Actor>>* getActorList();

};
#endif
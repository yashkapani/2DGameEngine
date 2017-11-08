#include "World.h"
#include "Timing.h"


namespace Engine
{
void intializeActrorList()
{
	gameObjects = new std::vector <Engine::SharedPtr<Actor>>;
}

void addActors()
{
	gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Vector3(0, 0, 0), Vector3(0, 0, 0), "Player")));
	gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Vector3(50, 50, 0), Vector3(0, 0, 0), "Monster")));
}

void updateActors()
{
	Timing::tick dt = Timing::GetCurrentTickCounter();
	int s = gameObjects->size();
	for (int i = 0; i < s; i++){
		(*gameObjects)[i]->SetAcceleration(Vector3(0, 0, 0));
		(*gameObjects)[i]->Update(dt);
	}
}

	std::vector<Engine::SharedPtr<Actor>> * getActorList()
	{
		return gameObjects;
	}

	
}
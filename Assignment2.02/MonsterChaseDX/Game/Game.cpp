#include "Game.h"
#include <string>
namespace{
	std::vector<Engine::SharedPtr<Actor>>* gameObjects;
}



//Cheesy::Create("Cheesy Test App", 640, 480, false, false);



namespace Game
{
	void createActorList()
	{
		gameObjects = new std::vector <Engine::SharedPtr<Actor>>;
	}

	bool GetAsVector3(const LuaPlus::LuaObject & i_Object, Vector3 & o_Out)
	{
		if (!i_Object.IsTable() || (i_Object.GetCount() < 3))
			return false;

		LuaPlus::LuaObject X = i_Object[1];
		LuaPlus::LuaObject Y = i_Object[2];
		LuaPlus::LuaObject Z = i_Object[3];

		if (!X.IsNumber() || !Y.IsNumber() || !Z.IsNumber())
			return false;

		o_Out.X(X.GetFloat());
		o_Out.Y(Y.GetFloat());
		o_Out.Z(Z.GetFloat());

		return true;
	}

	void initGame(LuaPlus::LuaState * i_State, const char * filename){
		createActorList();
		//gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Vector3(0, 0, 0), Vector3(0, 0, 0), "Player")));
		//gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Vector3(50, 50, 0), Vector3(0, 0, 0),"Monster")));
		//gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Vector3(-75, 100, 0), Vector3(0, 0, 0), "Monster")));
		//int s = gameObjects->size();
		addActor(i_State, filename);
		Engine::Renderer::initRenderer();
	}


	void updateGame(float dt){
		int s = gameObjects->size();
		for (int i = 0; i < s; i++){
			(*gameObjects)[i]->SetAcceleration(Vector3(0.0001f, 0.0003f, 0.0f));
			(*gameObjects)[i]->Update(dt);
		}
	}

	std::vector<Engine::SharedPtr<Actor>> * getActorList()
	{
		return gameObjects;
	}

	Engine::SharedPtr<Actor> nearestActor(Vector3 location)
	{
		int s = gameObjects->size();
		int nearestIndex = 0;
		float nearestDistance = FLT_MAX;
		float curDistance = 0;
		float locX = location.X();
		float locY = location.Y();
		for (int i = 0; i < s; i++)
		{
			Vector3 curVec = (*gameObjects)[i]->GetPosition();
			curDistance = (((curVec.X() - locX)*(curVec.X() - locX)) + ((curVec.Y() - locY)*(curVec.Y() - locY)));
			if (curDistance < nearestDistance)
			{
				nearestDistance = curDistance;
				nearestIndex = i;
			}
		}
		return ((*gameObjects)[nearestIndex]);
	}

	void addActor(LuaPlus::LuaObject & i_Object)
	{
		for (LuaPlus::LuaTableIterator it(i_Object); it; it.Next())
		{
			LuaPlus::LuaObject ThisActor = it.GetValue();
		//	MessagedAssert(ThisActor.IsTable(), "");

			LuaPlus::LuaObject Name = ThisActor["name"];
		//	MessagedAssert(Name.IsString(), "");
		//	DEBUG_PRINT(1, "name = %s", Name.GetString());

			//LuaPlus::LuaObject Class = ThisActor["class"];
			//MessagedAssert(Class.IsString(), "");
			//DEBUG_PRINT(1, "class = %s", Class.GetString());

			//LuaPlus::LuaObject MaxVelocity = ThisActor["max_velocity"];
			//MessagedAssert(MaxVelocity.IsNumber(), "");
			//DEBUG_PRINT(1, "max velocity = %f", MaxVelocity.GetFloat());

			Vector3 Position(0.0f, 0.0f, 0.0f);
			LuaPlus::LuaObject InitialPosition = ThisActor["position"];
			if (!InitialPosition.IsNil())
			{
				GetAsVector3(InitialPosition, Position);
			}

			Vector3 Velocity(0.0f, 0.0f, 0.0f);
			LuaPlus::LuaObject InitialVelocity = ThisActor["velocity"];
			if (!InitialPosition.IsNil())
			{
				GetAsVector3(InitialPosition, Position);
			}

			gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Position, Velocity, Name.GetString())));
			// now we'd create the actor using this information
			// new Actor( Name.GetString(), Class.GetString(), MaxVelocity.GetFloat() )
		}
	}
	void addActor(LuaPlus::LuaState * i_State, const char * filename)
	{
		if (i_State->DoFile(filename) == 0)
		{
			LuaPlus::LuaObject Actors = i_State->GetGlobal("Actors");
			addActor(Actors);
		}
	}

}
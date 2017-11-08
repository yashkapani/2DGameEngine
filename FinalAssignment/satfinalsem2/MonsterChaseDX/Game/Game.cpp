#include "Game.h"
#include "ConsolePrint.h"
#include <string>
#include "Resolution.h"

namespace{
	std::vector<Engine::SharedPtr<Actor>>* gameObjects;
}





namespace Game
{
	void createActorList()
	{
		gameObjects = new std::vector <Engine::SharedPtr<Actor>>;
	}

	int i_Key = 0;
	void HandleMessage(const Engine::HashedString & i_Message, void * i_pMessageSender, void* i_pData)
	{
		if (i_pData == NULL)
			i_Key = 0;
		else
			i_Key = *reinterpret_cast<int *>(i_pData);
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

	void start(LuaPlus::LuaState * i_State, const char * filename){
		createActorList();
		addActor(i_State, filename);
		Engine::Renderer::initRenderer();
	}
	

	void OnKeyPressed(unsigned int i_CharID)
	{
		i_Key = NULL;
	}

	void OnKeyDown(unsigned int i_CharID)
	{
		i_Key = i_CharID;
	}

	void run(float dt){
		Engine::Renderer::defaultColor();
		int s = gameObjects->size();
		Cheesy::setKeyDownCallback(OnKeyDown);
		Cheesy::setKeyPressCallback(OnKeyPressed);
		if (i_Key == 0)
		{
			
			(*gameObjects)[0]->SetAcceleration(Vector3(0.0f, 0.0f, 0.0f));
		}
		else if (i_Key == 65 || i_Key == 68 || i_Key == 87 || i_Key == 83)
		{
			switch (i_Key)
			{
			case 65:
				(*gameObjects)[0]->SetAcceleration(Vector3(-0.0001f, 0.0f, 0.0f));
				break;
			case 68:
				(*gameObjects)[0]->SetAcceleration(Vector3(0.0001f, 0.0f, 0.0f));
				break;
			case 87:
				(*gameObjects)[0]->SetAcceleration(Vector3(0.0f, 0.0001f, 0.0f));
				break;
			case 83:
				(*gameObjects)[0]->SetAcceleration(Vector3(0.0f, -0.0001f, 0.0f));
				break;
			}
		}

		//Testing for collisions
		bool isCollision = true;
		//Testing for collisions
		while (isCollision)
		{
			isCollision = false;
			float prevCollision = dt;
			float firstCollision = dt;
			int entityA = 0, entityB = 0;
			Vector4 normal4 = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
			Vector3 normal3;
			for (int i = 0; i < s; i++)
			{
				Matrix iRot = Matrix::CreateZRotation((*gameObjects)[i]->GetRotation().Z());
				Matrix WorldToi = Matrix::CreateTransformationToLocal((*gameObjects)[i]->GetPosition(), iRot);
				Matrix iToWorld = WorldToi.GetInverse();


				for (int j = i + 1; j < s; j++)
				{
					if (Engine::detectCollision(*(*gameObjects)[i], *(*gameObjects)[j], WorldToi, iToWorld, dt, firstCollision, normal4))
					{
						Engine::Renderer::detectColor();
						isCollision = true;
						if (firstCollision < prevCollision)
						{
							entityA = i;
							entityB = j;
							normal3 = Vector3(normal4.X(), normal4.Y(), normal4.Z());
						}

						//DEBUG_PRINT(1, "Collision detected at %f, and frametime was %f", firstCollision, dt);
					}
					//DEBUG_PRINT(1, "%s(%d): Collision Not - Detected\n", __FILE__, __LINE__);
				}
			}
			if (isCollision)
			{
				Engine::CollisionResolution(*(*gameObjects)[entityA], *(*gameObjects)[entityB], normal3, firstCollision);
				updateActors(firstCollision);
				dt -= firstCollision;
			}

		}

		for (int i = 0; i < s; i++){
			
			(*gameObjects)[i]->Update(dt);
		}
	}

	void updateActors(float dt)
	{
		int s = gameObjects->size();
		for (int i = 0; i < s; i++){
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
			MessagedAssert(ThisActor.IsTable(), "");

			LuaPlus::LuaObject Name = ThisActor["name"];
			MessagedAssert(Name.IsString(), "");
			DEBUG_PRINT(1, "name = %s", Name.GetString());

			
			Vector3 Position(0.0f, 0.0f, 0.0f);
			LuaPlus::LuaObject InitialPosition = ThisActor["position"];
			if (!InitialPosition.IsNil())
			{
				GetAsVector3(InitialPosition, Position);
			}

			Vector3 Velocity(0.0f, 0.0f, 0.0f);
			LuaPlus::LuaObject InitialVelocity = ThisActor["velocity"];
			if (!InitialVelocity.IsNil())
			{
				GetAsVector3(InitialVelocity, Velocity);
			}

			Vector3 Rotation(0.0f, 0.0f, 0.0f);
			LuaPlus::LuaObject InitialRotation = ThisActor["rotation"];
			if (!InitialRotation.IsNil())
			{
				GetAsVector3(InitialRotation, Rotation);
			}

			gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Position, Velocity, Rotation, Name.GetString())));
			
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

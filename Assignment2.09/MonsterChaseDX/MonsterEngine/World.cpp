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
	LuaPlus::LuaState* pState = LuaPlus::LuaState::Create();
	char * luaFile = "Data\\ActorsToCreate.lua";

	if (pState)
	{
		if (pState->DoFile(luaFile) == 0)
		{
			// Build the ClassTypes bits
			/*LuaPlus::LuaObject ClassTypesObject = pState->GetGlobal("ClassTypes");

			if (ClassTypesObject.IsTable())
			{
				for (LuaTableIterator it(ClassTypesObject); it; it.Next())
				{
					LuaObject Value = it.GetValue();
					assert(Value.IsString());

					ClassTypeBits.GetBitIndex(Value.GetString());
				}
			}
			*/
			// Read the Actors
			LuaPlus::LuaObject Actors = pState->GetGlobal("Actors");

			for (LuaPlus::LuaTableIterator it(Actors); it; it.Next())
			{
				LuaPlus::LuaObject ThisActor = it.GetValue();
				MessagedAssert(ThisActor.IsTable(),"");

				LuaPlus::LuaObject Name = ThisActor["name"];
				MessagedAssert(Name.IsString(),"");
				

				LuaPlus::LuaObject i_Position= ThisActor["Position"];
				
				Vector3 Position(0.0f, 0.0f, 0.0f);
				if (!i_Position.IsNil())
				{
					GetAsVector3(i_Position, Position);
				}
				LuaPlus::LuaObject i_Velocity = ThisActor["Velocity"];
				//MessagedAssert(i_Velocity.IsNumber(),"");
				Vector3 Velocity(0.0f, 0.0f, 0.0f);
				GetAsVector3(i_Velocity, Velocity);

				LuaPlus::LuaObject i_Accelaration = ThisActor["Accelaration"];
				//MessagedAssert(i_Accelaration.IsNumber(), "");
				Vector3 Accelaration(0.0f, 0.0f, 0.0f);
				GetAsVector3(i_Accelaration, Accelaration);

				gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Position, Velocity, Name.GetString())));
				// now we'd create the actor using this information
				// new Actor( Name.GetString(), Class.GetString(), MaxVelocity.GetFloat() );
			}
		}
	}
	//gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Vector3(0, 0, 0), Vector3(0, 0, 0), "Player")));
	//gameObjects->push_back(Engine::SharedPtr<Actor>(new Actor(Vector3(50, 50, 0), Vector3(0, 0, 0), "Monster")));
}

bool GetAsVector3(LuaPlus::LuaObject & i_Object, Vector3 & o_Out)
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
void updateActors()
{
	Timing::tick dt = Timing::GetCurrentTickCounter();
	int s = gameObjects->size();
	for (int i = 0; i < s; i++){
		(*gameObjects)[i]->SetAcceleration(Vector3(0, 0, 0));
		(*gameObjects)[i]->Update(dt);

		Cheesy::setKeyDownCallback(OnKeyDown);
		Cheesy::setKeyPressCallback(OnKeyPressed);
		PlayerController();

	}
}

void PlayerController()
{
	if (i_key == 0)
	{

		(*gameObjects)[0]->SetAcceleration(Vector3(0.0f, 0.0f, 0.0f));
	}
	else if (i_key == 65 || i_key == 68 || i_key == 87 || i_key == 83)
	{
		switch (i_key)
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
}

	std::vector<Engine::SharedPtr<Actor>> * getActorList()
	{
		return gameObjects;
	}

	void OnKeyPressed(unsigned int i_CharID)
	{
		i_key = NULL;
	}

	void OnKeyDown(unsigned int i_CharID)
	{
		i_key = i_CharID;
	}
}
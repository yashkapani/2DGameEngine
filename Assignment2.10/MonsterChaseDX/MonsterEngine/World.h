#ifndef _World_h
#define _World_h

#include <vector>
#include "Actor.h"
#include <vector>
#include "SharedPtr.h"
#include "LuaPlus.h"
#include "Assert.h"
#include "ConsolePrint.h"
#include <Cheesy.h>
namespace
{
	std::vector<Engine::SharedPtr<Actor>>* gameObjects;
	int i_key = 0;
}


namespace Engine
{
	
	bool GetAsVector3(LuaPlus::LuaObject & i_Object, Vector3 & o_Out);
	 void intializeActrorList();
	 void addActors();
	 void updateActors();
	 std::vector<Engine::SharedPtr<Actor>>* getActorList();
	 void OnKeyPressed(unsigned int i_CharID);
	 void OnKeyDown(unsigned int i_CharID);
	 void PlayerController();
};
#endif
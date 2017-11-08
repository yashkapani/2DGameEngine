#ifndef _World_h
#define _World_h

#include <vector>
#include "Actor.h"
#include <vector>
#include "SharedPtr.h"
#include "LuaPlus.h"
#include "Assert.h"
#include "ConsolePrint.h"
namespace
{
	std::vector<Engine::SharedPtr<Actor>>* gameObjects;
}


namespace Engine
{

	bool GetAsVector3(LuaPlus::LuaObject & i_Object, Vector3 & o_Out);
	 void intializeActrorList();
	 void addActors();
	 void updateActors();
	 std::vector<Engine::SharedPtr<Actor>>* getActorList();

};
#endif
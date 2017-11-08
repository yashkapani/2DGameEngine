#ifndef GUARD_Game_h
#define GUARD_Game_h
#include <vector>
#include "SharedPtr.h"
#include "Actor.h"
#include <Cheesy.h>
#include <Sprite.h>
#include <Texture.h>
#include <Text.h>
#include "Assert.h"
#include "Renderer.h"
#include "AutoPtr.h"
#include "StringPool.h"
#include "HashedString.h"
#include "NamedBitSet.h"
#pragma warning( disable : 4996 )
#include "LuaPlus.h"
#include "Matrix.h"
#include "DetectCollision.h"
#include "MessageSystem.h"


namespace Game{

	
	void HandleMessage(const Engine::HashedString & i_Message, void * i_pMessageSender, void * i_pData);
	
	void start(LuaPlus::LuaState * i_State, const char * filename);
	void run(float dt);
	//void draw();
	void shutdown();
	void createActorList();
	void addActor(LuaPlus::LuaObject & i_Object);
	void addActor(LuaPlus::LuaState * i_State, const char * filename);
	void updateActors(float dt);
	std::vector<Engine::SharedPtr<Actor>>* getActorList();
	Engine::SharedPtr<Actor> nearestActor(Vector3 location);

}

#endif // GUARD_Game_h
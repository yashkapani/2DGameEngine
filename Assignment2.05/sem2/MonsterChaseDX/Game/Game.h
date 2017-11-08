#ifndef _Game_h
#define _Game_h
#include <vector>
#include "SharedPtr.h"
#include "Actor.h"
#include <Cheesy.h>
#include <Sprite.h>
#include <Texture.h>
#include <Text.h>
#include "Assert.h"
#include "Renderer.h"
#include "World.h"
#include "Renderable.h"


namespace Game{

	void start();
	void run();
	bool end();

}

#endif 
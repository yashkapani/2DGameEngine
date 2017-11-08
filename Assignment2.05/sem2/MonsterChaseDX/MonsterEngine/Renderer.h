#ifndef _Renderer_h
#define _Renderer_h

#include <Cheesy.h>
#include <Sprite.h>
#include <Texture.h>
#include <Text.h>
#include "Assert.h"
#include <vector>
#include "SharedPtr.h"
#include "Actor.h"
#include "World.h"


namespace Engine{
	namespace Renderer{

		void Renderable();
		void draw();
		
	}
}

#endif 
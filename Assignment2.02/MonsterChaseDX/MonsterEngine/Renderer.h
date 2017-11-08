#ifndef GUARD_Renderer_h
#define GUARD_Renderer_h

#include <Cheesy.h>
#include <Sprite.h>
#include <Texture.h>
#include <Text.h>
#include "Assert.h"
#include <vector>
#include "SharedPtr.h"
#include "Actor.h"

namespace Engine{
	namespace Renderer{

		void initRenderer();
		void draw();

	}
}

#endif // GUARD_Renderer_h
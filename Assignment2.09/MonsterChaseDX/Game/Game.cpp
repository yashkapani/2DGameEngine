#include "Game.h"


namespace Game
{

	void start()
	{
		Engine::intializeActrorList();
	
		
		Engine::addActors();
		Engine::Renderer::Renderable();
	}

	void run()
	{
		Engine::updateActors();
		Engine::Renderer::draw();

	}

	bool end()
	{
		return true;
	}

}

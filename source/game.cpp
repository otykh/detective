#include "game.h"

void Game::init()
{
	int seed = time(NULL);
	random::set(seed);
	Logger::l << "seed: " << seed << std::endl;

	world = World();
	eventMgr = EventManager();

	world.GenerateRandomWorld();
}
void Game::tick()
{
	tick_count++;

	world.tick();

	if(tick_count % 5 == 0 && world.isDay())
	{
		// every fifth tick something happens
		std::string output = eventMgr.CauseOrgEvent(world, world.GetRandomOrganisation());
		std::cout << output << std::endl;
	}

	Logger::l << "Current time: " << world.GetRealTime() << std::endl;
}
void Game::debug_print_world()
{
	world.PrintWorldInformation();
}

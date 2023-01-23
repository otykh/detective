#include <iostream>
#include "logger.h"
#include "world.h"
#include "eventmgr.h"

// #include <SFML/Graphics.hpp>
// NOTE: FOR NOW THE GRAPHICS ARE NOT USED! THIS IS ONLY A PROOF OF CONCEPT WITH A CONSOLE USER INTERFACE AND NOT GRAPHICAL USER INTERFACE, THIS WILL BE ADDED IN THE FUTURE, LINKED WITH SFML!

bool randBool(int percent)
{
	return (rand() % 101) <= percent;
}
int randRange(int min, int max)
{
	if(min == 0)
	{
		return (rand() % max) + min;
	}
	else
	{
		int range = max - min + 1;
		return rand() % range + min;
	}
}

int main()
{
	//int seed = time(NULL);
	int seed = 1674408403;
	srand(seed);
	Logger::l << "seed: " << seed << std::endl;

	World w(randBool, randRange);
	EventManager evm(randRange);

	w.GenerateRandomWorld();

	for(int i = 0; i < 100; i++)
	{
		std::cout << evm.CauseOrgEvent(w, w.GetRandomOrganisation()) << std::endl;
	}

	w.PrintWorldInformation();

	return 0;
}

#include <iostream>
#include "logger.h"
#include "world.h"
#include "eventmgr.h"
#include "rand.h"

// #include <SFML/Graphics.hpp>
// NOTE: FOR NOW THE GRAPHICS ARE NOT USED! THIS IS ONLY A PROOF OF CONCEPT WITH A CONSOLE USER INTERFACE AND NOT GRAPHICAL USER INTERFACE, THIS WILL BE ADDED IN THE FUTURE, LINKED WITH SFML!

int main()
{
	int seed = time(NULL);
	random::set(seed);
	Logger::l << "seed: " << seed << std::endl;

	World w;
	EventManager evm;

	w.GenerateRandomWorld();

	for(int i = 0; i < 100; i++)
	{
		std::cout << evm.CauseOrgEvent(w, w.GetRandomOrganisation()) << std::endl;
	}

	w.PrintWorldInformation();

	return 0;
}

#include <iostream>
#include "logger.h"
#include "world.h"
#include "eventmgr.h"
#include "rand.h"
#include "game.h"

// #include <SFML/Graphics.hpp>
// NOTE: FOR NOW THE GRAPHICS ARE NOT USED! THIS IS ONLY A PROOF OF CONCEPT WITH A CONSOLE USER INTERFACE AND NOT GRAPHICAL USER INTERFACE, THIS WILL BE ADDED IN THE FUTURE, LINKED WITH SFML!

int main()
{
	Game g;
	g.init();
	g.debug_print_world();

	/*int seed = time(NULL);
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

	w.GetRandomOrganisation()->CommitCrime();*/

	for(;;)
	{
		std::string command;
		std::cout << "?: ";
		std::cin >> command;

		if(command.at(0) == 'n')
		{
			// next tick
			g.tick();
		}
		else if(command.at(0) == 'p')
		{
			g.debug_print_world();
		}
		else if(command.at(0) == 'w')
		{
			int waitTime = 0;
			for(int i = 1; i < command.size(); i++)
			{
				if(command.at(i) == ' ')
				{
					break;
				}
				waitTime *= 10;
				waitTime += static_cast<int>(command.at(i)) - 48;
			}

			Logger::lwarn << "Waiting " << waitTime << " ticks!" << std::endl;
			for(int i = 0; i < waitTime; i++)
			{
				g.tick();
			}
		}
		else
		{
			Logger::lerr << "No command found" << std::endl;
		}
	}

	return 0;
}

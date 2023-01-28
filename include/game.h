#pragma once
#include "logger.h"
#include "world.h"
#include "eventmgr.h"
#include "rand.h"

class Game
{
	World world;
	EventManager eventMgr;
	int tick_count;
public:
	void init();
	void tick();
	void debug_print_world();
};

#pragma once

#include <vector>
#include <string>
#pragma once

#include <memory>
#include <string>
#include "character.h"
#include "organization.h"
#include "world.h"

#define EVENT_MANAGER_EVENT_NUMBER 6

struct EventManager
{
	// events are STATIC and do NOT store any information about the party involved, the events change states of the objects they operated but DO NOT store anything, they just work as a custom function
	class Event
	{
		std::string formula;
		int functionIndexCall;

	public:
		Event(int, std::string);
		std::string Activate(World& w); // returns event description when called
	};

	static std::string CauseEvent(World& world, int index);
	static const std::unique_ptr<Event> eventArray[EVENT_MANAGER_EVENT_NUMBER];

private:
	static void (*functionArray[5])(Character*, Character*);

	//bad_event = {"X stole 100$ from BANK"};
	//good_event = {"X was caught while doing Y"};
	//internal_event = {"X got rid of Y hidden: killed Y"};
};

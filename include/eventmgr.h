#pragma once

#include <vector>
#include <string>
#pragma once

#include <memory>
#include <string>
#include "character.h"
#include "organization.h"
#include "world.h"

#define EVENT_MANAGER_EVENT_NUMBER 23
#define MIN_EVENT_LENGTH 11 // where the event is ends at minimum heat

struct EventManager
{
	// events are STATIC and do NOT store any information about the party involved, the events change states of the objects they operated but DO NOT store anything, they just work as a custom function
	class Event
	{
		std::string formula;
		int functionIndexCall;

	public:
		Event(int, std::string);
		std::string Activate(const World& w, Org* const org); // returns event description when called
	};

	EventManager(int(*)(int, int));
	std::string CauseOrgEvent(const World& world, Org* const org);
	static const std::unique_ptr<Event> eventArray[EVENT_MANAGER_EVENT_NUMBER];

private:
	int(*randRange)(int, int);
	static void (*functionArray[5])(Character*, Character*);

	//bad_event = {"X stole 100$ from BANK"};
	//good_event = {"X was caught while doing Y"};
	//internal_event = {"X got rid of Y hidden: killed Y"};
};

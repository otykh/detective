#include "eventmgr.h"
#include <algorithm>
#include <iostream>

EventManager::Event::Event(int functionIndex, std::string formula)
{
	this->functionIndexCall = functionIndex;
	this->formula = formula;
}
EventManager::EventManager(int(*randRange)(int, int))
{
	this->randRange = randRange;
	if(this->randRange == nullptr)
	{
		throw;
	}
}
std::string EventManager::CauseOrgEvent(const World& w, Org* const org)
{
	int maxEventIndex = org->getHeat() * EVENT_MANAGER_EVENT_NUMBER;
	maxEventIndex = std::max(maxEventIndex, MIN_EVENT_LENGTH);
	int index = randRange(0, maxEventIndex);
	return EventManager::eventArray[index]->Activate(w, org);
}
std::string EventManager::Event::Activate(const World& w, Org* const org)
{
	//std::string output = "The event was cause has formula of: ";
	//output += formula + '\n';
	std::string output;
	output += "in " + org->getName() + " ";

	bool gettingCharacterInfo;
	bool hidden = false;

	std::vector<Character*> recordedCharacters;
	std::vector<bool> isVictim;

	int victimNumberRemembered = 0;
	bool isVictimRemembered = false;

	for(int i = 0; i < formula.size(); i++)
	{
		char ch = formula.at(i);
		if(ch == '$')
		{
			gettingCharacterInfo = true;
			continue;
		}
		else if(ch == '|')
		{
			hidden = !hidden;
			continue;
		}

		if(gettingCharacterInfo)
		{
			if(ch >= '1' && ch <= '9')
			{
				// if number
				victimNumberRemembered += victimNumberRemembered * 10;
				victimNumberRemembered += ((ch - '1') + 1); // '1' - '1' = 0+1, '2' - '1' = 1+1
				// overly simple convertation form char->int
			}
			else if(ch == 'a' || ch == 'v')
			{
				isVictimRemembered = (ch == 'v');
			}

			if(ch == ' ' || ch == '.' || ch == ',' || i+1 == formula.size())
			{
				// end the $ phase
				if(victimNumberRemembered > recordedCharacters.size())
				{
					// get random character if it is not in vector
					recordedCharacters.push_back(w.GetRandomCharacterInOrg(org)); // add new character
					isVictim.push_back(isVictimRemembered);
				}
				if(!hidden)
				{
					output += recordedCharacters[victimNumberRemembered - 1]->getFullName(); // put it's name where it should be
				}
				gettingCharacterInfo = false;

				isVictimRemembered = false;
				victimNumberRemembered = 0;

				if(i+1 != formula.size()) {output+=ch;}
			}
		}
		else
		{
			if(!hidden)
			{
				output += ch;
			}
		}
	}

	bool no_victims = true;
	for(int a = 0; a < recordedCharacters.size(); a++)
	{
		if(isVictim[a]) { continue; }
		for(int v = 0; v < recordedCharacters.size(); v++)
		{
			if(a != v)
			{
				no_victims = false;
				EventManager::functionArray[functionIndexCall](recordedCharacters[a], recordedCharacters[v]);
			}
		}
	}

	if(no_victims)
	{
		for(int i = 0; i < recordedCharacters.size(); i++)
		{
			EventManager::functionArray[functionIndexCall](recordedCharacters[i], nullptr);
		}
	}
	//EventManager::functionArray[functionIndexCall](nullptr, nullptr);
	return output;
}

// put text and where you want character to be randomly selected put the dollar sign '$'
// after that put the index of the character, like '$1', which reads first character
// after all of that put the sign weather the this character is attacker ('a') or attacker is victim('v')
// if you want the same character to appear like in this case "$1v went into their room. $1 was killed by $2a"
// if something is needs to be hidden from the event, use the | sign, which will hide the text
const std::unique_ptr<EventManager::Event> EventManager::eventArray[EVENT_MANAGER_EVENT_NUMBER] =
{
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a performed a task")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a, $2a peformed a task together")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a commited to the organisation")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a risked their life, working for organization")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a followed the order, successfully")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a was praised for their work")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a was appreciated by the managment")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a was scolded by the managment, $1a is now full of guilt")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a was threathened by another group")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a was remembering good times in organization")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(4,
				"$1a had a good time being a part of organization")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a gets into a heated argument with $2v")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a went ballistic with $2v, arguing about the managment")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a smashesh thing around after hearing $2v speak wrong things about organization")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a could not believe what $2v spoke about")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a smashed a window|because of $2v")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a beat up $2v")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a went into an argument with $2v")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a dissrespected $2v")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a, $2a went out to steal from $3v, they stole a lot")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(1,
				"$1a appeciated $2v")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(2,
				"$1a killed $2v")),
	std::unique_ptr<EventManager::Event>(new EventManager::Event(3,
				"$1v was found dead|killed by $2a")),
};
void (*EventManager::functionArray[5])(Character*, Character*) =
{
	[](Character* a, Character* v){ v->GetDisrespectedBy(a); },
	[](Character* a, Character* v){ v->GetAppreciatedBy(a); },
	[](Character* a, Character* v){ v->GetKilled(a); },
	[](Character* a, Character* v){ v->GetKilled(nullptr); }, // gets killed, but the killer is unknown
	[](Character* a, Character* v){ a->IncreaseOrgLikeness(); }
};

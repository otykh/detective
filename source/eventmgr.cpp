#include "eventmgr.h"
#include <iostream>

EventManager::Event::Event(int functionIndex, std::string formula)
{
	this->functionIndexCall = functionIndex;
	this->formula = formula;
}
std::string EventManager::CauseEvent(World& w, int index)
{
	return EventManager::eventArray[index]->Activate(w);
}
std::string EventManager::Event::Activate(World& w)
{
	//std::string output = "The event was cause has formula of: ";
	//output += formula + '\n';
	std::string output;

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
					recordedCharacters.push_back(w.GetRandomCharacter()); // add new character
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

	for(int a = 0; a < recordedCharacters.size(); a++)
	{
		if(isVictim[a]) { continue; }
		for(int v = 0; v < recordedCharacters.size(); v++)
		{
			if(a != v)
			{
				EventManager::functionArray[functionIndexCall](recordedCharacters[a], recordedCharacters[v]);
			}
		}
	}
	//EventManager::functionArray[functionIndexCall](nullptr, nullptr);
	return output;
}

// put text and where you want character to be randomly selected put the dollar sign '$'
// after that put the index of the character, like '$1', which reads first character
// after all of that put the sign weather the this character is attacker ('a') or attacker is victim('v')
// if you want the same character to appear like in this case "$1v went into their room. $1 was killed by $2a"
const std::unique_ptr<EventManager::Event> EventManager::eventArray[EVENT_MANAGER_EVENT_NUMBER] =
{
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a went into an argument with $2v")), // Ch on Ch, cons: 1 and 2 on bad terms
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a dissrespected $2v")), // Ch on Ch, 1 and 2 on horrible terms
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a went into a fight with $2v, heavily injuring $2v")), // Ch on Ch, 1 and 2 at cross roads
	std::unique_ptr<EventManager::Event>(new EventManager::Event(1,
				"$1a killed $2v")), // Ch on Ch, 2 dies, 1 gets bad vibe from the org
	std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
				"$1a, $2a went out to steal from $3v, they stole a lot")), // Ch with Ch on Ch, 3 hates 1 and 2
	//std::unique_ptr<EventManager::Event>(new EventManager::Event(0,
	//				"$1 stole from the $2s organization")), // Ch on Org, 2s org stays at bad terms with 1's organisation
	std::unique_ptr<EventManager::Event>(new EventManager::Event(2,
				"$1v was found dead|killed by $2a")), // Ch on Ch, $1 is dead killed by 2, but only the player will know about $1 death but now who did it, but the consequences inside the org will be applied ex. 2 is now disrespected among their group
};
void (*EventManager::functionArray[5])(Character*, Character*) =
{
	[](Character* a, Character* v){ a->GetDisrespectedBy(v); },
	[](Character* a, Character* v){ v->GetKilled(a); },
	[](Character* a, Character* v){ v->GetKilled(nullptr); }, // gets killed, but the killer is unknown
};

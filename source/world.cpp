#include "world.h"
#include <time.h>
#include "logger.h"

World::World()
{
	hourCount = 1;
}

void World::tick()
{
	hourCount++;
	if(hourCount > World::endTime)
	{
		// this DAY ends, thus reset the count
		DateEnd();
		hourCount = 0;
	}
	else if(hourCount == dayTimeEndTick)
	{
		// day time ends, everyone goes to sleep
		//
		Logger::lwarn << "Sleepy Time!" << std::endl;
		for(int i = 0; i < organizations.size(); i++)
		{
			organizations[i]->Call(false);
		}
	}
	else if(hourCount == 1)
	{
		// first hour of the day
		DateStart();

		Logger::lwarn << "Wakey Wakey!" << std::endl;
		for(int i = 0; i < organizations.size(); i++)
		{
			organizations[i]->Call(true);
		}
	}
	else
	{
	}

	/*for(int i = 0; i < organizations.size(); i++)
	{
		organizations[i]->TickUpdate(isDay());
	}*/
}
bool World::isDay()
{
	return World::hourCount < dayTimeEndTick;
}
void World::DateEnd()
{
}
void World::DateStart()
{
}
int World::GetRealTime() const
{
	return World::hourCount / World::divideToGetTime;
}
Character* World::GetRandomCharacterInOrg(Org* org) const
{
	int heat_extend_mod = random::Range(0, org->getHeatExtend());
	int org_layer_index = (org->structure.size() - 1) - heat_extend_mod;
	int index = random::Range(0, org->structure[org_layer_index].size());
	bool loop = false;
	for(;;)
	{
		Character* ch = org->associates[org->structure[org_layer_index][index]];

		if(ch->getIsAlive() == true)
		{
			return ch;
		}
		else
		{
			index++;
			if(index >= org->structure[org_layer_index].size())
			{
				if(loop) {throw;}
				index = 0;
				loop = true;
			}
		}
	}
}
Org* World::GetRandomOrganisation() const
{
	return organizations[random::Range(0, organizations.size())];
}
Org* World::GenerateOrganization()
{
	Org* generated = new Org(Org::S_ORG_NAMES_ARR[random::Range(0, ORG_RANDOM_NAME_ARR_LENGTH)]);
	this->organizations.push_back(generated);
	return generated;
}
Character* World::GenerateCharacter(Org* originOrg, int future_position)
{
	// Character(std::string name, std::string surname, int age, bool gender, Org* org_ptr);
	std::string name;
	std::string nick_name;
	std::string sur_name;

	bool isMale = random::Bool(90);
	int n_index = random::Range(0, CHARACTER_RANDOM_NAME_ARRAY_LENGTH);
	int sur_index = random::Range(0, CHARACTER_RANDOM_SURNAME_ARRAY_LENGTH);

	int age;
	if(future_position == 0)
	{
		age = random::Range(51, 76); // the boss should be older
	}
	else if(future_position == 1)
	{
		age = random::Range(30, 50); // the trusted people should have older age
	}
	else
	{
		age = random::Range(18, 50);
	}

	if(isMale)
	{
		name = Character::S_CHARACTER_MALE_NAMES[n_index];
	}
	else
	{
		name = Character::S_CHARACTER_FEMALE_NAMES[n_index];
	}
	sur_name = Character::S_CHARACTER_SURNAMES[sur_index];

	int nick_len;
	if(future_position == 0)
	{
		nick_len = 1; // for the 0 figures (boss of the org) need's a cool nick name
	}
	else
	{
		nick_len = random::Range(2, 4);
	}

	for(int i = 0; i < nick_len; i++)
	{
		nick_name += Character::S_NICK_NAMES[random::Range(0, CHARACTER_RANDOM_NICK_NAME_ARRAY_LENGTH)];
	}

	Character* character = new Character(
		name,
		sur_name,
		nick_name,
		age,
		isMale,
		originOrg
	);
	this->characters.push_back(character);

	return character;
}
void World::GenerateRandomWorld()
{
	for(int i = 0; i < random::Range(3, 6); i++)
	{
		Org* org = World::GenerateOrganization();

		int member_count = random::Range(6, 100);
		int layer1;
		int layer2;
		if(member_count > 20)
		{
			layer1 = member_count * 0.05f;
			layer2 = (member_count - layer1) * 0.2;
		}
		else
		{
			layer1 = member_count;
			layer2 = 0;
		}

		std::cout << member_count << std::endl;
		std::cout << layer1 << std::endl;
		std::cout << layer2 << std::endl;

		for(int i = 0; i < member_count; i++)
		{
			int position;

			if(i == 0) {position = 0;}
			else if(i <= layer1) {position = 1;}
			else if(i <= layer2) {position = 2;}
			else {position = 3;}

			Character* genChar = World::GenerateCharacter(org, position);

			org->AddAssociate(genChar, position);
		}
		org->Restructure();
	}

	RevaluateOrgRelations();
}
void World::GenerateOrgRelations()
{
	int org_count = organizations.size();

	org_relations = std::vector<std::vector<float>>(org_count);
	for(int i = 0; i < org_count; i++)
	{
		org_relations[i] = std::vector<float>(org_count);
	}
}
void World::RevaluateOrgRelations()
{
	if(org_relations.size() == 0)
	{
		this->GenerateOrgRelations();
	}

	for(int i = 0; i < org_relations.size(); i++)
	{
		for(int j = 0; j < org_relations[i].size(); j++)
		{
			org_relations[i][j] = Org::CompareTwoOrgsAlignment(organizations[i], organizations[j]);
			std::cout << org_relations[i][j] << ' ';
		}
		std::cout << std::endl;
	}
}
void World::PrintOrgTree(Org* org)
{
	World::PrintResponsible(org, 0, 0);
}
void World::PrintResponsible(Org* org, int layer, int index)
{
	Character* top = org->associates[org->structure[layer][index]];
	for(int i = 0; i < layer; i++)
	{
		Logger::ls << '\t';
	}
	if(top->getIsAlive())
	{
		Logger::ls << cstring(top->toString(), static_cast<cstring::COLORS>(layer + 1)) << std::endl;
	}
	else
	{
		Logger::ls << cstring(top->toString(), static_cast<cstring::COLORS>(layer + 1), cstring::RED, cstring::BLINK) << std::endl;
	}

	for(int i = org->responsibility[layer][index].first; i < org->responsibility[layer][index].second + 1; i++)
	{
		World::PrintResponsible(org, layer+1, i);
	}
}
void World::PrintWorldInformation()
{
	for(int j = 0; j < World::organizations.size(); j++)
	{
		Org* org = World::organizations[j];
		Logger::lwarn << "Inspecting the organisation under the name " << org->getName() << std::endl;

		Logger::l << "They call themselves \"" << cstring(org->getName(), cstring::BLACK, cstring::RED) << "\"" << std::endl;

		for(int i = 0; i < org->structure.size(); i++)
		{
			for(int j = 0; j < org->structure[i].size(); j++)
			{
				std::cout << org->structure[i][j] << ", ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		for(int i = 0; i < org->responsibility.size(); i++)
		{
			for(int j = 0; j < org->responsibility[i].size(); j++)
			{
				std::cout << '{' << org->responsibility[i][j].first << " ; " << org->responsibility[i][j].second << "} ";
			}
			std::cout << std::endl;
		}
		World::PrintOrgTree(org);

		Logger::ls << std::endl;
	}
}
World::~World()
{
	for(int i = 0; i < characters.size(); i++)
	{
		delete characters[i];
	}
	for(int i = 0; i < organizations.size(); i++)
	{
		delete organizations[i];
	}
}

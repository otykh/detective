#include "world.h"
#include <cstdlib>
#include <time.h>
#include "logger.h"

World::World(bool(*randBool)(int), int(*randRange)(int, int)) : randBool(randBool), randRange(randRange)
{
}

Character* World::GetRandomCharacterInOrg(Org* org) const
{
	int index = randRange(0, org->associates.size());
	for(;;)
	{
		Character* ch = org->associates[index];
		if(ch->getIsAlive() == true)
		{
			return ch;
		}
		else
		{
			index++;
		}
	}
}
Org* World::GetRandomOrganisation() const
{
	return organizations[randRange(0, organizations.size())];
}
Org* World::GenerateOrganization()
{
	Org* generated = new Org(Org::S_ORG_NAMES_ARR[randRange(0, ORG_RANDOM_NAME_ARR_LENGTH)]);
	this->organizations.push_back(generated);
	return generated;
}
Character* World::GenerateCharacter(Org* originOrg, int future_position)
{
	// Character(std::string name, std::string surname, int age, bool gender, Org* org_ptr);
	std::string name;
	std::string nick_name;
	std::string sur_name;

	bool isMale = randBool(90);
	int n_index = randRange(0, CHARACTER_RANDOM_NAME_ARRAY_LENGTH);
	int sur_index = randRange(0, CHARACTER_RANDOM_SURNAME_ARRAY_LENGTH);

	int age;
	if(future_position == 0)
	{
		age = randRange(51, 76); // the boss should be older
	}
	else if(future_position == 1)
	{
		age = randRange(30, 50); // the trusted people should have older age
	}
	else
	{
		age = randRange(18, 50);
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
		nick_len = randRange(2, 4);
	}

	for(int i = 0; i < nick_len; i++)
	{
		nick_name += Character::S_NICK_NAMES[randRange(0, CHARACTER_RANDOM_NICK_NAME_ARRAY_LENGTH)];
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
	for(int i = 0; i < randRange(3, 6); i++)
	{
		Org* org = World::GenerateOrganization();

		int member_count = randRange(6, 100);
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

		/*for(int i = 0; i < org->structure.size(); i++)
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
		}*/
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

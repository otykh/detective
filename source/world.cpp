#include "world.h"
#include <cstdlib>
#include <time.h>
#include "logger.h"

World::World(bool(*randBool)(int), int(*randRange)(int, int)) : randBool(randBool), randRange(randRange)
{
}

Character* World::GetRandomCharacter()
{
	Character* ch = this->characters[randRange(0, this->characters.size())];
	if(ch->getIsAlive() == false)
	{
		return World::GetRandomCharacter(); //@TODO remove this and use some other method, this will cause stack overflow 
	}
	return ch;
}
Org* World::GetRandomOrganisation()
{
	return organizations[randRange(0, organizations.size())];
}
Org* World::GenerateOrganization()
{
	Org* generated = new Org(Org::S_ORG_NAMES_ARR[randRange(0, ORG_RANDOM_NAME_ARR_LENGTH)]);
	this->organizations.push_back(generated);
	return generated;
}
Character* World::GenerateCharacter(Org* originOrg)
{
	// Character(std::string name, std::string surname, int age, bool gender, Org* org_ptr);
	std::string name;
	std::string nick_name;
	std::string sur_name;
	bool isMale = randBool(90);
	int n_index = randRange(0, CHARACTER_RANDOM_NAME_ARRAY_LENGTH);
	int sur_index = randRange(0, CHARACTER_RANDOM_SURNAME_ARRAY_LENGTH);

	if(isMale)
	{
		name = Character::S_CHARACTER_MALE_NAMES[n_index];
	}
	else
	{
		name = Character::S_CHARACTER_FEMALE_NAMES[n_index];
	}
	sur_name = Character::S_CHARACTER_SURNAMES[sur_index];

	int nick_len = randRange(2, 4);
	for(int i = 0; i < nick_len; i++)
	{
		nick_name += Character::S_NICK_NAMES[randRange(0, CHARACTER_RANDOM_NICK_NAME_ARRAY_LENGTH)];
	}

	Character* character = new Character(
		name,
		sur_name,
		nick_name,
		randRange(18, 50),
		isMale,
		originOrg
	);
	this->characters.push_back(character);

	return character;
}
void World::GenerateRandomWorld()
{
	int seed = time(NULL);
	srand(seed);

	Logger::l << "seed: " << seed << std::endl;

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
		Character* genChar = World::GenerateCharacter(org);

		if(i == 0) {position = 0;}
		else if(i <= layer1) {position = 1;}
		else if(i <= layer2) {position = 2;}
		else {position = 3;}

		org->AddAssociate(genChar, position);
	}
	org->Restructure();
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
	Logger::ls << cstring(top->toString(), static_cast<cstring::COLORS>(layer + 1)) << std::endl;

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

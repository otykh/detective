#pragma once

#include <vector>
#include "character.h"
#include "organization.h"

/*
 * A class database, only controlled from the main entry
 * this class should not be accessed from the outside
 * the vectors are READ ONLY and should not be changed in game
 * use pointers for that reason
 */

class World
{
private:
	// anything that is created, should be placed in this vector, no matter is dead or alive, busted or active etc.
	std::vector<Character*> characters;
	std::vector<Org*> organizations;

	bool (*randBool)(int);
	int (*randRange)(int, int);

public:
	World(bool(*)(int), int(*)(int, int));
	// functions to access the characters etc.
	void GenerateRandomWorld();
	Character* GetRandomCharacter();
	Org* GetRandomOrganisation();
	Org* GenerateOrganization();
	Character* GenerateCharacter(Org* originOrg);

	void PrintWorldInformation();
	static void PrintOrgTree(Org* org);
	static void PrintResponsible(Org* org, int layer, int index);

	~World();
};

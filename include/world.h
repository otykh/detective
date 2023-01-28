#pragma once

#include <vector>
#include "character.h"
#include "organization.h"
#include "rand.h"

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
	std::vector<std::vector<float>> org_relations;

	inline static const int endTime = 72;
	inline static const int divideToGetTime = 3;
	inline static const int dayTimeEndTick = 48;

	int hourCount;

public:
	World();

	void tick();
	bool isDay();
	void DateEnd(); // when this date completes
	void DateStart(); // this this date starts
	int GetRealTime() const;
	// functions to access the characters etc.
	void GenerateRandomWorld();
	void GenerateOrgRelations();
	void RevaluateOrgRelations();
	Character* GetRandomCharacterInOrg(Org*) const;
	Org* GetRandomOrganisation() const;
	Org* GenerateOrganization();
	Character* GenerateCharacter(Org* originOrg, int future_position);

	void PrintWorldInformation();
	static void PrintOrgTree(Org* org);
	static void PrintResponsible(Org* org, int layer, int index);

	~World();
};

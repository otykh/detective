#pragma once

#include <string>
#include <vector>
#include "character.h"
#include <memory>
#include <iostream>

#define ORG_RANDOM_NAME_ARR_LENGTH 29

class Org
{
friend class World;
friend class EventManager;

private:
	static int idCounter;

	const int id;
	const std::string orgName;

	int heat_extend;
	// while the heat system is how bad the air is in the org
	// the heat extend will show how far up the managment the events will happen
	// this will remove any posibility for the boss to be killed at the start of the game
	float heat;
	// [0, 1] range how heated the organization is
	// the large the head the more events and the more impactful they will be
	// heat is increased by the time and investigation

public:
	Org(std::string orgName);

private:
	void Call(bool isDay);

	std::string getName() const;
	float getHeat() const;
	int getHeatExtend() const;
	Character* getCharacterAt(int) const;
	const std::pair<int, int>& getResponsibilityFor(int layer, int) const;
	void CommitCrime();
	void AddAssociate(Character* newCharacter, int position);
	void Restructure();

	//@TODO move this in the private context
	std::vector<Character*> associates;
	// the organisation structure:
	std::vector<std::vector<int>> structure;
	// structure:
	// 0 - is boss
	// 1 - is trusted people
	// 2 - is managers
	// 3 - is workers
	// the smaller the structure the more limited the size of the operation
	std::vector<std::vector<std::pair<int, int>>> responsibility;
	// who is responsible for who
	// it would be that boss is responsible for [0 - trusted_len] on the layer below
	// if both are -1 then the person is not responsible for anyone -> there is no layer below
	// this is for the restructure game machinic @TODO
	// if all workers in managers responsibility are gone (left or dead) then the worker is going
	// to be fired OR they are going to get workers split from other team but rarely

	static float CompareTwoOrgsAlignment(const Org*, const Org*); // [0 - 1] relation status 0 - HATE, 1 - UWU

	static const char* S_ORG_NAMES_ARR[];
};

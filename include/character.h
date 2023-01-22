#pragma once

#include <string>

#define CHARACTER_RANDOM_NAME_ARRAY_LENGTH 28
#define CHARACTER_RANDOM_SURNAME_ARRAY_LENGTH 40
#define CHARACTER_RANDOM_NICK_NAME_ARRAY_LENGTH 147

class Org;

class Character
{
	static int idCounter;
private:
	const int id;
	const std::string name;
	const std::string surname;
	const std::string nick_name;
	const int age; // is not stored as a date, since there is no "year"
	const bool isMale; // 1 is MALE, 0 is FEMALE

	const Org* ptr_associated_organization; // who is a part of this organisation, pointer

	bool isAlive;

	// Organisation Related, used for reason and interigation
	// all in range from 0 (not at all) - 1 (very much so)
	float org_respect;
	float trust;
	float talkative;
	float responsible;
	float respect;
	float naive;
	float hatered;

	// ORG RESPECT respect to the associated organization
	// TRUST how much they trust the org, less trusted the organisation is the more likely the character will try to sabotage or run away, but not nececeraly comply with the officers
	// TALKATIVE how much they are willing to talk when interigated, more talkative characters will reveal more information
	// RESPONSIBLE how much responsible they are, non responsible characters will make more mistakes
	// RESPECT how much respect they have for their peers, high respect individuals are less likely to reveal sensetive information about the higher ups even if are realy talkative
	// NAIVE how easily the person can be tricked, the more naive people will check less and do more without thinking
	// HATERED influences how much the person hates everyone around them especially the higher ups

	// Values and Ideas, used for ruling, reason and personality
	// Gameplay related, DO NOT USE FOR EVENTS
	float value_respect; // will not lose respect most of the time if high
	float value_life; // if high the person will not hate others
	float value_security; // if high the person will be MORE swayed by untrusting others
	float value_money; // if high the person easily bribed, but "depends"
	float value_justice; // if high the person wil be more talkative if trust/hated is low/high respectably
	float value_privacy; // if high the person will rarely share the information about themselves and try to stay low and not attract attention
	float value_family; // if high the person will be scared for their family, people with low family value will not have families
public:
	Character(std::string& i_name, std::string& i_surname, std::string& i_nick, int age, bool isMale, Org* org_ptr);

	std::string getFullName() const;
	std::string getNickName() const;
	int getId() const;
	int getAge() const;
	bool getIsMale() const;
	bool getIsAlive() const;

	std::string toString();

	void GetDisrespectedBy(Character*); // causes high hatered
	void GetKilled(Character*); // get killed by character

	void GetInformedAboutDeath(); // used when someone is killed and proven with evidence, can cause less trust
	friend std::ostream& operator<<(std::ostream& os, const Character& dt);

	static const char* S_CHARACTER_MALE_NAMES[];
	static const char* S_CHARACTER_FEMALE_NAMES[];
	static const char* S_CHARACTER_SURNAMES[];
	static const char* S_NICK_NAMES[];
};

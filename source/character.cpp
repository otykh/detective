#include "character.h"
#include <iostream>

int Character::idCounter = 0;

Character::Character(std::string& i_name, std::string& i_surname, std::string& i_nick, int i_age, bool i_gender, Org* i_org_ptr) :
	id(idCounter++),
	name(i_name),
	surname(i_surname),
	nick_name(i_nick),
	age(i_age),
	isMale(i_gender),
	ptr_associated_organization(i_org_ptr)
{
	this->isAlive = true;
}

std::string Character::getFullName() const
{
	return (this->name + ' ' + this->surname);
}
std::string Character::getNickName() const
{
	return this->nick_name;
}
int Character::getId() const
{
	return this->id;
}
int Character::getAge() const
{
	return this->age;
}
bool Character::getIsMale() const
{
	return this->isMale;
}
bool Character::getIsAlive() const
{
	return this->isAlive;
}

void Character::GetDisrespectedBy(Character* attacker)
{
	this->hatered += 0.1f * this->value_life;
	if(this->hatered > 1) {
		this->hatered = 1;
	}
}
void Character::GetKilled(Character* attacker)
{
	this->isAlive = false; // now this character is DEAD
	//@TODO report who is the attacker and at which operation GetInformedAboutDeath()
}
void Character::GetInformedAboutDeath()
{

}
std::string Character::toString()
{
	return this->getFullName() + " aka. \"" + this->getNickName() + "\" " + std::to_string(this->getAge()) + " years old " + (this->getIsMale() ? "Male " : "Female ") + ", Status: " + (this->getIsAlive() ? "Alive " : "DEAD ");
}
std::ostream& operator<<(std::ostream& os, const Character& dt)
{
	os << dt.getFullName() << " aka. \"" << dt.getNickName() << "\" " << dt.getAge() << " years old " << (dt.getIsMale() ? "Male " : "Female ") << ", Status: " << (dt.getIsAlive() ? "Alive " : "DEAD ");
    return os;
}

const char* Character::S_CHARACTER_MALE_NAMES[CHARACTER_RANDOM_NAME_ARRAY_LENGTH] =
{
	"James",
	"Robert",
	"John",
	"Michael",
	"David",
	"William",
	"Richard",
	"Joseph",
	"Thomas",
	"Charles",
	"Christopher",
	"Daniel",
	"Matthew",
	"Anthony",
	"Mark",
	"Donald",
	"Steven",
	"Paul",
	"Andrew",
	"Joshua",
	"Airam",
	"Aday",
	"Yerai",
	"Jonay",
	"Beneharo",
	"Ayoze",
	"Nauzet",
	"Rayco"
};
const char* Character::S_CHARACTER_FEMALE_NAMES[CHARACTER_RANDOM_NAME_ARRAY_LENGTH] =
{
	"Mary",
    "Patricia",
    "Jennifer",
	"Linda",
    "Elizabeth",
    "Barbara",
    "Susan",
    "Jessica",
    "Sarah",
    "Karen",
    "Lisa",
    "Nancy",
    "Betty",
    "Margaret",
    "Sandra",
    "Ashley",
    "Kimberly",
    "Emily",
    "Donna",
    "Michelle",
	"Naira",
	"Idaira",
	"Yurena",
	"May",
	"Adassa",
	"Dacil",
	"Guacimara",
	"Dacil"
};
const char* Character::S_CHARACTER_SURNAMES[CHARACTER_RANDOM_SURNAME_ARRAY_LENGTH] =
{
	"Smith",
	"Johnson",
	"Williams",
	"Brown",
	"Jones",
	"Miller",
	"Davis",
	"Garcia",
	"Rodriguez",
	"Wilson",
	"Martinez",
	"Anderson",
	"Taylor",
	"Thomas",
	"Hernandez",
	"Moore",
	"Martin",
	"Jackson",
	"Thompson",
	"White",
	"Garcia",
	"Rodriguez",
	"Gonzalez",
	"Fernandez",
	"Lopez",
	"Martinez",
	"Sanchez",
	"Perez",
	"Gomez",
	"Martin",
	"Jimenez",
	"Ruiz",
	"Hernandez",
	"Diaz",
	"Moreno",
	"Muñoz",
	"Alvarez",
	"Romero",
	"Alonso",
	"Gutierrez"
};
const char* Character::S_NICK_NAMES[CHARACTER_RANDOM_NICK_NAME_ARRAY_LENGTH] =
{
	"Sunshine", "Best",
	"Freez", "Bold",
	"River", "Potato",
	"River", "The",
	"Ruby", "Door",
	"Lively",
	"Skill" , "Gx",
	"Hack", "Lively",
	"Python",
	"Duck", "Goku",
	"Toto", "Ze",
	"Black", "Colossus",
	"Night", "Sir",
	"Iron", "Poke",
	"Boy", "Pretty",
	"Mamba", "Morphine",
	"Small", "Best",
	"Sir", "Riku",
	"Bolt", "Good",
	"Steel", "Rex",
	"Freestyle", "Small",
	"Gama", "Bear",
	"Riku", "Shadow",
	"Russian", "Stun",
	"Troll", "Maj",
	"Dog", "Steak",
	"Rex", "Drake",
	"Frost", "Lively",
	"Sniper", "River",
	"Bannana", "Flying",
	"Wait", "Master",
	"Boy", "Wood",
	"Paper", "Sunrise",
	"Blade", "Sol",
	"Ghost", "Tyra",
	"Godzilla", "Doctor",
	"Ninja", "Crazy",
	"Sunrise", "Morphine",
	"Luck", "Python",
	"Princess", "Dela",
	"Dragon", "Fr",
	"Hydro", "Gx",
	"Red", "Devil",
	"Sunrise", "Best",
	"Dela", "Gamer",
	"Miss", "Sir",
	"Riku", "Bread",
	"Galactic", "Wolf",
	"Never", "Freez",
	"Covid", "Onix",
	"Alpha", "River",
	"Tek", "Nova",
	"Mamba", "Flamme",
	"Black", "Craby",
	"Gt", "Fish",
	"Naruto", "Reality",
	"Dog", "Naruto",
	"Primus", "Stun",
	"Thunder", "Dia",
	"Primus", "Raptor",
	"Maj", "Python",
	"French", "Pepito",
	"Flamme", "Witcher",
	"Good", "Warrior",
	"Sunshine", "Dog",
	"Bad", "Oxygen",
	"Emerald", "Sniper",
	"Poke", "Steel",
	"Mini", "Freez",
	"Beta", "Sun",
	"Craby", "Badboy",
	"DelaMy",
	"Bad",
	"Good",
	"Good",
	"Sx",
	"Fun",
	"Goodly"
};

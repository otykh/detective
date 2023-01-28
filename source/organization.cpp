#include "organization.h"

int Org::idCounter = 0;
Org::Org(std::string i_orgName) : orgName(i_orgName), id(Org::idCounter++)
{
	heat_extend = 0;
	heat = 0;
}

void Org::Call(bool isDay)
{
	for(int i = 0; i < associates.size(); i++)
	{
		// only change from SLEEP -> ALIVE
		// only change from ALIVE -> SLEEP
		if(isDay)
		{
			if(associates[i]->get_status() == Character::Sleeping)
			{
				associates[i]->change_status(Character::Alive);
			}
		}
		else
		{
			if(associates[i]->get_status() == Character::Alive)
			{
				associates[i]->change_status(Character::Sleeping);
			}
		}
	}
}

void Org::AddAssociate(Character* newCharacter, int position)
{
	associates.push_back(newCharacter);

	if(position >= structure.size())
	{
		structure.push_back(std::vector<int>());
	}

	structure[position].push_back(associates.size() - 1);
}
void Org::CommitCrime()
{
	//@TODO make this in a normal way
	if(this->structure.size() < 3)
	{
		return;
	}
	// what is a criminal without criminal activity
	// each org will do some crimes depending on their situation
	// some random, some not so much
	// first, chose the leader of this crime
	std::vector<int>& leaderArr = structure[structure.size() - 2];
	int person = random::Range(0, leaderArr.size());

	const std::pair<int, int>& groupRange = getResponsibilityFor(structure.size() - 2, person);
	//std::pair<int, int>& groupRange = responsibility[responsibility.size() - 2][person];

	Character* leader = getCharacterAt(leaderArr[person]);

	std::cout << *leader << " lead a crime action with:" << std::endl;
	for(int i = groupRange.first; i < groupRange.second + 1; i++)
	{
		std::cout << getCharacterAt(structure[structure.size() - 1][i])->getFullName() << ", ";
	}
	std::cout << std::endl;
}
void Org::Restructure()
{
	// should be called once
	responsibility.clear();
	for(int i = 0; i < structure.size(); i++)
	{
		responsibility.push_back( // responsibility list pushesh new layer with
				std::vector<std::pair<int,int>>(structure[i].size())); // the size of workers in this region

		int everyone_size = 0;
		int squad_size = 0;
		if(i + 1 != structure.size())
		{
			everyone_size = structure[i+1].size();
			squad_size = everyone_size / structure[i].size();
		}

		for(int j = 0; j < structure[i].size(); j++)
		{
			if(structure[i].size() == j + 1) // last element
			{
				responsibility[responsibility.size() - 1][j] =
						std::pair<int, int>(squad_size * j, everyone_size - 1);
			}
			else
			{
				responsibility[responsibility.size() - 1][j] =
						std::pair<int, int>(squad_size * j, squad_size * (j + 1) - 1);
			}
		}
	}
}
Character* Org::getCharacterAt(int n) const
{
	return associates[n];
}
const std::pair<int, int>& Org::getResponsibilityFor(int layer, int n) const
{
	return responsibility[layer][n];
}
std::string Org::getName() const
{
	return orgName;
}
float Org::getHeat() const
{
	return heat;
}
int Org::getHeatExtend() const
{
	return heat_extend;
}

float Org::CompareTwoOrgsAlignment(const Org* orgOne, const Org* orgTwo)
{
	Character* bossOne = orgOne->associates[orgOne->structure[0][0]]; // boss in first org
	Character* bossTwo = orgTwo->associates[orgTwo->structure[0][0]]; // boss in second org

	float relation = 0;

	relation += std::abs(bossOne->get_value_respect() - bossTwo->get_value_respect());
    relation += std::abs(bossOne->get_value_life() - bossTwo->get_value_life());
    relation += std::abs(bossOne->get_value_security() - bossTwo->get_value_security());
    relation += std::abs(bossOne->get_value_money() - bossTwo->get_value_money());
    relation += std::abs(bossOne->get_value_justice() - bossTwo->get_value_justice());
    relation += std::abs(bossOne->get_value_privacy() - bossTwo->get_value_privacy());
    relation += std::abs(bossOne->get_value_family() - bossTwo->get_value_family());

	relation = relation / 7;

	return 1 - std::abs(relation);
}
const char* Org::S_ORG_NAMES_ARR[ORG_RANDOM_NAME_ARR_LENGTH] //@TODO expnd
{
	"Esquivel Hermanos",
	"Valencia S.L.",
	"Trejo S.A.",
	"Corrales e Hijos",
	"Renteria S.L.",
	"Corral Corp.",
	"Barela of Carrasquillo",
	"Aponte S.A.",
	"Cisneros S.A.",
	"Granado of Malave",
	"Valle Solano organization",
	"Cortés",
	"Berríos Archuleta",
	"Salinas S.L.",
	"Avila Banda",
	"Carrero e Hijos",
	"Ocasio S.L.",
	"Olmos S.A.",
	"Melgar Hermanos",
	"Barrientos of Olivas",
	"Garcia Jaramillo organization",
	"Bustos Acevedo",
	"Garcia Carrero South",
	"Naranjo Salinas Brothers",
	"Brito Paez Brothers",
	"Escobar organization",
	"Duenas Brothers",
	"Alicea",
	"Berríos"
};

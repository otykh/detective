#include "organization.h"

int Org::idCounter = 0;
Org::Org(std::string i_orgName) : orgName(i_orgName), id(Org::idCounter++)
{
	heat_extend = 0;
	heat = 0;
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

	relation += bossOne->get_value_respect() - bossTwo->get_value_respect();
    relation += bossOne->get_value_life() - bossTwo->get_value_life();
    relation += bossOne->get_value_security() - bossTwo->get_value_security();
    relation += bossOne->get_value_money() - bossTwo->get_value_money();
    relation += bossOne->get_value_justice() - bossTwo->get_value_justice();
    relation += bossOne->get_value_privacy() - bossTwo->get_value_privacy();
    relation += bossOne->get_value_family() - bossTwo->get_value_family();

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

#include "rand.h"

void random::set(int seed)
{
	srand(seed);
}
bool random::Bool(int percent)
{
	return (rand() % 101) <= percent;
}
float random::Float()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}
int random::Range(int min, int max)
{
	if(min == 0 && max == 0)
	{
		return 0;
	}
	if(min == 0)
	{
		return (rand() % max) + min;
	}
	else
	{
		int range = max - min + 1;
		return rand() % range + min;
	}
}

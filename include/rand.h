#pragma once

#include <cstdlib>

class random
{
public:
	static void set(int);
	static bool Bool(int percent);
	static int Range(int min, int max);
	static float Float();
};

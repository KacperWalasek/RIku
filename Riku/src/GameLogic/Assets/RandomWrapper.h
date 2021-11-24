#pragma once
#include <cstdlib>

class RandomWrapper
{
public:
	RandomWrapper() {};
	int generate(int x, int y)
	{
		return std::rand() % (y - x) + x;
	}
};


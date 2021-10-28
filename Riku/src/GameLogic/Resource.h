//Kacper Walasek
#pragma once
#include <string>

class Resource
{
	std::string name;
public:
	Resource(std::string name) :name(name) {}
	std::string getName() const
	{
		return name;
	}
};


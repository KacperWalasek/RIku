// Kacper Walasek
#pragma once
#include <string>

// Z tej klasy dziedziczy ka�dy element, kt�ry jest wczytywany z pliku
class IResource
{
public:
	virtual std::string getName() const = 0;
};

// Prosty asset
class Resource
{
	std::string name;
public:
	Resource(std::string name):name(name) {}
	std::string getName() const
	{
		return name;
	} 
};


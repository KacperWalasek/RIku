// Kacper Walasek
#pragma once
#include <string>

// Z tej klasy dziedziczy ka¿dy element, który jest wczytywany z pliku
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


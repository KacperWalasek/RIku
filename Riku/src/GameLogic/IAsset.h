// Kacper Walasek
#pragma once
#include <string>

// Z tej klasy dziedziczy ka�dy element, kt�ry jest wczytywany z pliku
class IAsset
{
public:
	virtual std::string getName() const = 0;
};

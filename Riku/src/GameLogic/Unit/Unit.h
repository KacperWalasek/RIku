#pragma once
#include "../IHookable.h"
#include "../IAsset.h"

class Unit : public IHookable, public IAsset
{
	std::string type;
public:
	Unit(std::string type, int baseMovementPoints);
	// te pola s� publiczne, �eby hooki mog�y je zmienia�
	int movementPoints;
	int baseMovementPoints;

	void useMovementPoints(int points);
	void restoreMovementPoints();

};


#pragma once
#include "../IHookable.h"
#include "../IAsset.h"

class Unit : public IHookable, public IAsset
{
	std::string type;
public:
	Unit(std::string type, int baseMovementPoints);
	// te pola s¹ publiczne, ¿eby hooki mog³y je zmieniaæ
	int movementPoints;
	int baseMovementPoints;

	void useMovementPoints(int points);
	void restoreMovementPoints();

};


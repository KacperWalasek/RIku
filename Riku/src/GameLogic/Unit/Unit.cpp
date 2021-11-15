#include "Unit.h"


Unit::Unit(std::string type, int baseMovementPoints)
	: type(type), baseMovementPoints(baseMovementPoints), movementPoints(baseMovementPoints)
{}

void Unit::useMovementPoints(int points)
{
	movementPoints -= points;
	if (movementPoints < 0)
		movementPoints = 0;
}

void Unit::restoreMovementPoints()
{
	movementPoints = baseMovementPoints;
}

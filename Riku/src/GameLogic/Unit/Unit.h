#pragma once
#include "../IHookable.h"
#include "../IAsset.h"
#include "../LoadedHookable.h"

class Unit : public IHookable, public IAsset
{
	std::string type;
	std::string name;
	LoadedHookable loadedHookable;
public:
	Unit(std::string type, std::string name, int baseMovementPoints, std::map<std::string, sol::function> hooks);
	// te pola s� publiczne, �eby hooki mog�y je zmienia�
	int movementPoints;
	int baseMovementPoints;

	void useMovementPoints(int points);
	void restoreMovementPoints();

	// Odziedziczono za po�rednictwem elementu IHookable
	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override;

	virtual std::shared_ptr<IMove> onTurnEnd() override;

	virtual std::shared_ptr<IMove> onTurnBegin() override;

	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;


	// Odziedziczono za po�rednictwem elementu IAsset
	virtual std::string getName() const override;

};

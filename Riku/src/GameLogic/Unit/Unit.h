#pragma once
#include "../IHookable.h"
#include "../IAsset.h"
#include "../LoadedHookable.h"

class Unit : public IHookable, public IAsset
{
	std::string type;
	std::string name;
	LoadedHookable loadedHookable;
	int mapX = 0, mapY = 0;
public:
	Unit(std::string type, std::string name, int baseMovementPoints, const std::map<std::string, sol::function>& hooks);
	// te pola s¹ publiczne, ¿eby hooki mog³y je zmieniaæ
	int movementPoints;
	int baseMovementPoints;

	void useMovementPoints(int points);
	void restoreMovementPoints();


	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override;

	virtual std::shared_ptr<IMove> onTurnEnd() override;

	virtual std::shared_ptr<IMove> onTurnBegin() override;

	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;

	virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;

	virtual std::string getName() const override;
	
	int getMapX();
	int getMapY();

};

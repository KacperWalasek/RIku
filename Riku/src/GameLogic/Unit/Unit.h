#pragma once
#include "../Hooks/IHookable.h"
#include "../IAsset.h"
#include "../Hooks/LoadedHookable.h"

class Unit : public IHookable, public IAsset
{
	std::string type;
	std::string name;
	LoadedHookable loadedHookable;
	int player;
public:
	Unit(std::string type, std::string name, int player, int baseMovementPoints, const std::vector<std::string>& miniunits, const std::map<std::string, sol::function>& hooks);

	int mapX = 0, mapY = 0;
	int movementPoints;
	int baseMovementPoints;
	std::vector<std::string> miniunits;

	void useMovementPoints(int points);
	void restoreMovementPoints();


	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override;

	virtual std::shared_ptr<IMove> onTurnEnd() override;

	virtual std::shared_ptr<IMove> onTurnBegin() override;

	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;

	virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;

	virtual std::string getName() const override;
	
	int getMapX() const;
	int getMapY() const;

	int getOwner() const;
};

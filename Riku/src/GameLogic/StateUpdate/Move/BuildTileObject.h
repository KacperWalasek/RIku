#pragma once
#include "IMove.h"
#include "../../Tile/Tile.h"
#include "../../LogicAssets.h"
#include "../../Assets/Asset.h"
class BuildTileObject : public IMove
{
	int player;
	std::pair<int, int> tile;
	std::string tileObject;
	LogicAssets& assets;
public:
	BuildTileObject(int player, std::pair<int, int> tile, std::string tileObject, LogicAssets& assets);
	virtual std::shared_ptr<Patch> createPatch(const GameState& state) const override;
	virtual bool isDoable(const GameState& state) const override;
	virtual std::shared_ptr<IMove> asPointner() const override;
};


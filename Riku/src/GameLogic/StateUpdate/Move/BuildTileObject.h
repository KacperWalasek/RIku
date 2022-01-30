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
	std::shared_ptr<ITileObject> createObject(const LogicAssets& assets) const;
public:
	BuildTileObject(int player, std::pair<int, int> tile, std::string tileObject);
	virtual std::shared_ptr<Patch> createPatch(const GameState& state, const LogicAssets& assets) const override;
	virtual bool isDoable(const GameState& state, const LogicAssets& assets, bool popup = false) const override;
	virtual std::shared_ptr<IMove> asPointner() const override;
};


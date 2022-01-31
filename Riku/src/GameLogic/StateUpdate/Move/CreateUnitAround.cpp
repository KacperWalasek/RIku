#include "CreateUnitAround.h"
#include "CreateUnit.h"
#include "../../Utils/LogicUtils.h"
CreateUnitAround::CreateUnitAround(std::string unit, int mapX, int mapY)
	: unit(unit), mapX(mapX), mapY(mapY)
{}

std::shared_ptr<Patch> CreateUnitAround::createPatch(const GameState & state, const LogicAssets & assets) const
{
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++) 
		{
			CreateUnit createMove(unit, mapX + i, mapY + j);
			if (!(i == 0 && j == 0) && createMove.isDoable(state, assets))
				return createMove.createPatch(state, assets);
		}

	return nullptr;
}

bool CreateUnitAround::isDoable(const GameState& state, const LogicAssets& assets, bool popup) const
{
	for (int i = -1; i < 2; i++)
		for (int j = -1; j < 2; j++)
			if (!(i == 0 && j == 0) && CreateUnit(unit, mapX + i, mapY + j).isDoable(state, assets))
				return true;
	if (popup)
		LogicUtils::addPopup("No tile available!");
	return false;
}

std::shared_ptr<IMove> CreateUnitAround::asPointner() const
{
	return std::make_shared<CreateUnitAround>(unit, mapX, mapY);
}

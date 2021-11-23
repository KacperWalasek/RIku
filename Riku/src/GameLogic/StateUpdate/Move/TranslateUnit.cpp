#include "TranslateUnit.h"
#include "../Patch/Patch.h"
#include "../../Unit/Unit.h"
#include "../../GameState.h"

TranslateUnit::TranslateUnit(int fromX, int fromY, int toX, int toY)
    : fromX(fromX), fromY(fromY), toX(toX), toY(toY) {}

std::shared_ptr<Patch> TranslateUnit::createPatch(const GameState& state, const LogicAssets& assets) const
{
    auto unit = state.map[fromX][fromY].unit;
    return std::make_shared<Patch>(TilePatch({ toX, toY }, unit) + (Patch)TilePatch({ fromX,fromY },false,true));
}

bool TranslateUnit::isDoable(const GameState& state, const LogicAssets& assets) const
{
    int dist = abs(toX - fromX) + abs(toY - fromY);
    return dist == 1 && state.map[fromX][fromY].unit;
}

std::shared_ptr<IMove> TranslateUnit::asPointner() const
{
    return std::make_shared<TranslateUnit>(fromX,fromY,toX,toY);
}

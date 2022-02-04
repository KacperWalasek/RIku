#include "MiniGameAssetInitializer.h"
#include "../GameLogic/Assets/AssetData.h"
#include "StateUpdate/Move/CreateMiniUnit.h"
#include "StateUpdate/Move/MiniResign.h"
#include "Hooks/MiniMoveWrapper.h"
#include "StateUpdate/Move/MiniAttack.h"
#include "StateUpdate/Move/CombinedMiniMove.h"

void minigame::MiniGameAssetInitializer::initAsset(std::shared_ptr<sol::state> lua) const
{
	lua->new_usertype<logic::AssetData>("AssetData",
		sol::constructors<logic::AssetData(const logic::AssetData&)>(),
		"as_int", &logic::AssetData::asInt
		);
	lua->new_usertype<CreateMiniUnit>("CreateMiniUnit",
		sol::constructors<CreateMiniUnit(std::string,int,int)>()
		);
	lua->new_usertype<MiniAttack>("MiniAttack",
		sol::constructors<MiniAttack(int, int)>()
		);
	lua->new_usertype<CombinedMiniMove>("CombinedMove",
		sol::constructors<CombinedMiniMove(MiniMoveWrapper, MiniMoveWrapper)>()
		);
	lua->new_usertype<MiniResign>("MiniResign",
		sol::constructors<MiniResign()>()
		);
	lua->new_usertype<MiniMoveWrapper>("MoveWrapper",
		sol::constructors<MiniMoveWrapper(MiniResign), MiniMoveWrapper(CreateMiniUnit), MiniMoveWrapper(MiniAttack)>()
		);
}

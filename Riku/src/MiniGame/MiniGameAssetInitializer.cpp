#include "MiniGameAssetInitializer.h"
#include "../GameLogic/Assets/AssetData.h"
#include "StateUpdate/Move/CreateMiniUnit.h"

void MiniGameAssetInitializer::initAsset(std::shared_ptr<sol::state> lua) const
{
	lua->new_usertype<logic::AssetData>("AssetData",
		sol::constructors<logic::AssetData(const logic::AssetData&)>(),
		"as_int", &logic::AssetData::asInt
		);
	lua->new_usertype<CreateMiniUnit>("CreateMiniUnit",
		sol::constructors<CreateMiniUnit(std::string,int,int)>()
		);
}

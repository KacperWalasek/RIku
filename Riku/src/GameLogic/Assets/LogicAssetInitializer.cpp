#include "LogicAssetInitializer.h"
#include "AssetData.h"
#include "../StateUpdate/Move/TestMove.h"
#include "../StateUpdate/Move/CreateUnit.h"
#include "../StateUpdate/Move/UseResources.h"
#include "../Hooks/MoveWrapper.h"
#include "../Tile/TileDescription.h"
#include "../StateUpdate/Move/CombinedMove.h"

void LogicAssetInitializer::initAsset(std::shared_ptr<sol::state> lua) const
{
	lua->new_usertype<logic::AssetData>("AssetData",
		sol::constructors<logic::AssetData(const logic::AssetData&)>(),
		"as_int", &logic::AssetData::asInt
		);
	lua->new_usertype<TestMove>("TestMove",
		sol::constructors<TestMove()>()
		);
	lua->new_usertype<CreateUnit>("CreateUnit",
		sol::constructors<CreateUnit(std::string, int, int)>()
		);
	lua->new_usertype<UseResources>("UseResources",
		sol::constructors<UseResources(int, int), UseResources(std::string, int)>()
		);
	lua->new_usertype<MoveWrapper>("MoveWrapper",
		sol::constructors<MoveWrapper(TestMove), MoveWrapper(CreateUnit), MoveWrapper(CombinedMove), MoveWrapper(UseResources)>()
		);
	lua->new_usertype<TileDescription>("TileDescription",
		sol::constructors<TileDescription(int, std::string, std::string, std::string)>()
		);
	lua->new_usertype<CombinedMove>("CombinedMove",
		sol::constructors<CombinedMove(MoveWrapper, MoveWrapper)>()
		);
}

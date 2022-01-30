#include "LogicAssetInitializer.h"
#include "AssetData.h"
#include "../StateUpdate/Move/TestMove.h"
#include "../StateUpdate/Move/CreateUnit.h"
#include "../StateUpdate/Move/UseResources.h"
#include "../Hooks/MoveWrapper.h"
#include "../Tile/TileDescription.h"
#include "../StateUpdate/Move/CombinedMove.h"
#include "../StateUpdate/Move/AddMiniUnit.h"
#include "../StateUpdate/Move/AddSkill.h"
#include "../StateUpdate/Move/CreateUnitAround.h"

void LogicAssetInitializer::initAsset(std::shared_ptr<sol::state> lua) const
{
	lua->new_usertype<logic::AssetData>("AssetData",
		sol::constructors<logic::AssetData(const logic::AssetData&)>(),
		"as_int", &logic::AssetData::asInt,
		"as_string", &logic::AssetData::asString
		);
	lua->new_usertype<TestMove>("TestMove",
		sol::constructors<TestMove(std::string)>()
		);
	lua->new_usertype<CreateUnit>("CreateUnit",
		sol::constructors<CreateUnit(std::string, int, int)>()
		);
	lua->new_usertype<CreateUnitAround>("CreateUnitAround",
		sol::constructors<CreateUnitAround(std::string, int, int)>()
		);
	lua->new_usertype<UseResources>("UseResources",
		sol::constructors<UseResources(int, int), UseResources(std::string, int)>()
		);
	lua->new_usertype<AddMiniUnit>("AddMiniUnit",
		sol::constructors<AddMiniUnit(std::string, int, int)>()
		);
	lua->new_usertype<AddSkill>("AddSkill",
		sol::constructors<AddSkill(std::string, int, int)>()
		);
	lua->new_usertype<MoveWrapper>("MoveWrapper",
		sol::constructors<
			MoveWrapper(TestMove), 
			MoveWrapper(CreateUnit), 
			MoveWrapper(CombinedMove), 
			MoveWrapper(UseResources), 
			MoveWrapper(AddSkill),
			MoveWrapper(CreateUnitAround),
			MoveWrapper(AddMiniUnit)>()
		);
	lua->new_usertype<TileDescription>("TileDescription",
		sol::constructors<TileDescription(int, std::string, std::string, std::string), TileDescription(int, std::string, std::string, std::string, std::string)>()
		);
	lua->new_usertype<CombinedMove>("CombinedMove",
		sol::constructors<CombinedMove(MoveWrapper, MoveWrapper)>()
		);
}

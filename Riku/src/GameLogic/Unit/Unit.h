#pragma once
#include "../Hooks/IHookable.h"
#include "../IAsset.h"
#include "../Hooks/LoadedHookable.h"
#include "../Utils/DeserializationData.h"
#define CEREAL_FUTURE_EXPERIMENTAL
#include <cereal/archives/adapters.hpp>
#include <cereal/access.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

class Unit : public IHookable, public IAsset
{
	std::string id;

	std::string type;
	std::string name;
	LoadedHookable loadedHookable;
	int player;
public:
	Unit(std::string type, std::string name, int player, int baseMovementPoints, const std::vector<std::string>& miniunits, const std::map<std::string, sol::function>& hooks, std::string id = "");

	int mapX = 0, mapY = 0;
	int movementPoints;
	int baseMovementPoints;
	std::vector<std::string> miniunits;
	std::vector<std::string> skills;

	void useMovementPoints(int points);
	void restoreMovementPoints();


	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) override;

	virtual std::shared_ptr<IMove> onTurnEnd() override;

	virtual std::shared_ptr<IMove> onTurnBegin() override;

	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;

	virtual std::shared_ptr<IMove> onBeingCreated() override;

	virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;

	virtual std::string getName() const override;
	
	int getMapX() const;
	int getMapY() const;

	int getOwner() const;

	virtual std::string getId() const override;


	template <class Archive>
	void serialize(Archive& archive) const {
		archive(player, name, id, type, mapX, mapY, movementPoints, baseMovementPoints, skills, miniunits);
	}

	template <class Archive>
	static void load_and_construct(Archive& archive,
		cereal::construct<Unit>& construct) {
		std::string id, type, name;
		int player, mapX, mapY, movementPoints, baseMovementPoints;
		std::vector<std::string> miniunits, skills;
		archive(player, name, id, type, mapX, mapY, movementPoints, baseMovementPoints, skills, miniunits);
		DeserializationData data = cereal::get_user_data<DeserializationData>(archive);
		auto it = data.assets.units.find(name);
		if (it == data.assets.units.end())
			throw;
		auto hooks = it->second.getFunctions();
		construct(type, name, player, baseMovementPoints, miniunits, hooks, id);
		construct->movementPoints = movementPoints;
		construct->mapX = mapX;
		construct->mapY = mapY;
	}
};

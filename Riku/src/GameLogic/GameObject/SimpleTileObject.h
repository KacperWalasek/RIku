//Kacper Walasek
#pragma once
#include <cereal/access.hpp>
#define CEREAL_FUTURE_EXPERIMENTAL
#include <cereal/archives/adapters.hpp>
#include "../Resource.h"
#include "ITileObject.h"
#include "../Hooks/LoadedHookable.h"
#include <map>
#include "../GameState.h"
#include "../Hooks/GUIDescription.h"
#include "../Utils/DeserializationData.h"

class SimpleTileObject : public ITileObject
{
	std::string id;

	LoadedHookable loadedHookable;
 	std::string name;
	int player;
public:
	GUIDescription gui;
	SimpleTileObject(std::string name, int player, const std::map<std::string, sol::function>& hooks, GUIDescription gui, std::string id = "");

	virtual std::string getName() const override;
	virtual int getOwner() const override;
	virtual double getModifiedCost(double cost) const override;

	virtual std::shared_ptr<IMove> onDestroy(int mapX, int mapY) override;
	virtual std::shared_ptr<IMove> onTurnEnd(int mapX, int mapY) override;
	virtual std::shared_ptr<IMove> onTurnBegin(int mapX, int mapY) override;
	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) override;
	virtual std::shared_ptr<IMove> onBeingCreated(int mapX, int mapY) override;
	virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) override;

	virtual const GUIDescription& getGuiDescription() override;
	virtual std::shared_ptr<IMove> onOptionChosen(int index, int mapX, int mapY) override;

	virtual std::string getId() const override;

	template <class Archive>
	void serialize(Archive& archive) const {
		archive(player, name, id);
	}

	template <class Archive>
	static void load_and_construct(Archive& archive,
		cereal::construct<SimpleTileObject>& construct) {
		int player;
		std::string name;
		std::string id;
		archive(player, name, id);
		DeserializationData data = cereal::get_user_data<DeserializationData>(archive);
		auto it = data.assets.tileObjects.find(name);
		if (it == data.assets.tileObjects.end())
			throw;
		const auto& hooks = it->second.getFunctions();
		construct(name, player, hooks, GUIDescription(hooks), id);
	}
}; 
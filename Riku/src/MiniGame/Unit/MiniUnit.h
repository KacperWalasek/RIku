#pragma once
#include <string>
#include "../Hooks/MiniLoadedHookable.h"
#include "../../GameLogic/IAsset.h"
#include "../../GameLogic/Utils/DeserializationData.h"
#define CEREAL_FUTURE_EXPERIMENTAL
#include <cereal/archives/adapters.hpp>
#include <cereal/access.hpp>

namespace minigame
{
    class MiniUnit :
        public IMiniHookable, public IAsset
    {
        std::string id;

        std::string name;
        MiniLoadedHookable loadedHookable;
        int owner;
    public:
        MiniUnit(std::string name, int owner, int baseMovementPoints, const std::map<std::string, sol::function>& hooks, std::string id = "");

        int mapX = 0, mapY = 0;
        int movementPoints;
        int baseMovementPoints;

        virtual std::shared_ptr<IMiniMove> onDestroy(bool byOwner) override;
        virtual std::shared_ptr<IMiniMove> onTurnEnd() override;
        virtual std::shared_ptr<IMiniMove> onTurnBegin() override;
        virtual std::shared_ptr<IMiniMove> onBeingPlaced(int mapX, int mapY) override;

        virtual std::string getName() const override;

        int getMapX() const;
        int getMapY() const;
        int getOwner() const;
        virtual std::string getId() const override;

        template <class Archive>
        void serialize(Archive& archive) const {
            archive(name, id, owner, mapX, mapY, movementPoints, baseMovementPoints);
        }

        template <class Archive>
        static void load_and_construct(Archive& archive,
            cereal::construct<MiniUnit>& construct) {
            std::string id, name;
            int owner, mapX, mapY, movementPoints, baseMovementPoints;
            archive(name, id, owner, mapX, mapY, movementPoints, baseMovementPoints);
            DeserializationData data = cereal::get_user_data<DeserializationData>(archive);
            auto it = data.miniGameAssets.units.find(name);
            if (it == data.miniGameAssets.units.end())
                throw;
            const auto& hooks = it->second.getFunctions();
            construct(name, owner, baseMovementPoints, hooks, id);
            construct->movementPoints = movementPoints;
            construct->mapX = mapX;
            construct->mapY = mapY;
        }
    };

}
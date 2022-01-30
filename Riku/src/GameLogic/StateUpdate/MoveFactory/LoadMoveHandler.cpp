#include "LoadMoveHandler.h"
#include "../MoveDescriptions/StringMoveDescription.h"
#include "../Move/Load.h"
#include <fstream>
#include "../../Utils/LogicUtils.h"
#include "../Patch/Patch.h"
#include "../../LogicAssets.h"
#include <cereal/archives/binary.hpp>
#define CEREAL_FUTURE_EXPERIMENTAL
#include <cereal/archives/adapters.hpp>
#include <cereal/types/polymorphic.hpp>
#include "../../../MiniGame/StateUpdate/Patch/MiniPatch.h"
#include "../../../MiniGame/MiniGame.h"
#include "../../Utils/SaveStruct.h"
#include "../../../Network/WebModule.h"

LoadMoveHandler::LoadMoveHandler(GameState& state, const LogicAssets& assets)
    : state(state), assets(assets)
{
}

std::shared_ptr<IMove> LoadMoveHandler::handleDescription(const IMoveDescription& description)
{
    if (state.invitedPlayers.size() != 0 || state.map.size() != 0)
    {
        state.invitedPlayers.clear();
        state.map.clear();
        state.minigames.clear();
        state.playerOnMove = 0;
        state.players.clear();
        state.registredHookables.clear();
        LogicUtils::clearHookables();
        LogicUtils::resetPlayerIndexes();
    }

    const StringMoveDescription& desc = (const StringMoveDescription&)description;
    std::ifstream file;
    std::string path = desc.get();
    file.open(path, std::ios::in | std::ios::binary);
    if (!file.is_open())
        return nullptr;

    DeserializationData data(assets, minigame::MiniGame::getAssets());
    cereal::UserDataAdapter<DeserializationData, cereal::BinaryInputArchive> iarchive(data, file);

    SaveStruct str;
    iarchive(str);
    file.close();
    Patch patch = str.patch;
    patch.clearGameState = true;
    state.invitedPlayers.clear();
    state.hotSeatPlayers.clear();
    state.hotSeatPlayers.push_back(0);
    LogicUtils::resetPlayerIndexes();
    for (auto& inv : str.invitations)
    {
        inv.state = InvitationState::Pending;
        state.invitedPlayers.emplace(inv.ip, inv);
        Network::WebModule::Invite(inv.ip, state.name);
    }
    for (int i = 0; i < str.hotseatCount - 1; i++)
        state.hotSeatPlayers.push_back(LogicUtils::getAvailablePlayerId());
    
    return std::make_shared<Load>(patch);
}

bool LoadMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "load";
}
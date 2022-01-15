#include "AcceptInvitationMoveHandler.h"
#include "../MoveDescriptions/StringMoveDescription.h"
#include "../../../Network/WebModule.h"

std::shared_ptr<IMove> AcceptInvitationMoveHandler::handleDescription(const IMoveDescription& description)
{

    const auto& desc = (const StringMoveDescription&)description;
    Network::WebModule::AcceptInvitation(desc.get());
    return nullptr;
}

bool AcceptInvitationMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "accept_invitation";
}

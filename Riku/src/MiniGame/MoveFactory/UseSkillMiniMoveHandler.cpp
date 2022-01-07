#include "UseSkillMiniMoveHandler.h"
#include "../StateUpdate/Move/UseSkill.h"
#include "../StateUpdate/MoveDescription/UseSkillMoveDescription.h"

std::shared_ptr<minigame::IMiniMove> minigame::UseSkillMiniMoveHandler::handleDescription(const IMoveDescription& description)
{
    const UseSkillMoveDescription& desc = (const UseSkillMoveDescription&)description;
    return std::make_shared<UseSkill>(desc.getName(), desc.getMapX(), desc.getMapY());
}

bool minigame::UseSkillMiniMoveHandler::canHandle(const IMoveDescription& description) const
{
    return description.getMoveType() == "use_skill";
}

//Kacper Walasek
#pragma once
#include "../Move/IMove.h"
#include "../MoveDescriptions/IMoveDescription.h"
#include "IMoveDescriptionHandler.h"

class MoveFactory {
	std::vector<std::shared_ptr<IMoveDescriptionHandler>> handlers;
public:
	std::shared_ptr<IMove> createMove(const IMoveDescription& description) const;
	void setHandlers(std::vector<std::shared_ptr<IMoveDescriptionHandler>>&& handlers);
};
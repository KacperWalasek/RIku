#pragma once
#include <memory>
#include <string>
#include "../StateUpdate/Move/IMove.h"

class IHookable
{
public:
	virtual std::string getId() const = 0;
	// wywolane po zniszczeniu obiektu
	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) = 0;
	// wywolywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnEnd() = 0;
	// wywolywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnBegin() = 0;
	// wywolywane gdy zostanie postawiony na polu
	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) = 0;

	virtual int getOwner() const = 0;

	virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) = 0;
};


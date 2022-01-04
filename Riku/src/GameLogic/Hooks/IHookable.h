#pragma once
#include <memory>
#include "../StateUpdate/Move/IMove.h"

class IHookable
{
public:
	// wywo³ane po zniszczeniu obiektu
	// byOwner mówi czy zniszczenie zosta³o wywo³ane przez w³aœciciela budynku. Przydatne np. ¿eby zwróciæ czêœæ zasobów graczowi jeœli to on zburzy³ budynek, który wczeœniej zbudowa³
	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) = 0;
	// wywo³ywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnEnd() = 0;
	// wywo³ywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnBegin() = 0;
	// wywo³ywane gdy zostanie postawiony na polu
	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) = 0;

	virtual int getOwner() const = 0;

	virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) = 0;
};


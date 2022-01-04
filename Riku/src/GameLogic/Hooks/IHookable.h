#pragma once
#include <memory>
#include "../StateUpdate/Move/IMove.h"

class IHookable
{
public:
	// wywo�ane po zniszczeniu obiektu
	// byOwner m�wi czy zniszczenie zosta�o wywo�ane przez w�a�ciciela budynku. Przydatne np. �eby zwr�ci� cz�� zasob�w graczowi je�li to on zburzy� budynek, kt�ry wcze�niej zbudowa�
	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) = 0;
	// wywo�ywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnEnd() = 0;
	// wywo�ywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnBegin() = 0;
	// wywo�ywane gdy zostanie postawiony na polu
	virtual std::shared_ptr<IMove> onBeingPlaced(int mapX, int mapY) = 0;

	virtual int getOwner() const = 0;

	virtual bool canBeBuilt(const GameState& state, int mapX, int mapY) = 0;
};


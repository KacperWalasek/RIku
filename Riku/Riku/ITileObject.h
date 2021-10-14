// Kacper Walasek

#pragma once
#include "IAsset.h"
#include "ICostModifier.h"
#include "IMove.h"
#include <map>

class ITileObject : public IAsset, public ICostModifier
{
public:
	// wywo�ane po zniszczeniu obiektu
	// byOwner m�wi czy zniszczenie zosta�o wywo�ane przez w�a�ciciela budynku. Przydatne np. �eby zwr�ci� cz�� zasob�w graczowi je�li to on zburzy� budynek, kt�ry wcze�niej zbudowa�
	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) = 0;
	// wywo�ywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnEnd() = 0;
	// wywo�ywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnBegin() = 0;
};


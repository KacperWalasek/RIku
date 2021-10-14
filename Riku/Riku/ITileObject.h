// Kacper Walasek

#pragma once
#include "IAsset.h"
#include "ICostModifier.h"
#include "IMove.h"
#include <map>

class ITileObject : public IAsset, public ICostModifier
{
public:
	// wywo³ane po zniszczeniu obiektu
	// byOwner mówi czy zniszczenie zosta³o wywo³ane przez w³aœciciela budynku. Przydatne np. ¿eby zwróciæ czêœæ zasobów graczowi jeœli to on zburzy³ budynek, który wczeœniej zbudowa³
	virtual std::shared_ptr<IMove> onDestroy(bool byOwner) = 0;
	// wywo³ywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnEnd() = 0;
	// wywo³ywane na koniec tury
	virtual std::shared_ptr<IMove> onTurnBegin() = 0;
};


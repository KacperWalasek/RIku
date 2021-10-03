// Kacper Walasek

#pragma once
#include "Resource.h"
#include "ICostModifier.h"
#include <map>

class ITileObject : public IResource, public ICostModifier
{
public:
	// wywo³ane po zniszczeniu obiektu
	// byOwner mówi czy zniszczenie zosta³o wywo³ane przez w³aœciciela budynku. Przydatne np. ¿eby zwróciæ czêœæ zasobów graczowi jeœli to on zburzy³ budynek, który wczeœniej zbudowa³
	virtual void onDestroy(bool byOwner) = 0;
	// wywo³ywane na koniec tury
	virtual void onTurnEnd() = 0;
	// wywo³ywane na koniec tury
	virtual void onTurnBegin() = 0;
	/*
		TODO - onDestroy, onTurnEnd i onTurnBegin powinny zwracaæ akcjê, które mo¿na wywo³aæ na stanie gry. Na ten moment zwracaj¹ voida, bo akcje jeszcze nie zimplementowane
	*/
};


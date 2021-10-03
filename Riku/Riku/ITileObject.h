// Kacper Walasek

#pragma once
#include "Resource.h"
#include "ICostModifier.h"
#include <map>

class ITileObject : public IResource, public ICostModifier
{
public:
	// wywo�ane po zniszczeniu obiektu
	// byOwner m�wi czy zniszczenie zosta�o wywo�ane przez w�a�ciciela budynku. Przydatne np. �eby zwr�ci� cz�� zasob�w graczowi je�li to on zburzy� budynek, kt�ry wcze�niej zbudowa�
	virtual void onDestroy(bool byOwner) = 0;
	// wywo�ywane na koniec tury
	virtual void onTurnEnd() = 0;
	// wywo�ywane na koniec tury
	virtual void onTurnBegin() = 0;
	/*
		TODO - onDestroy, onTurnEnd i onTurnBegin powinny zwraca� akcj�, kt�re mo�na wywo�a� na stanie gry. Na ten moment zwracaj� voida, bo akcje jeszcze nie zimplementowane
	*/
};


//Kacper Walasek
#include "StateUpdate.h"

StateUpdate::StateUpdate(GameState& state) : state(state) {}

void StateUpdate::handleMoveRequest(const IMove& move)
{
	if (move.isDoable(state))
		move.apply(state);
		//TODO - updatowaæ liczbê punktów ruchu na podstawie wartoœci zwróconej przez apply, kiedy ju¿ bêd¹ zaimplementowane
}

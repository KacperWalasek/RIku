//Kacper Walasek
#include "StateUpdate.h"

StateUpdate::StateUpdate(GameState& state) : state(state) {}

void StateUpdate::handleMoveRequest(const IMove& move)
{
	if (move.isDoable(state))
		move.apply(state);
		//TODO - updatowa� liczb� punkt�w ruchu na podstawie warto�ci zwr�conej przez apply, kiedy ju� b�d� zaimplementowane
}

#pragma once

class GameState;
class LogicAssets;
class StateUpdate;
class Communicator;
class MoveFactory;

/// <summary>
/// Takes some action on GameLogic. It is returned by PatchHandlers for GameLogic to decide if action should be taken or not. 
/// If given Patch was recived from other player action isn't taken. Otherwise it is taken. 
/// </summary>
class IAction
{
public:
	virtual void takeAction(
		GameState& gameState,
		LogicAssets& assets,
		StateUpdate& stateUpdate,
		Communicator& communicator,
		MoveFactory& factory) = 0;
};


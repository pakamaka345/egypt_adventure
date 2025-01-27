//
// Created by pakamaka345 on 1/27/25.
//

#include "InteractCommand.hpp"

#include <states/GameState.hpp>

void InteractCommand::execute(GameState& gameState)
{
	gameState.handleInteraction();
}

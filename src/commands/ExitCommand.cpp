//
// Created by pakamaka345 on 1/19/25.
//

#include "ExitCommand.hpp"

#include <states/GameState.hpp>

void ExitCommand::execute(GameState& gameState)
{
	if (gameState.getIsGameOver() == false) {
		gameState.setIsGameOver(true);
	}
}

//
// Created by pakamaka345 on 1/28/25.
//

#include "AmuletsMenuCommand.hpp"

#include <states/GameState.hpp>

void AmuletsMenuCommand::execute(GameState& gameState)
{
	gameState.setIsActiveAmuletsMenuOpen(true);
}

//
// Created by pakamaka345 on 1/27/25.
//

#include "InventoryCommand.hpp"

#include <states/GameState.hpp>

void InventoryCommand::execute(GameState& gameState)
{
	gameState.setIsInventoryOpen(true);
}

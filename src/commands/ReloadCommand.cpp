//
// Created by pakamaka345 on 1/23/25.
//

#include "ReloadCommand.hpp"

#include <entities/Character.hpp>
#include <states/GameState.hpp>

void ReloadCommand::execute(GameState& gameState)
{
	const auto& player = gameState.getPlayer();
	if (player) {
		player->reloadRevolver();
	}
}

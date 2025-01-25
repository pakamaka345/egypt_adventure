//
// Created by pakamaka345 on 1/19/25.
//

#include "GameController.hpp"

#include <commands/Command.hpp>
#include <entities/Character.hpp>
#include <states/GameState.hpp>
#include <items/Bullet.hpp>

GameController::GameController(GameState& gameState)
	: gameState(gameState)
{
	const auto character = std::make_shared<Character>("Peter Miller", 0, 0, 1, '@');
	for (int i = 0; i < 20; i++) {
		character->addToInventory(std::make_shared<Bullet>(50, 50, 1));
	}
	gameState.initializePlayer(character);
	character->reloadRevolver();
	gameState.nextLevel(1);
}

void GameController::executeCommand(const std::shared_ptr<Command>& command) const
{
	if (command) {
		command->execute(gameState);
	}
}

void GameController::update() const
{
	gameState.update();
}

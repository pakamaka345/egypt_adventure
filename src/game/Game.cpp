//
// Created by pakamaka345 on 1/19/25.
//

#include "Game.hpp"

#include <states/GameState.hpp>

#include "GameController.hpp"
#include "InputHandler.hpp"
#include "map/Map.hpp"
#include "tiles/Tile.hpp"
#include "entities/Entity.hpp"
#include "items/Item.hpp"
#include <iostream>
#include <entities/Character.hpp>
#include <weapons/Weapon.hpp>

#include "GameView.hpp"
#include "utils/EventManager.hpp"

void Game::run()
{
	auto& gameState = GameState::getInstance();
	GameController gameController(gameState);
	InputHandler inputHandler(gameState);
	GameView gameView(60, 30);

	while (true) {
		// TODO не забути зробити всі runtime_error як EventManager
		try {
			gameView.render(gameState);

			if (gameState.getIsGameOver()) {
				break;
			}

			EventManager::getInstance().clearEvents();

			auto command = inputHandler.handleInput();
			gameController.executeCommand(command);
			gameController.update();
		} catch (const std::exception& e) {
			std::cerr << e.what() << std::endl;
		}
	}
}

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

void Game::run()
{
	auto& gameState = GameState::getInstance();
	GameController gameController(gameState);
	InputHandler inputHandler(gameState);

	while (!gameState.getIsGameOver()) {

		// TODO create GameView
		auto map = gameState.getCurrentLevel().getMap();
		system("clear");
		for (int y = gameState.getPlayer()->getY() - 20; y <= gameState.getPlayer()->getY() + 20; ++y) {
			for (int x = gameState.getPlayer()->getX() - 50; x <= gameState.getPlayer()->getX() + 50; ++x) {
				if (x >= 0 && x < map->getWidth() && y >= 0 && y < map->getHeight()) {
					auto tile = map->getTile(x, y);
					if (tile->hasEntity()) {
						std::cout << tile->getEntity()->getSymbol();
						continue;
					}
					if (tile->hasItems()) {
						std::cout << tile->getItem()->getSymbol();
						continue;
					}

					std::cout << tile->getSymbol();
				}
			}
			std::cout << std::endl;
		}
		std::cout << "\e[0;32m " << gameState.getPlayer()->getHealth() << " HP\e[0m" << std::endl;
		std::cout << "\e[0;32m " << gameState.getPlayer()->getCooldown() << " Cooldown\e[0m" << std::endl;

		auto command = inputHandler.handleInput();
		gameController.executeCommand(command);
		gameController.update();
	}
}

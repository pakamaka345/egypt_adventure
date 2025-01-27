#include "GameView.hpp"

#include <entities/Character.hpp>
#include <map/Map.hpp>
#include <states/GameState.hpp>
#include <iomanip>
#include <tiles/Tile.hpp>
#include <weapons/Weapon.hpp>
#include <iostream>

#include "utils/EventManager.hpp"

GameView::GameView(int width, int height)
	: viewportWidth(width), viewportHeight(height)
{
}



void GameView::render(GameState& gameState)
{
	auto map = gameState.getCurrentLevel().getMap();
	auto player = gameState.getPlayer();

	int startX = std::max(0, player->getX() - viewportWidth / 2);
	int endX = std::min(map->getWidth(), player->getX() + viewportWidth / 2);
	int startY = std::max(0, player->getY() - viewportHeight / 2);
	int endY = std::min(map->getHeight(), player->getY() + viewportHeight / 2);

#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

	for (int y = startY; y < endY; ++y) {
		std::ostringstream row;
		for (int x = startX; x < endX; ++x) {
			auto tile = map->getTile(x, y);

			if (map->getDynamicLight(x, y) != LightType::NONE) {
				row << "\e[0;36m";
			} else if (map->getStaticLight(x, y) != LightType::NONE) {
				row << "\e[0;37m";
			} else if (map->isSeen(x, y)) {
				row << "\e[0;90m";
			} else {
				row << "\e[0;100m";
			}

			if (!map->isSeen(x, y) && map->getStaticLight(x, y) == LightType::NONE) {
				row << " ";
			} else if (map->isSeen(x, y) && map->getDynamicLight(x, y) == LightType::NONE && map->getStaticLight(x, y) == LightType::NONE) {
				row << tile->getSymbol();
			} else if (tile->hasEntity()) {
				row << tile->getEntity()->getSymbol();
			} else if (tile->hasItems()) {
				row << tile->getItem()->getSymbol();
			} else {
				row << tile->getSymbol();
			}

			row << "\e[0m";
		}

		appendPlayerStatsRow(row, y, startY, player);

		std::cout << row.str() << std::endl;
	}

	std::cout << "------------Combat Logs: ------------" << std::endl;
	std::cout << EventManager::getInstance().formatCombatEvents();

	if (gameState.getIsGameOver()) {
		std::cout << "Game Over!" << std::endl;
	}
}

void GameView::appendPlayerStatsRow(std::ostringstream& row, int y, int startY, const std::shared_ptr<Character>& player)
{
	if (y == startY) {
		row << std::setw(10) << "\e[0;32m Hero Stats: \e[0m";
	} else if (y == startY + 1) {
		row << std::setw(10) << "\e[0;32m HP: " << player->getHealth() << "/" << player->getMaxHealth() << "\e[0m";
	} else if (y == startY + 2) {
		row << std::setw(10) << "\e[0;33m Physical damage: " << player->getPhysicalDamage() << " - Magical damage: " << player->getMagicalDamage() << "\e[0m";
	} else if (y == startY + 3) {
		row << std::setw(10) << "\e[0;34m AttackRange: " << player->getAttackRange() << "\e[0m";
	} else if (y == startY + 4) {
		row << std::setw(10) << "\e[0;35m Ammo: " << player->getRevolver()->getAmmo() << " / " << player->getInventory().getItemCount("bullet") << "\e[0m";
	} else if (y == startY + 5) {
		row << std::setw(10) << "\e[0;36m Visibility range: " << player->getVisibilityRange() << "\e[0m";
	} else if (y == startY + 6) {
		row << std::setw(10) << "\e[0;37m effects: " << player->getEffectManager().formatActiveEffects() << "\e[0m";
	} else if (y == startY + 7) {
		if (player->getCooldown() > 0) {
			row << std::setw(10) << " Status: On Cooldown (" << player->getCooldown() << " turns left)";
		} else {
			row << std::setw(10) << " Status: Ready to attack";
		}
	} else if (y == startY + 8) {
		if (player->getActiveTorch()) {
			row << std::setw(10) << " Torch: " << player->getActiveTorch()->getDuration() << " turns left";
		}
	} else if (y == startY + 9) {
		row << std::setw(10) << " Items in Inventory: " << player->getInventory().getItemsCount()  << " press 'i' to open inventory";
	} else if (y == startY + 10) {
		row << std::setw(10) << " " + EventManager::getInstance().formatInteractEvents();
	} else if (y == startY + 11) {
		row << std::setw(10) << " System Events: ";
	} else if (y == startY + 12) {
		row << std::setw(10) << " " + EventManager::getInstance().formatSystemEvents();
	}
}


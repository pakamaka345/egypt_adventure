#include "GameView.hpp"

#include <entities/Character.hpp>
#include <map/Map.hpp>
#include <states/GameState.hpp>
#include <iomanip>
#include <tiles/Tile.hpp>
#include <weapons/Weapon.hpp>
#include <iostream>
#include <items/ThrowableItem.hpp>
#include "utils/EventManager.hpp"
#include <unistd.h>
#include <items/amulets/Amulet.hpp>

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

void GameView::renderInventory(GameState& gameState) const
{
	auto player = gameState.getPlayer();
	const auto& inventory = player->getInventory();

#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

	const std::string CYAN = "\033[36m";
	const std::string RESET = "\033[0m";

	std::cout << CYAN << "+---------------------------------------------------------------------------+" << RESET << std::endl;
	std::cout << CYAN << "|██╗███╗   ██╗██╗   ██╗███████╗███╗   ██╗████████╗ ██████╗ ██████╗ ██╗   ██╗|" << RESET << std::endl;
	std::cout << CYAN << "|██║████╗  ██║██║   ██║██╔════╝████╗  ██║╚══██╔══╝██╔═══██╗██╔══██╗╚██╗ ██╔╝|" << RESET << std::endl;
	std::cout << CYAN << "|██║██╔██╗ ██║██║   ██║█████╗  ██╔██╗ ██║   ██║   ██║   ██║██████╔╝ ╚████╔╝ |" << RESET << std::endl;
	std::cout << CYAN << "|██║██║╚██╗██║╚██╗ ██╔╝██╔══╝  ██║╚██╗██║   ██║   ██║   ██║██╔══██╗  ╚██╔╝  |" << RESET << std::endl;
	std::cout << CYAN << "|██║██║ ╚████║ ╚████╔╝ ███████╗██║ ╚████║   ██║   ╚██████╔╝██║  ██║   ██║   |" << RESET << std::endl;
	std::cout << CYAN << "|╚═╝╚═╝  ╚═══╝  ╚═══╝  ╚══════╝╚═╝  ╚═══╝   ╚═╝    ╚═════╝ ╚═╝  ╚═╝   ╚═╝   |" << RESET << std::endl;
	std::cout << CYAN << "+---------------------------------------------------------------------------+" << RESET << std::endl;

	int index = 0;
	for (const auto& [name, itemData] : inventory.getItems()) {
		std::cout << CYAN << "█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗" << RESET << std::endl;
		std::cout << CYAN   << "╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝" << RESET << std::endl;
		std::cout << "[" << index++ << "] " << name << " (x" << itemData.count << ")" << std::endl;
		std::cout << "Description: " << itemData.item->getDescription() << std::endl;
		std::cout << "Specifics: \n" << itemData.item->getSpecifications() << std::endl;
	}

	std::cout << "Choose an item by entering its name, or press 'q' to exit inventory" << std::endl;

	std::string input;
	getline(std::cin, input);
	if (input == "q") { gameState.setIsInventoryOpen(false); return; }

	auto item = inventory.getItem(input);
	if (!item.has_value()) {
		std::cout << "There are no items with name " << input << std::endl;
		sleep(3);
		return;
	}

	if (auto throwable = std::dynamic_pointer_cast<ThrowableItem>(item.value())) {
		handleThrowableItem(gameState, throwable);
	} else {
		player->getInventory().useItem(item.value()->getName(), player);
	}
}

void GameView::renderAmuletMenu(GameState& gameState) const
{
	auto player = gameState.getPlayer();
	const auto& activeAmulets = player->getActiveAmulets();

#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif

	int index = 0;
	const std::string CYAN = "\033[36m";
	const std::string RESET = "\033[0m";

	if (activeAmulets.empty()) {
		std::cout << "No active amulets" << std::endl;
	}

	for (const auto& amulet : activeAmulets) {
		std::cout << CYAN << "█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗█████╗" << RESET << std::endl;
		std::cout << CYAN   << "╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝╚════╝" << RESET << std::endl;
		std::cout << "[" << index++ << "] " << amulet->getName() << std::endl;
		std::cout << "Description: " << amulet->getDescription() << std::endl;
		std::cout << "Specifics: \n" << amulet->getSpecifications() << std::endl;
	}

	std::cout << "Choose an amulet by entering its index to deactivate it, or press 'q' to exit amulet menu" << std::endl;

	std::string input;
	getline(std::cin, input);
	if (input == "q") { gameState.setIsActiveAmuletsMenuOpen(false); return; }

	if (std::stoi(input) >= activeAmulets.size() || std::stoi(input) < 0) {
		std::cout << "Invalid amulet index" << std::endl;
		sleep(3);
		return;
	}

	auto& amulet = player->getActiveAmulets()[std::stoi(input)];
	player->removeAmulet(amulet);

	player->addToInventory(amulet);
}


void GameView::handleThrowableItem(GameState& gameState, std::shared_ptr<ThrowableItem> item) const
{
	auto map = gameState.getCurrentLevel().getMap();
	auto player = gameState.getPlayer();

	std::cout << "Select a target to throw the item. Entities in range:" << std::endl;
	int index = 0;
	std::vector<std::shared_ptr<Entity>> entitiesInRange;

	for (auto& entity : gameState.getCurrentLevel().getEntities()) {
		if (player->distanceTo(*entity) <= item->getRadius() && entity != player) {
			std::cout << "[" << index++ << "] " << entity->getName() << " (x" << entity->getX() << ", y" << entity->getY() << ")" << std::endl;
			entitiesInRange.push_back(entity);
		}
	}

	if (entitiesInRange.empty()) {
		std::cout << "No entities in range to throw the " + item->getName() << std::endl;
		sleep(3);
		return;
	}

	std::cout << "Choose a target by entering its index or -1 to cancel" << std::endl;

	int targetIndex = 0;
	std::cin >> targetIndex;

	if (targetIndex == -1) {
		return;
	}

	if (targetIndex >= 0 && targetIndex < entitiesInRange.size()) {
		const auto& target = entitiesInRange[targetIndex];
		player->getInventory().useItem(item->getName(), target);
	} else {
		std::cout << "Invalid target index" << std::endl;
		sleep(3);
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


//
// Created by pakamaka345 on 1/25/25.
//

#include "SandGolemAIComponent.hpp"

#include <map/Map.hpp>
#include "tiles/Tile.hpp"
#include "commands/ActivateSandShieldCommand.hpp"
#include "commands/CoverWithSandCommand.hpp"
#include "commands/MoveCommand.hpp"
#include "entities/SandGolem.hpp"
#include "entities/Character.hpp"
#include "states/GameState.hpp"
#include "dice/DiceRoll.hpp"

std::shared_ptr<SandGolem> SandGolemAIComponent::getGolem() const
{
	return std::dynamic_pointer_cast<SandGolem>(getOwner());
}

std::shared_ptr<Command> SandGolemAIComponent::makeDecision(GameState& gameState)
{
	DiceRoll gen;

	const auto& monster = getGolem();
	const auto& player = gameState.getPlayer();


	if (monster->isOnSameLevel(player)) {
		if (monster->getHealth() / monster->getMaxHealth() < 0.5 && isShieldActivated == false) {
			if (gen.randomNumber(1, 10) > 5 && monster->getShieldMaxHealth() == 0) {
				isShieldActivated = true;
				return std::make_shared<ActivateSandShieldCommand>(monster);
			}
		}

		if (monster->getShieldHealth() / monster->getShieldMaxHealth() < 0.7 && isSpecialActionActivated == false) {
			isSpecialActionActivated = true;
			return std::make_shared<CoverWithSandCommand>(monster);
		}
	}

	return AIComponent::makeDecision(gameState);
}

std::shared_ptr<Command> SandGolemAIComponent::movement(const std::shared_ptr<Entity>& monster, const Position& playerPosition, const std::shared_ptr<Map>& map, DiceRoll gen)
{
	auto tiles = getTilesWithSand(map);
	const auto& golem = std::dynamic_pointer_cast<SandGolem>(monster);
	if (!tiles.empty() && golem->getShieldHealth() / golem->getShieldMaxHealth() < 0.3 && isShieldActivated) {
		auto path = findPath(monster, tiles[gen.randomNumber(0, tiles.size() - 1)], map);
		if (path != Direction::NONE) {
			return std::make_shared<MoveCommand>(path, monster);
		}
	}

	return AIComponent::movement(monster, playerPosition, map, gen);
}

std::vector<Position> SandGolemAIComponent::getTilesWithSand(const std::shared_ptr<Map>& map) const
{
	std::vector<Position> tiles;
	for (int dx = getGolem()->getX() - 10; dx <= getGolem()->getX() + 10; dx++) {
		for (int dy = getGolem()->getY() - 10; dy <= getGolem()->getY() + 10; dy++) {
			if (map->isInsideMap(dx, dy) && map->getTile(dx, dy)->getTileType() == TileType::SAND) {
				tiles.emplace_back(dx, dy);
			}
		}
	}

	return tiles;
}




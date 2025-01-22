//
// Created by pakamaka345 on 1/6/25.
//

#pragma once
#include "MapDecorator.hpp"
#include "config/Config.hpp"
#include <map/RoomGenerator.hpp>
#include <ai/AIComponent.hpp>
#include <string>
#include <memory>

class Entity;
class LevelState;

class EnemyDecorator : public MapDecorator {
	int enemyCount;
	int mapSection;
	std::string enemyName;
	std::shared_ptr<LevelState> levelState;
	std::shared_ptr<Config> config;
	std::map<std::string, std::function<std::shared_ptr<Entity>(Position)>> enemyCreationMap;

	std::shared_ptr<Entity> createEnemy(const std::string& enemyName, Position pos);
	void placeEnemy(Map& map, const std::shared_ptr<RoomGenerator::Room>& room);
	Position generateEnemyPosition(const std::shared_ptr<RoomGenerator::Room>& room);

	template<typename T>
	std::shared_ptr<Entity> createSpecificEnemy(Position pos)
	{
		auto enemy = config->createEntity<T>(enemyName)->clone();
		enemy->setPos(pos);
		auto specificEnemy = std::dynamic_pointer_cast<T>(enemy);
		if (specificEnemy) {
			auto ai = specificEnemy->getAIComponent();
			if (ai) {
				ai->setOwner(specificEnemy);
			}
		}
		return enemy;
	}

public:
	EnemyDecorator(int enemyCount, int mapSection, std::string enemyName, std::shared_ptr<LevelState> levelState, int levelIndex);

	void decorate(Map& map) override;
};

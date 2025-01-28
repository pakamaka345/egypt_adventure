//
// Created by pakamaka345 on 1/6/25.
//

#include "EnemyDecorator.hpp"
#include <utility>
#include <iostream>
#include <entities/Scarab.hpp>
#include <entities/Skeleton.hpp>
#include <entities/Mummy.hpp>
#include <entities/Phantom.hpp>
#include <entities/SandGolem.hpp>
#include <map/Map.hpp>
#include <states/LevelState.hpp>


EnemyDecorator::EnemyDecorator(int enemyCount, int mapSection, std::string enemyName, std::shared_ptr<LevelState> levelState, int levelIndex)
		: MapDecorator(levelIndex), enemyCount(enemyCount), mapSection(mapSection), enemyName(std::move(enemyName)), levelState(std::move(levelState))
{
	config = Config::getInstance("../assets/configs/config.json");

	enemyCreationMap = {
		{"Scarab", [this](Position pos) { return createSpecificEnemy<Scarab>(pos); }},
		{"Scarab2", [this](Position pos) { return createSpecificEnemy<Scarab>(pos); }},
		{"Skeleton", [this](Position pos) { return createSpecificEnemy<Skeleton>(pos); }},
		{"Skeleton2", [this](Position pos) { return createSpecificEnemy<Skeleton>(pos); }},
		{"Mummy", [this](Position pos) { return createSpecificEnemy<Mummy>(pos); }},
		{"Phantom", [this](Position pos) { return createSpecificEnemy<Phantom>(pos); }},
		{"Phantom2", [this](Position pos) { return createSpecificEnemy<Phantom>(pos); }},
		{"SandGolem", [this](Position pos) { return createSpecificEnemy<SandGolem>(pos); }}
	};
}

void EnemyDecorator::decorate(Map& map)
{
	auto rooms = map.getRooms();

	int roomsPerSection = rooms.size() / 3;
	int startRoomIndex = 0;
	int endRoomIndex = roomsPerSection;

	switch (mapSection) {
	case 0:
		startRoomIndex = 1;
		endRoomIndex = roomsPerSection;
		break;
	case 1:
		startRoomIndex = roomsPerSection;
		endRoomIndex = 2 * roomsPerSection;
		break;
	case 2:
		startRoomIndex = 2 * roomsPerSection;
		endRoomIndex = rooms.size();
		break;
	default:
		break;
	}

	int totalRoomsInSection = endRoomIndex - startRoomIndex;
	int monstersPerRoom = enemyCount / totalRoomsInSection;
	int remainderMonsters = enemyCount % totalRoomsInSection;

	std::vector<int> roomIndices(totalRoomsInSection);
	std::iota(roomIndices.begin(), roomIndices.end(), startRoomIndex);
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(roomIndices.begin(), roomIndices.end(), gen);

	int placedMonsters = 0;

	for (int i = 0; i < totalRoomsInSection && placedMonsters < enemyCount; ++i) {
		auto& room = rooms[roomIndices[i]];

		int monstersInRoom = monstersPerRoom;
		if (i - startRoomIndex < remainderMonsters) {
			monstersInRoom++;
		}

		for (int j = 0; j < monstersInRoom && placedMonsters < enemyCount; ++j) {
			placeEnemy(map, room);
			placedMonsters++;
		}
	}
}


void EnemyDecorator::placeEnemy(Map& map, const std::shared_ptr<RoomGenerator::Room>& room)
{
	auto pos = map.getRandomFreePosition(room->getCenter().x, room->getCenter().y, 5);

	if (pos != Position(-1, -1)) {
		pos.z = levelIndex;
		auto enemy = createEnemy(enemyName, pos);
		map.placeEntity(pos.x, pos.y, enemy);
		levelState->addEntity(enemy);
	}
}

std::shared_ptr<Entity> EnemyDecorator::createEnemy(const std::string& enemyName, Position pos)
{
	try {
		auto it = enemyCreationMap.find(enemyName);
		if (it != enemyCreationMap.end()) {
			return it->second(pos);
		} else {
			throw std::runtime_error("Invalid enemy name");
		}
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
		return nullptr;
	}
}



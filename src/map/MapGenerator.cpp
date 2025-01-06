//
// Created by pakamaka345 on 12/26/24.
//

#include "MapGenerator.hpp"
#include "decorators/CompositeMapDecorator.hpp"
#include "decorators/BSPTreeDecorator.hpp"
#include "decorators/RoomDecorator.hpp"
#include "decorators/CorridorDecorator.hpp"
#include "decorators/StairsDecorator.hpp"
#include "Map.hpp"
#include "decorators/EnemyDecorator.hpp"
#include "decorators/TorchDecorator.hpp"
#include "states/LevelState.hpp"

std::shared_ptr<LevelState> MapGenerator::GenerateMap(int levelIndex, int width, int height, const int MinLeafSize, const int MaxLeafSize, const int MinRoomSize)
{
	Map map(width, height);
	CompositeMapDecorator mapGenerator;

	mapGenerator.addDecorator(std::make_unique<BSPTreeDecorator>(MinLeafSize, MaxLeafSize));
	mapGenerator.addDecorator(std::make_unique<RoomDecorator>(MinRoomSize));
	mapGenerator.addDecorator(std::make_unique<CorridorDecorator>());
	mapGenerator.addDecorator(std::make_unique<StairsDecorator>(levelIndex));
	mapGenerator.addDecorator(std::make_unique<TorchDecorator>());

	mapGenerator.decorate(map);

	auto levelState = std::make_shared<LevelState>(map);

	// Map Section could be only 0, 1, 2
	mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(3, 2, "Scarab", levelState));
	mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(3, 0, "Skeleton", levelState));
	mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(3, 1, "Mummy", levelState));

	mapGenerator.decorate(map);

	return levelState;
}

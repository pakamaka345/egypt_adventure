//
// Created by pakamaka345 on 12/26/24.
//

#include "MapGenerator.hpp"
#include "Map.hpp"
#include "decorators/CompositeMapDecorator.hpp"
#include "decorators/BSPTreeDecorator.hpp"
#include "decorators/RoomDecorator.hpp"
#include "decorators/CorridorDecorator.hpp"
#include "decorators/StairsDecorator.hpp"
#include "decorators/EnemyDecorator.hpp"
#include "decorators/TorchDecorator.hpp"
#include "decorators/ItemDecorator.hpp"
#include "states/LevelState.hpp"
#include "items/Bullet.hpp"
#include "items/Torch.hpp"

std::shared_ptr<LevelState> MapGenerator::GenerateMap(int levelIndex, int width, int height, const int MinLeafSize, const int MaxLeafSize, const int MinRoomSize)
{
	Map map(width, height, levelIndex);
	CompositeMapDecorator mapGenerator(levelIndex);

	mapGenerator.addDecorator(std::make_unique<BSPTreeDecorator>(MinLeafSize, MaxLeafSize, levelIndex));
	mapGenerator.addDecorator(std::make_unique<RoomDecorator>(MinRoomSize, levelIndex));
	mapGenerator.addDecorator(std::make_unique<CorridorDecorator>(levelIndex));
	mapGenerator.addDecorator(std::make_unique<StairsDecorator>(levelIndex));
	mapGenerator.addDecorator(std::make_unique<TorchDecorator>(levelIndex));

	mapGenerator.decorate(map);

	auto levelState = std::make_shared<LevelState>(std::make_shared<Map>(map));

	// Map Section could be only 0, 1, 2
	//mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(10, 0, "SandGolem", levelState, levelIndex));
	//mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(15, 1, "Scarab", levelState, levelIndex));
	//mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(7, 1, "Phantom", levelState, levelIndex));
	//mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(15, 0, "Skeleton", levelState, levelIndex));
	//mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(7, 0, "Mummy", levelState, levelIndex));
	//mapGenerator.addDecorator(std::make_unique<ItemDecorator>(3, false, std::make_shared<Bullet>(30, 15, levelIndex), levelState, levelIndex));
	//mapGenerator.addDecorator(std::make_unique<ItemDecorator>(1, false, std::make_shared<Torch>(20, 12, levelIndex), levelState, levelIndex));

	mapGenerator.decorate(map);
	return levelState;
}

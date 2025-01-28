//
// Created by pakamaka345 on 12/26/24.
//

#include "MapGenerator.hpp"

#include <items/HealPotion.hpp>
#include <items/amulets/ArmorAmulets.hpp>
#include <items/amulets/DamageAmulet.hpp>
#include <items/amulets/HealthAmulet.hpp>

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
#include "items/Grenade.hpp"

std::shared_ptr<LevelState> MapGenerator::GenerateMap(int levelIndex, int width, int height, const int MinLeafSize, const int MaxLeafSize, const int MinRoomSize) {
    Map map(width, height, levelIndex);
    CompositeMapDecorator mapGenerator(levelIndex);

    mapGenerator.addDecorator(std::make_unique<BSPTreeDecorator>(MinLeafSize, MaxLeafSize, levelIndex));
    mapGenerator.addDecorator(std::make_unique<RoomDecorator>(MinRoomSize, levelIndex));
    mapGenerator.addDecorator(std::make_unique<CorridorDecorator>(levelIndex));
    mapGenerator.addDecorator(std::make_unique<StairsDecorator>(levelIndex));
    mapGenerator.addDecorator(std::make_unique<TorchDecorator>(levelIndex));

    mapGenerator.decorate(map);

    auto levelState = std::make_shared<LevelState>(std::make_shared<Map>(map));

    if (levelIndex == 1) {
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(8, 0, "Scarab", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(5, 1, "Skeleton", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(2, 2, "Skeleton2", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<ItemDecorator>(3, false, std::make_shared<HealthAmulet>(10, levelIndex), levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<ItemDecorator>(2, false, std::make_shared<Bullet>(20, 10, levelIndex), levelState, levelIndex));
    } else if (levelIndex == 2) {
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(10, 0, "Scarab2", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(7, 1, "Skeleton2", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(5, 1, "Mummy", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<ItemDecorator>(3, false, std::make_shared<DamageAmulet>(10, 5, levelIndex), levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<ItemDecorator>(2, false, std::make_shared<Grenade>(20, 20, 5, levelIndex), levelState, levelIndex));
    } else if (levelIndex == 3) {
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(10, 0, "Phantom", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(8, 1, "SandGolem", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<EnemyDecorator>(5, 2, "Phantom2", levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<ItemDecorator>(3, false, std::make_shared<ArmorAmulets>(0.3, 0.2, levelIndex), levelState, levelIndex));
        mapGenerator.addDecorator(std::make_unique<ItemDecorator>(1, true, std::make_shared<Torch>(30, 20, levelIndex), levelState, levelIndex));
    }

    mapGenerator.decorate(map);
    return levelState;
}

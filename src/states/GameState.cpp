#include "states/GameState.hpp"
#include <utility>
#include <tiles/InteractTile.hpp>

#include "map/Map.hpp"
#include "entities/Character.hpp"
#include "map/MapGenerator.hpp"
#include "states/LevelState.hpp"



GameState::GameState() : player(nullptr), levelIndex(1), isGameOver(false)
{
    for (int i = 1; i <= MAX_LEVELS; ++i) {
        levels[i] = nullptr;
    }
}

GameState &GameState::getInstance() {
    static GameState instance;
    return instance;
}

void GameState::initializePlayer(std::shared_ptr<Character> newPlayer) {
    player = std::move(newPlayer);
}

void GameState::setLevel(std::shared_ptr<LevelState> level) {
    currentLevel = std::move(level);
    levels[levelIndex] = currentLevel;
}

LevelState &GameState::getCurrentLevel() {
    if (!currentLevel) {
        throw std::runtime_error("Level is not set");
    }

    return *currentLevel;
}

std::shared_ptr<Character> GameState::getPlayer() {
    if (!player) {
        throw std::runtime_error("Player is not set");
    }

    return player;
}

void GameState::nextLevel(const int newLevelIndex) {
    if (levels[newLevelIndex] == nullptr) {
        levels[newLevelIndex] = createLevel(newLevelIndex);
    }

    currentLevel = levels[newLevelIndex];
    levelIndex = newLevelIndex;
    if (player) {
        player->setPos(currentLevel->getStartPosition());
        currentLevel->addEntity(player);
        currentLevel->getMap()->placeEntity(player->getX(), player->getY(), player);
    }
}

void GameState::previousLevel(const int newLevelIndex)
{
    if (levels[newLevelIndex] == nullptr) {
        throw std::runtime_error("Invalid level index for previous level");
    }
    currentLevel = levels[newLevelIndex];
    levelIndex = newLevelIndex;
    player->setPos(currentLevel->getStartPosition());
}


void GameState::update() const {
    if (currentLevel) {
        currentLevel->update(getInstance());
    }

    if (player) {
        //player->update(getInstance());

        const auto adjacent = currentLevel->getMap()->getAdjacentTiles(player->getX(), player->getY());
        onCollisionWithTile(adjacent);
        onCollisionWithItem(adjacent);
    }
}

void GameState::setLevelIndex(int newLevelIndex) {
    levelIndex = newLevelIndex;
}

int GameState::getLevelIndex() const {
    return levelIndex;
}

std::shared_ptr<LevelState> GameState::createLevel(const int levelIndex)
{
    std::shared_ptr<LevelState> level;
    if (levelIndex == 1) {
        level = MapGenerator::GenerateMap(levelIndex, 200, 200, 20, 25, 10);
    } else if (levelIndex == 2) {
        level = MapGenerator::GenerateMap(levelIndex, 150, 150, 25, 35, 20);
    } else if (levelIndex == 3) {
        level = MapGenerator::GenerateMap(levelIndex, 100, 100, 20, 30, 15);
    } else {
        throw std::runtime_error("Invalid level index");
    }

    auto startPos = level->getMap()->getPositionNearStair();
    if (startPos != Position{-1, -1}) {
        startPos.z = levelIndex;
        level->setStartPosition(startPos);
    }
    return level;
}

void GameState::onCollisionWithTile(const std::vector<std::shared_ptr<Tile>>& adjacent) const
{
    for (auto& tile : adjacent) {
        if (auto interactTile = std::dynamic_pointer_cast<InteractTile>(tile)) {
            //TODO add EventManager.
        }
    }
}

void GameState::onCollisionWithItem(const std::vector<std::shared_ptr<Tile>>& adjacent) const
{
    for (auto& tile : adjacent) {
        if (tile->hasItems()) {
            //TODO add EventManager.
        }
    }
}



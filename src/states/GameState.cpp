#include "states/GameState.hpp"
#include <utility>
#include "map/Map.hpp"
#include "entities/Character.hpp"
#include "states/LevelState.hpp"



GameState::GameState() : player(nullptr), levelIndex(1)
{}

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

Character &GameState::getPlayer() {
    if (!player) {
        throw std::runtime_error("Player is not set");
    }

    return *player;
}

void GameState::nextLevel(const Position &startPos) {
    levelIndex++;
    if (levels[levelIndex] == nullptr) {
        // Create new level with Map Generator
    }
    levels[levelIndex]->setStartPosition(startPos);
    currentLevel = levels[levelIndex];
}

void GameState::previousLevel(const Position& startPos)
{
    levelIndex--;
    if (levels[levelIndex] == nullptr) {
        throw std::runtime_error("level does not exist");
    }
    levels[levelIndex]->setStartPosition(startPos);
    currentLevel = levels[levelIndex];
}


void GameState::update() {
    if (currentLevel) {
        currentLevel->update();
    }

    if (player) {
        player->update();
    }
}

void GameState::setLevelIndex(int newLevelIndex) {
    levelIndex = newLevelIndex;
}

int GameState::getLevelIndex() const {
    return levelIndex;
}
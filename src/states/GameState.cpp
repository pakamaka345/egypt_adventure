#include "states/GameState.hpp"
#include <utility>
#include "Map.hpp"
#include "entities/Character.hpp"



GameState::GameState() : player(nullptr), levelNumber(1)
{}

GameState &GameState::getInstance() {
    static GameState instance;
    return instance;
}

void GameState::initializePlayer(std::shared_ptr<Character> newPlayer) {
    player = std::move(newPlayer);
}

void GameState::setLevel(std::unique_ptr<LevelState> level) {
    currentLevel = std::move(level);
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

void GameState::nextLevel(const Map& newMap, const LevelState::Position &startPos) {
    currentLevel = std::make_unique<LevelState>(newMap, startPos);
}

void GameState::update() {
    if (currentLevel) {
        currentLevel->update();
    }

    if (player) {
        player->update();
    }
}

void GameState::setLevelNumber(int newLevelNumber) {
    levelNumber = newLevelNumber;
}

int GameState::getLevelNumber() const {
    return levelNumber;
}
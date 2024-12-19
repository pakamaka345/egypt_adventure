#pragma once
#include <memory>
#include "states/LevelState.hpp"

class Character;
class LevelState;
class Map;

class GameState {
private:
    std::shared_ptr<Character> player;
    std::unique_ptr<LevelState> currentLevel;
    int levelNumber;

    GameState();

public:
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;
    ~GameState() = default;
    static GameState& getInstance();

    void initializePlayer(std::shared_ptr<Character> newPlayer);
    void setLevel(std::unique_ptr<LevelState> level);

    LevelState& getCurrentLevel();
    Character& getPlayer();

    void nextLevel(const Map& newMap, const LevelState::Position& startPos);

    void setLevelNumber(int newLevelNumber);
    int getLevelNumber() const;

    void update();
};
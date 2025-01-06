#pragma once
#include <memory>
#include <map>
#include "states/LevelState.hpp"

class Character;
class LevelState;
class Map;

class GameState {
private:
    std::shared_ptr<Character> player;
    std::shared_ptr<LevelState> currentLevel;
    std::map<int, std::shared_ptr<LevelState>> levels;
    int levelIndex;

    GameState();

public:
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;
    ~GameState() = default;
    static GameState& getInstance();

    void initializePlayer(std::shared_ptr<Character> newPlayer);
    void setLevel(std::shared_ptr<LevelState> level);

    LevelState& getCurrentLevel();
    Character& getPlayer();

    void nextLevel(const Position& startPos);
    void previousLevel(const Position& startPos);

    void setLevelIndex(int newLevelIndex);
    int getLevelIndex() const;

    void update();
};
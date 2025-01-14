#pragma once
#include <memory>
#include <map>
#include <vector>
#include "states/LevelState.hpp"

class Character;
class LevelState;
class Tile;
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

    void nextLevel(int newLevelIndex);
    void previousLevel(int newLevelIndex);

    void setLevelIndex(int newLevelIndex);
    int getLevelIndex() const;

    void update() const;

private:
    std::shared_ptr<LevelState> createLevel(int levelIndex);

    void onCollisionWithTile(const std::vector<std::shared_ptr<Tile>>& adjacent) const;
    void onCollisionWithItem(const std::vector<std::shared_ptr<Tile>>& adjacent) const;
};
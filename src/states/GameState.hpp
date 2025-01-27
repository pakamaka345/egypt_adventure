#pragma once
#include <memory>
#include <map>
#include <vector>
#include "states/LevelState.hpp"
#include "utils/PriorityQueue.hpp"

class Character;
class LevelState;
class Tile;
class Map;

constexpr int MAX_LEVELS = 3;

class GameState {
private:
    std::shared_ptr<Character> player;
    std::shared_ptr<LevelState> currentLevel;
    std::map<int, std::shared_ptr<LevelState>> levels;
    PriorityQueue queue;
    int levelIndex;
    bool isGameOver;

    GameState();

public:
    GameState(const GameState&) = delete;
    GameState& operator=(const GameState&) = delete;
    ~GameState() = default;
    static GameState& getInstance();

    void initializePlayer(std::shared_ptr<Character> newPlayer);
    void setLevel(std::shared_ptr<LevelState> level);

    LevelState& getCurrentLevel();
    std::map<int, std::shared_ptr<LevelState>>& getLevels();
    std::shared_ptr<Character> getPlayer();

    void nextLevel(int newLevelIndex);
    void previousLevel(int newLevelIndex);

    void setLevelIndex(int newLevelIndex);
    [[nodiscard]] int getLevelIndex() const;

    void setIsGameOver(const bool newIsGameOver) { isGameOver = newIsGameOver; }
    [[nodiscard]] bool getIsGameOver() const { return isGameOver; }

    void update();

    void handleInteraction();

private:
    std::shared_ptr<LevelState> createLevel(int levelIndex);

    void onCollisionWithTile(const std::vector<std::shared_ptr<Tile>>& adjacent) const;
    void onCollisionWithItem(const std::vector<std::shared_ptr<Tile>>& adjacent) const;
};
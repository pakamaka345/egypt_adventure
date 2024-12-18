#pragma once
#include <string>
#include "PriorityQueue.hpp"

class Entity;

class BattleSystem
{
private:
    PriorityQueue queue;
    std::vector<std::shared_ptr<Entity>> entitiesList;

public:
    explicit BattleSystem(const std::string& pathToInitFile);
    ~BattleSystem() = default;

    void addEntityToList(const std::shared_ptr<Entity>& entity);
    void removeEntityFromList(const std::shared_ptr<Entity>& entity);

    void addEntityToBattle(const std::shared_ptr<Entity>& entity);
    void removeEntityFromBattle(const std::shared_ptr<Entity>& entity);
    void clearBattle();

    void startBattle(int rounds);

    std::vector<std::shared_ptr<Entity>>& getEntitiesList();

private:
    std::shared_ptr<Entity> findTarget();
    void updateEntities();

    // Now will just create the entities class but after i wanna replace this method to a Config class
    void readEntitiesFromFile(const std::string &pathToInitFile);
};